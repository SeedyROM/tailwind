#include "FreezeButton.h"

FreezeButton::FreezeButton(juce::AudioProcessorValueTreeState& apvts, const juce::String& paramID) {
  addAndMakeVisible(button);

  attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
      apvts, paramID, button);
}

void FreezeButton::resized() {
  button.setBounds(getLocalBounds());
}
