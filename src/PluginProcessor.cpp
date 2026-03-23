#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <cmath>

namespace {

constexpr auto pluginStateRootType = "TailwindPluginState";
constexpr auto pluginStatePropertySchemaVersion = "schemaVersion";
constexpr auto pluginStatePropertyPluginVersion = "pluginVersion";
constexpr auto pluginStatePropertyActiveABSlot = "activeABSlot";
constexpr auto pluginStatePropertySlotAPresetName = "slotAPresetName";
constexpr auto pluginStatePropertySlotBPresetName = "slotBPresetName";
constexpr auto pluginStateChildSlotA = "slotAState";
constexpr auto pluginStateChildSlotB = "slotBState";
constexpr auto abSlotNameA = "A";
constexpr auto abSlotNameB = "B";

} // namespace

TailwindAudioProcessor::TailwindAudioProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Parameters", FaustParams::createLayout()), faustBridge(apvts) {
  defaultPresetState = captureCurrentState();
  initialiseABSlotsFromCurrentState();
}

TailwindAudioProcessor::~TailwindAudioProcessor() {}

const juce::String TailwindAudioProcessor::getName() const {
  return JucePlugin_Name;
}

bool TailwindAudioProcessor::acceptsMidi() const {
  return false;
}

bool TailwindAudioProcessor::producesMidi() const {
  return false;
}

bool TailwindAudioProcessor::isMidiEffect() const {
  return false;
}

double TailwindAudioProcessor::getTailLengthSeconds() const {
  constexpr double minDecay = 0.1;
  constexpr double maxDecay = 0.99;
  constexpr double minT60Seconds = 0.2;
  constexpr double maxT60Seconds = 30.0;
  constexpr double freezeTailSeconds = 60.0;

  const auto freezeOn = apvts.getRawParameterValue(FaustParamIDs::freezeOn);
  if (freezeOn != nullptr && *freezeOn > 0.5f)
    return freezeTailSeconds;

  const auto decayParam = apvts.getRawParameterValue(FaustParamIDs::decay);
  const auto predelayParam = apvts.getRawParameterValue(FaustParamIDs::preDelayMs);

  const auto decay = juce::jlimit(static_cast<float>(minDecay),
                                  static_cast<float>(maxDecay),
                                  decayParam != nullptr ? decayParam->load() : 0.85f);
  const auto predelayMs =
      juce::jlimit(0.0f, 500.0f, predelayParam != nullptr ? predelayParam->load() : 20.0f);

  const auto normalizedDecay =
      (decay - static_cast<float>(minDecay)) / static_cast<float>(maxDecay - minDecay);
  const auto t60Seconds = minT60Seconds * std::pow(maxT60Seconds / minT60Seconds, normalizedDecay);

  return (predelayMs / 1000.0) + t60Seconds;
}

int TailwindAudioProcessor::getNumPrograms() {
  return 1;
}

int TailwindAudioProcessor::getCurrentProgram() {
  return 0;
}

void TailwindAudioProcessor::setCurrentProgram(int index) {
  juce::ignoreUnused(index);
}

const juce::String TailwindAudioProcessor::getProgramName(int index) {
  juce::ignoreUnused(index);
  return {};
}

void TailwindAudioProcessor::changeProgramName(int index, const juce::String& newName) {
  juce::ignoreUnused(index, newName);
}

void TailwindAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
  currentSampleRate = sampleRate;
  inputMeterPeak.store(0.0f);
  outputMeterPeak.store(0.0f);
  faustBridge.prepare(sampleRate, samplesPerBlock);
}

void TailwindAudioProcessor::releaseResources() {
  // Release resources here
}

juce::ValueTree TailwindAudioProcessor::captureCurrentState() {
  auto state = apvts.copyState();
  sanitiseTransientState(state);
  return state;
}

