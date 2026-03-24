#pragma once

#include "TailwindColors.h"
#include <juce_gui_basics/juce_gui_basics.h>

/**
 * Custom LookAndFeel for the Tailwind reverb plugin.
 * Warm analog aesthetic: charcoal body, amber arc indicators, notch pointers.
 */
class TailwindLookAndFeel : public juce::LookAndFeel_V4 {
public:
  TailwindLookAndFeel();
  ~TailwindLookAndFeel() override = default;

  // Rotary slider (knob)
  void drawRotarySlider(juce::Graphics& g,
                        int x,
                        int y,
                        int width,
                        int height,
                        float sliderPosProportional,
                        float rotaryStartAngle,
                        float rotaryEndAngle,
                        juce::Slider& slider) override;

  // Toggle button (for freeze)
  void drawToggleButton(juce::Graphics& g,
                        juce::ToggleButton& button,
                        bool shouldDrawButtonAsHighlighted,
                        bool shouldDrawButtonAsDown) override;

  // Label
  void drawLabel(juce::Graphics& g, juce::Label& label) override;

  // Slider text box (value readout with rounded border)
  juce::Label* createSliderTextBox(juce::Slider& slider) override;

  juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override;
  void drawButtonBackground(juce::Graphics& g,
                            juce::Button& button,
                            const juce::Colour& backgroundColour,
                            bool shouldDrawButtonAsHighlighted,
                            bool shouldDrawButtonAsDown) override;
  void drawButtonText(juce::Graphics& g,
                      juce::TextButton& button,
                      bool shouldDrawButtonAsHighlighted,
                      bool shouldDrawButtonAsDown) override;
  void drawComboBox(juce::Graphics& g,
                    int width,
                    int height,
                    bool isButtonDown,
                    int buttonX,
                    int buttonY,
                    int buttonW,
                    int buttonH,
                    juce::ComboBox& box) override;
  juce::Font getTextButtonFont(juce::TextButton& button, int buttonHeight) override;
  juce::Font getComboBoxFont(juce::ComboBox& box) override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TailwindLookAndFeel)
};
