#pragma once

#include "ui/TailwindColors.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

/**
 * Freeze toggle button — illuminated pill-shaped toggle with ice-blue glow.
 * Attaches to an APVTS boolean parameter.
 */
class FreezeButton : public juce::Component {
public:
  FreezeButton(juce::AudioProcessorValueTreeState& apvts, const juce::String& paramID);
  ~FreezeButton() override = default;

  void resized() override;

private:
  juce::ToggleButton button{"FREEZE"};
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachment;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FreezeButton)
};