juce::ValueTree TailwindAudioProcessor::createWrappedPluginState(bool includeABState) {
  juce::ValueTree wrappedState(pluginStateRootType);
  wrappedState.setProperty(pluginStatePropertySchemaVersion, stateSchemaVersion, nullptr);
  wrappedState.setProperty(pluginStatePropertyPluginVersion, JucePlugin_VersionString, nullptr);
  syncActiveABSlotFromCurrentState();
  wrappedState.appendChild(captureCurrentState(), nullptr);

  if (includeABState) {
    wrappedState.setProperty(pluginStatePropertyActiveABSlot,
                             activeABSlot == ABSlot::A ? abSlotNameA : abSlotNameB,
                             nullptr);
    wrappedState.setProperty(pluginStatePropertySlotAPresetName, slotAPresetName, nullptr);
    wrappedState.setProperty(pluginStatePropertySlotBPresetName, slotBPresetName, nullptr);

    juce::ValueTree slotAWrapper(pluginStateChildSlotA);
    slotAWrapper.appendChild(slotAState.createCopy(), nullptr);
    wrappedState.appendChild(slotAWrapper, nullptr);

    juce::ValueTree slotBWrapper(pluginStateChildSlotB);
    slotBWrapper.appendChild(slotBState.createCopy(), nullptr);
    wrappedState.appendChild(slotBWrapper, nullptr);
  }

  return wrappedState;
}

juce::ValueTree TailwindAudioProcessor::migrateStateTree(juce::ValueTree savedTree) const {
  auto schemaVersion = savedTree.getProperty(pluginStatePropertySchemaVersion);
  if (!schemaVersion.isInt() || static_cast<int>(schemaVersion) < 1)
    savedTree.setProperty(pluginStatePropertySchemaVersion, stateSchemaVersion, nullptr);

  if (!savedTree.hasProperty(pluginStatePropertyPluginVersion))
    savedTree.setProperty(pluginStatePropertyPluginVersion, JucePlugin_VersionString, nullptr);

  if (!savedTree.hasProperty(pluginStatePropertyActiveABSlot))
    savedTree.setProperty(pluginStatePropertyActiveABSlot, abSlotNameA, nullptr);

  if (!savedTree.hasProperty(pluginStatePropertySlotAPresetName))
    savedTree.setProperty(pluginStatePropertySlotAPresetName, "Init", nullptr);

  if (!savedTree.hasProperty(pluginStatePropertySlotBPresetName))
    savedTree.setProperty(pluginStatePropertySlotBPresetName, "Init", nullptr);

  return savedTree;
}

juce::ValueTree
TailwindAudioProcessor::extractPluginStateFromSavedTree(const juce::ValueTree& savedTree) const {
  if (!savedTree.isValid())
    return {};

  if (savedTree.hasType(apvts.state.getType()))
    return savedTree.createCopy();

  if (!savedTree.hasType(pluginStateRootType))
    return {};

  auto migratedTree = migrateStateTree(savedTree.createCopy());
  auto pluginState = migratedTree.getChildWithName(apvts.state.getType());
  return pluginState.isValid() ? pluginState.createCopy() : juce::ValueTree{};
}

void TailwindAudioProcessor::applyStateToApvts(const juce::ValueTree& stateToApply) {
  if (!stateToApply.isValid())
    return;

  const juce::ScopedValueSetter<bool> applyingState(isApplyingABState, true);
  apvts.replaceState(stateToApply.createCopy());
}

void TailwindAudioProcessor::initialiseABSlotsFromCurrentState() {
  auto currentState = captureCurrentState();
  slotAState = currentState.createCopy();
  slotBState = currentState.createCopy();
  activeABSlot = ABSlot::A;
  slotAPresetName = "Init";
  slotBPresetName = "Init";
}

void TailwindAudioProcessor::syncActiveABSlotFromCurrentState() {
  if (isApplyingABState)
    return;

  getMutableABState(activeABSlot) = captureCurrentState();
}

void TailwindAudioProcessor::sanitiseTransientState(juce::ValueTree& state) const {
  for (int i = 0; i < state.getNumChildren(); ++i) {
    auto child = state.getChild(i);
    if (child.hasProperty("id") && child["id"].toString() == "freeze_on")
      child.setProperty("value", 0.0f, nullptr);
  }
}

void TailwindAudioProcessor::setActivePresetName(const juce::String& presetName) {
  if (activeABSlot == ABSlot::A)
    slotAPresetName = presetName;
  else
    slotBPresetName = presetName;
}

juce::ValueTree& TailwindAudioProcessor::getMutableABState(ABSlot slot) {
  return slot == ABSlot::A ? slotAState : slotBState;
}

