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

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TailwindAudioProcessorEditor)
};
