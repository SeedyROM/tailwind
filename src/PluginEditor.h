#pragma once

#include "PluginProcessor.h"
#include "components/brand/TopBar.h"
#include "components/controls/FreezeButton.h"
#include "components/controls/PowerButton.h"
#include "components/controls/RotaryKnob.h"
#include "ui/TailwindLookAndFeel.h"

#include <juce_audio_processors/juce_audio_processors.h>

class TailwindAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer {
public:
  TailwindAudioProcessorEditor(TailwindAudioProcessor&);
  ~TailwindAudioProcessorEditor() override;

  void paint(juce::Graphics&) override;
  void resized() override;

private:
  void timerCallback() override;
  void showOptionsMenu();
  void promptSavePreset();
  void refreshPresetControls();

  static constexpr int minEditorWidth = 760;
  static constexpr int minEditorHeight = 740;

  TailwindAudioProcessor& audioProcessor;

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

  // --- GAIN STAGING section ---
  RotaryKnob inputGainKnob;
  RotaryKnob outputGainKnob;

  // --- ECHO section ---
  PowerButton echoOnBtn;
  juce::TextButton echoPreFdnBtn;
  RotaryKnob echoTimeKnob;
  RotaryKnob echoFeedbackKnob;
  RotaryKnob echoColorKnob;
  RotaryKnob echoMixKnob;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> echoOnAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> echoPreFdnAttachment;

  // ---- Layout geometry (single source of truth for paint + resized) ----
  struct RowLayout {
    juce::Rectangle<int> topRow;
    juce::Rectangle<int> bottomRow;
    juce::Rectangle<int> echoRow;
  };

  RowLayout computeRowLayout() const {
    auto bounds = getLocalBounds();
    bounds.removeFromTop(50); // topBar
    bounds.reduce(12, 12);

    // topRow proportional (capped), echoRow fixed, bottomRow fills remaining.
    const int availH = bounds.getHeight();
    const int topH = juce::jlimit(280, 320, (availH * 2) / 3);
    const int echoH = 160;
    const int lowerH = availH - topH - 16 - echoH; // 16 = two 8px gaps

    RowLayout layout;
    layout.topRow = bounds.removeFromTop(topH);
    bounds.removeFromTop(8);
    layout.bottomRow = bounds.removeFromTop(lowerH);
    bounds.removeFromTop(8);
    layout.echoRow = bounds.removeFromTop(echoH);
    return layout;
  }

  // Helpers
  void drawSectionPanel(juce::Graphics& g, juce::Rectangle<int> bounds, const juce::String& title);
  void updateEchoSectionState();

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TailwindAudioProcessorEditor)
};