const juce::ValueTree& TailwindAudioProcessor::getABState(ABSlot slot) const {
  return slot == ABSlot::A ? slotAState : slotBState;
}

void TailwindAudioProcessor::setActiveABSlot(ABSlot slot) {
  if (slot == activeABSlot)
    return;

  syncActiveABSlotFromCurrentState();
  activeABSlot = slot;
  applyStateToApvts(getABState(activeABSlot));
}

void TailwindAudioProcessor::copyABSlot(ABSlot from, ABSlot to) {
  syncActiveABSlotFromCurrentState();
  getMutableABState(to) = getABState(from).createCopy();
  if (from == ABSlot::A)
    slotBPresetName = slotAPresetName;
  else
    slotAPresetName = slotBPresetName;

  if (activeABSlot == to)
    applyStateToApvts(getABState(to));
}

void TailwindAudioProcessor::swapABSlots() {
  syncActiveABSlotFromCurrentState();
  auto previousA = slotAState.createCopy();
  auto previousName = slotAPresetName;
  slotAState = slotBState.createCopy();
  slotBState = previousA;
  slotAPresetName = slotBPresetName;
  slotBPresetName = previousName;
  applyStateToApvts(getABState(activeABSlot));
}

juce::StringArray TailwindAudioProcessor::getAvailablePresetNames() const {
  juce::StringArray names;
  for (const auto& preset :
       TailwindPresetManager::getAvailablePresets(defaultPresetState, apvts.state.getType()))
    names.add(preset.name);
  return names;
}

bool TailwindAudioProcessor::hasDistinctABState() const {
  return !slotAState.isEquivalentTo(slotBState);
}

juce::String TailwindAudioProcessor::getActivePresetName() const {
  return activeABSlot == ABSlot::A ? slotAPresetName : slotBPresetName;
}

juce::String TailwindAudioProcessor::getDisplayedPresetName() {
  syncActiveABSlotFromCurrentState();

  const auto activePresetName = getActivePresetName();
  const auto currentState = captureCurrentState();
  const auto presetState = TailwindPresetManager::loadPresetState(
      activePresetName, defaultPresetState, apvts.state.getType());

  if (!presetState.isValid())
    return activePresetName;

  return currentState.isEquivalentTo(presetState) ? activePresetName : "Custom";
}

bool TailwindAudioProcessor::isActivePresetFactory() const {
  return TailwindPresetManager::isFactoryPreset(
      getActivePresetName(), defaultPresetState, apvts.state.getType());
}

bool TailwindAudioProcessor::loadPreset(const juce::String& presetName) {
  auto presetState =
      TailwindPresetManager::loadPresetState(presetName, defaultPresetState, apvts.state.getType());
  if (!presetState.isValid())
    return false;

  getMutableABState(activeABSlot) = presetState.createCopy();
  setActivePresetName(presetName);
  applyStateToApvts(getABState(activeABSlot));
  return true;
}

bool TailwindAudioProcessor::saveUserPreset(const juce::String& presetName) {
  syncActiveABSlotFromCurrentState();
  auto wrappedState = createWrappedPluginState(false);
  if (!TailwindPresetManager::saveUserPreset(presetName, wrappedState))
    return false;

  setActivePresetName(presetName);
  return true;
}

bool TailwindAudioProcessor::deleteActiveUserPreset() {
  auto presetName = getActivePresetName();
  if (presetName.isEmpty() ||
      TailwindPresetManager::isFactoryPreset(presetName, defaultPresetState, apvts.state.getType()))
    return false;

  if (!TailwindPresetManager::deleteUserPreset(presetName))
    return false;

  setActivePresetName("Init");
  return true;
}

void TailwindAudioProcessor::revealPresetDirectory() const {
  TailwindPresetManager::revealPresetDirectory();
}

void TailwindAudioProcessor::clearABState() {
  syncActiveABSlotFromCurrentState();
  slotBState = slotAState.createCopy();
  slotBPresetName = slotAPresetName;
  activeABSlot = ABSlot::A;
}

