#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <cmath>

TailwindAudioProcessor::TailwindAudioProcessor()
    : AudioProcessor(
          BusesProperties()
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Parameters", FaustParams::createLayout()),
      faustBridge(apvts) {}

TailwindAudioProcessor::~TailwindAudioProcessor() {}

const juce::String TailwindAudioProcessor::getName() const {
  return JucePlugin_Name;
}

bool TailwindAudioProcessor::acceptsMidi() const { return false; }

bool TailwindAudioProcessor::producesMidi() const { return false; }

bool TailwindAudioProcessor::isMidiEffect() const { return false; }

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

  const auto decay = juce::jlimit(
      static_cast<float>(minDecay), static_cast<float>(maxDecay),
      decayParam != nullptr ? decayParam->load() : 0.85f);
  const auto predelayMs = juce::jlimit(
      0.0f, 500.0f,
      predelayParam != nullptr ? predelayParam->load() : 20.0f);

  const auto normalizedDecay = (decay - static_cast<float>(minDecay)) /
                               static_cast<float>(maxDecay - minDecay);
  const auto t60Seconds =
      minT60Seconds * std::pow(maxT60Seconds / minT60Seconds, normalizedDecay);

  return (predelayMs / 1000.0) + t60Seconds;
}

int TailwindAudioProcessor::getNumPrograms() { return 1; }

int TailwindAudioProcessor::getCurrentProgram() { return 0; }

void TailwindAudioProcessor::setCurrentProgram(int index) {
  juce::ignoreUnused(index);
}

const juce::String TailwindAudioProcessor::getProgramName(int index) {
  juce::ignoreUnused(index);
  return {};
}

void TailwindAudioProcessor::changeProgramName(int index,
                                              const juce::String &newName) {
  juce::ignoreUnused(index, newName);
}

void TailwindAudioProcessor::prepareToPlay(double sampleRate,
                                           int samplesPerBlock) {
  currentSampleRate = sampleRate;
  inputMeterPeak.store(0.0f);
  outputMeterPeak.store(0.0f);
  faustBridge.prepare(sampleRate, samplesPerBlock);
}

void TailwindAudioProcessor::releaseResources() {
  // Release resources here
}

void TailwindAudioProcessor::updatePeakMeter(std::atomic<float> &meterState,
                                            float blockPeak,
                                            int numSamples) noexcept {
  const auto heldPeak = meterState.load(std::memory_order_relaxed);
  if (blockPeak >= heldPeak) {
    meterState.store(blockPeak, std::memory_order_relaxed);
    return;
  }

  const auto decayTimeSeconds = 0.16f;
  const auto decay = std::exp(
      -static_cast<float>(numSamples) /
      static_cast<float>(juce::jmax(1.0, currentSampleRate * decayTimeSeconds)));
  meterState.store(heldPeak * decay, std::memory_order_relaxed);
}

bool TailwindAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
  const auto mainInput = layouts.getMainInputChannelSet();
  const auto mainOutput = layouts.getMainOutputChannelSet();

  if (mainOutput != juce::AudioChannelSet::stereo())
    return false;

  if (mainInput != juce::AudioChannelSet::mono() &&
      mainInput != juce::AudioChannelSet::stereo())
    return false;

  return true;
}

void TailwindAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                         juce::MidiBuffer &midiMessages) {
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
  const auto outputGainDb =
      apvts.getRawParameterValue(FaustParamIDs::outputGainDb);
  const auto inputGainLinear = juce::Decibels::decibelsToGain(
      inputGainDb != nullptr ? inputGainDb->load() : 0.0f);
  juce::ignoreUnused(outputGainDb);

  updatePeakMeter(inputMeterPeak,
                  juce::jlimit(0.0f, 1.2f,
                               getMaxPeak(totalNumInputChannels) * inputGainLinear),
                  buffer.getNumSamples());

  faustBridge.process(buffer, totalNumInputChannels, totalNumOutputChannels);

  updatePeakMeter(outputMeterPeak,
                  juce::jlimit(0.0f, 1.2f, getMaxPeak(totalNumOutputChannels)),
                  buffer.getNumSamples());
}

bool TailwindAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor *TailwindAudioProcessor::createEditor() {
  return new TailwindAudioProcessorEditor(*this);
}

void TailwindAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
  auto state = apvts.copyState();
  std::unique_ptr<juce::XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);
}

void TailwindAudioProcessor::setStateInformation(const void *data,
                                                int sizeInBytes) {
  std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
  if (xml && xml->hasTagName(apvts.state.getType()))
    apvts.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new TailwindAudioProcessor();
}
