#pragma once

#include "PluginProcessor.h"
#include "components/brand/TopBar.h"

#include <juce_audio_processors/juce_audio_processors.h>

class TailwindAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  TailwindAudioProcessorEditor(TailwindAudioProcessor &);
  ~TailwindAudioProcessorEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  TailwindAudioProcessor &audioProcessor;

  // Components
  TopBar topBar;

  // ---------------------------------------------------------------------------
  // Parameter controls — one slider per float param, one button for the toggle
  // ---------------------------------------------------------------------------
  struct ParamSlider {
    juce::Slider slider;
    juce::Label label;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        attachment;
  };

  ParamSlider mixSlider;
  ParamSlider decaySlider;
  ParamSlider preDelaySlider;
  ParamSlider diffusionSlider;
  ParamSlider dampingSlider;
  ParamSlider lowDampSlider;
  ParamSlider modRateSlider;
  ParamSlider modDepthSlider;
  ParamSlider lowCutSlider;
  ParamSlider highCutSlider;
  ParamSlider freezeSlider;
  ParamSlider saturationSlider;

  // Freeze On toggle
  juce::ToggleButton freezeOnButton{"Freeze On"};
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
      freezeOnAttachment;

  // Helper to set up a single param slider
  void setupSlider(ParamSlider &ps, const juce::String &labelText,
                   const juce::String &paramID);

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TailwindAudioProcessorEditor)
};
