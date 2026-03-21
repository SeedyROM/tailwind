#include "PluginEditor.h"
#include "BinaryData.h"
#include "PluginProcessor.h"

TailwindAudioProcessorEditor::TailwindAudioProcessorEditor(
    TailwindAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {

  // Add top bar
  addAndMakeVisible(topBar);

  setSize(800, 600);
}

TailwindAudioProcessorEditor::~TailwindAudioProcessorEditor() {}

void TailwindAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(juce::Colour(0xff1a1a1a)); // Dark background
}

void TailwindAudioProcessorEditor::resized() {
  auto bounds = getLocalBounds();

  // Top bar (full width)
  topBar.setBounds(bounds.removeFromTop(50));

  // Main content area
  bounds.reduce(10, 10);

  // Add your component layout here
}
