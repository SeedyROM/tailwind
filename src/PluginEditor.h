#pragma once

#include "PluginProcessor.h"
#include "components/brand/TopBar.h"
#include "components/controls/FreezeButton.h"
#include "components/controls/RotaryKnob.h"
#include "ui/TailwindLookAndFeel.h"

#include <juce_audio_processors/juce_audio_processors.h>

class TailwindAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  TailwindAudioProcessorEditor(TailwindAudioProcessor &);
  ~TailwindAudioProcessorEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  // Custom look and feel
  TailwindLookAndFeel tailwindLnf;

  // Components
  TopBar topBar;

  // --- MAIN section ---
  RotaryKnob mixKnob;
  RotaryKnob decayKnob;
  RotaryKnob preDelayKnob;
  RotaryKnob diffusionKnob;

  // --- TONE section ---
  RotaryKnob dampingKnob;
  RotaryKnob lowDampKnob;
  RotaryKnob lowCutKnob;
  RotaryKnob highCutKnob;

  // --- MODULATION section ---
  RotaryKnob modRateKnob;
  RotaryKnob modDepthKnob;

  // --- CHARACTER section ---
  RotaryKnob saturationKnob;
  RotaryKnob freezeKnob;
  FreezeButton freezeOnBtn;

  // Helpers
  void drawSectionPanel(juce::Graphics &g, juce::Rectangle<int> bounds,
                        const juce::String &title);

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TailwindAudioProcessorEditor)
};