void TailwindAudioProcessor::updatePeakMeter(std::atomic<float>& meterState,
                                             float blockPeak,
                                             int numSamples) noexcept {
  const auto heldPeak = meterState.load(std::memory_order_relaxed);
  if (blockPeak >= heldPeak) {
    meterState.store(blockPeak, std::memory_order_relaxed);
    return;
  }

  const auto decayTimeSeconds = 0.16f;
  const auto decay =
      std::exp(-static_cast<float>(numSamples) /
               static_cast<float>(juce::jmax(1.0, currentSampleRate * decayTimeSeconds)));
  meterState.store(heldPeak * decay, std::memory_order_relaxed);
}

bool TailwindAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
  const auto mainInput = layouts.getMainInputChannelSet();
  const auto mainOutput = layouts.getMainOutputChannelSet();

  if (mainOutput != juce::AudioChannelSet::stereo())
    return false;

  if (mainInput != juce::AudioChannelSet::mono() && mainInput != juce::AudioChannelSet::stereo())
    return false;

  return true;
}

void TailwindAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                          juce::MidiBuffer& midiMessages) {
  juce::ignoreUnused(midiMessages);
  juce::ScopedNoDenormals noDenormals;

  const auto totalNumInputChannels = getTotalNumInputChannels();
  const auto totalNumOutputChannels = getTotalNumOutputChannels();

  // Clear any output channels that don't have input
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  auto getMaxPeak = [&buffer](int numChannels) {
    auto peak = 0.0f;
    for (int ch = 0; ch < numChannels; ++ch)
      peak = juce::jmax(peak, buffer.getMagnitude(ch, 0, buffer.getNumSamples()));
    return peak;
  };

  const auto inputGainDb = apvts.getRawParameterValue(FaustParamIDs::inputGainDb);
  const auto outputGainDb = apvts.getRawParameterValue(FaustParamIDs::outputGainDb);
  const auto inputGainLinear =
      juce::Decibels::decibelsToGain(inputGainDb != nullptr ? inputGainDb->load() : 0.0f);
  juce::ignoreUnused(outputGainDb);

  updatePeakMeter(inputMeterPeak,
                  juce::jlimit(0.0f, 1.2f, getMaxPeak(totalNumInputChannels) * inputGainLinear),
                  buffer.getNumSamples());

  faustBridge.process(buffer, totalNumInputChannels, totalNumOutputChannels);

  updatePeakMeter(outputMeterPeak,
                  juce::jlimit(0.0f, 1.2f, getMaxPeak(totalNumOutputChannels)),
                  buffer.getNumSamples());
}

bool TailwindAudioProcessor::hasEditor() const {
  return true;
}

juce::AudioProcessorEditor* TailwindAudioProcessor::createEditor() {
  return new TailwindAudioProcessorEditor(*this);
}

void TailwindAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
  auto state = createWrappedPluginState(true);
  std::unique_ptr<juce::XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);
}

void TailwindAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
  std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
  if (xml == nullptr)
    return;

  auto restoredTree = juce::ValueTree::fromXml(*xml);
  auto pluginState = extractPluginStateFromSavedTree(restoredTree);
  if (!pluginState.isValid())
    return;

  applyStateToApvts(pluginState);

  if (restoredTree.hasType(pluginStateRootType)) {
    auto migratedTree = migrateStateTree(restoredTree.createCopy());
    auto restoredSlotAWrapper = migratedTree.getChildWithName(pluginStateChildSlotA);
    auto restoredSlotBWrapper = migratedTree.getChildWithName(pluginStateChildSlotB);

    auto restoredSlotA = restoredSlotAWrapper.getChildWithName(apvts.state.getType());
    auto restoredSlotB = restoredSlotBWrapper.getChildWithName(apvts.state.getType());

    if (restoredSlotA.isValid() && restoredSlotB.isValid()) {
      slotAState = restoredSlotA.createCopy();
      slotBState = restoredSlotB.createCopy();
      slotAPresetName = migratedTree[pluginStatePropertySlotAPresetName].toString();
      slotBPresetName = migratedTree[pluginStatePropertySlotBPresetName].toString();
      activeABSlot = migratedTree[pluginStatePropertyActiveABSlot].toString() == abSlotNameB
                         ? ABSlot::B
                         : ABSlot::A;
      applyStateToApvts(getABState(activeABSlot));
      return;
    }
  }

  initialiseABSlotsFromCurrentState();
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new TailwindAudioProcessor();
}
