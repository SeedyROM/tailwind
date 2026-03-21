#include "PluginEditor.h"
#include "BinaryData.h"
#include "FaustParams.h"
#include "PluginProcessor.h"

TailwindAudioProcessorEditor::TailwindAudioProcessorEditor(
    TailwindAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {

  // Top bar
  addAndMakeVisible(topBar);

  // Set up all parameter sliders
  setupSlider(mixSlider, "Mix", FaustParamIDs::mix);
  setupSlider(decaySlider, "Decay", FaustParamIDs::decay);
  setupSlider(preDelaySlider, "Pre-Delay", FaustParamIDs::preDelayMs);
  setupSlider(diffusionSlider, "Diffusion", FaustParamIDs::diffusion);
  setupSlider(dampingSlider, "Damping", FaustParamIDs::damping);
  setupSlider(lowDampSlider, "Low Damp", FaustParamIDs::lowDamp);
  setupSlider(modRateSlider, "Mod Rate", FaustParamIDs::modRateHz);
  setupSlider(modDepthSlider, "Mod Depth", FaustParamIDs::modDepth);
  setupSlider(lowCutSlider, "Low Cut", FaustParamIDs::lowCutHz);
  setupSlider(highCutSlider, "High Cut", FaustParamIDs::highCutHz);
  setupSlider(freezeSlider, "Freeze", FaustParamIDs::freeze);
  setupSlider(saturationSlider, "Saturation", FaustParamIDs::saturation);

  // Freeze On toggle button
  addAndMakeVisible(freezeOnButton);
  freezeOnAttachment =
      std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
          audioProcessor.apvts, FaustParamIDs::freezeOn, freezeOnButton);

  setSize(800, 600);
}

TailwindAudioProcessorEditor::~TailwindAudioProcessorEditor() {}

void TailwindAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(juce::Colour(0xff1a1a1a));
}

void TailwindAudioProcessorEditor::resized() {
  auto bounds = getLocalBounds();

  // Top bar (full width)
  topBar.setBounds(bounds.removeFromTop(50));

  // Main content area with padding
  bounds.reduce(10, 10);

  // Collect all sliders for grid layout
  ParamSlider *sliders[] = {
      &mixSlider,       &decaySlider,    &preDelaySlider, &diffusionSlider,
      &dampingSlider,   &lowDampSlider,  &modRateSlider,  &modDepthSlider,
      &lowCutSlider,    &highCutSlider,  &freezeSlider,   &saturationSlider,
  };

  const int columns = 4;
  const int rows = 3;
  const int sliderWidth = bounds.getWidth() / columns;
  const int sliderHeight =
      (bounds.getHeight() - 40) / rows; // reserve 40px for the toggle row

  for (int i = 0; i < 12; ++i) {
    int col = i % columns;
    int row = i / columns;
    auto cell = juce::Rectangle<int>(bounds.getX() + col * sliderWidth,
                                     bounds.getY() + row * sliderHeight,
                                     sliderWidth, sliderHeight);

    // Label on top, slider below
    sliders[i]->label.setBounds(cell.removeFromTop(20));
    sliders[i]->slider.setBounds(cell.reduced(4, 0));
  }

  // Toggle button row at the bottom
  auto toggleRow = bounds.removeFromBottom(36);
  freezeOnButton.setBounds(toggleRow.removeFromLeft(140));
}

void TailwindAudioProcessorEditor::setupSlider(ParamSlider &ps,
                                                const juce::String &labelText,
                                                const juce::String &paramID) {
  ps.slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
  ps.slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 18);
  addAndMakeVisible(ps.slider);

  ps.label.setText(labelText, juce::dontSendNotification);
  ps.label.setJustificationType(juce::Justification::centred);
  ps.label.attachToComponent(&ps.slider, false);
  addAndMakeVisible(ps.label);

  ps.attachment =
      std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
          audioProcessor.apvts, paramID, ps.slider);
}
