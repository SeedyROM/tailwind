#include "PluginProcessor.h"
#include "PluginEditor.h"

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

double TailwindAudioProcessor::getTailLengthSeconds() const { return 0.0; }

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
  faustBridge.prepare(sampleRate, samplesPerBlock);
}

void TailwindAudioProcessor::releaseResources() {
  // Release resources here
}

bool TailwindAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;

  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;

  return true;
}

void TailwindAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                         juce::MidiBuffer &midiMessages) {
  juce::ignoreUnused(midiMessages);
  juce::ScopedNoDenormals noDenormals;

  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  // Clear any output channels that don't have input
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  faustBridge.process(buffer);
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
