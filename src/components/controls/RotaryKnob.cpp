#include "RotaryKnob.h"

RotaryKnob::RotaryKnob(juce::AudioProcessorValueTreeState &apvts,
                       const juce::String &paramID,
                       const juce::String &labelText,
                       const juce::String &suffix, bool showAsPercentage) {
  // Slider configuration
  slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
  slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 68, 22);
  slider.setColour(juce::Slider::textBoxTextColourId,
                   juce::Colour(TailwindColors::valueText));
  slider.setColour(juce::Slider::textBoxBackgroundColourId,
                   juce::Colours::transparentBlack);
  slider.setColour(juce::Slider::textBoxOutlineColourId,
                   juce::Colours::transparentBlack);

  addAndMakeVisible(slider);

  // Label configuration
  label.setText(labelText, juce::dontSendNotification);
  label.setJustificationType(juce::Justification::centred);
  label.setColour(juce::Label::textColourId,
                  juce::Colour(TailwindColors::labelText));
  label.setFont(juce::Font(12.0f, juce::Font::bold));
  addAndMakeVisible(label);

  // APVTS attachment
  attachment =
      std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
          apvts, paramID, slider);

  // Unit suffix and percentage display — set AFTER attachment
  // The attachment overwrites textFromValueFunction, so we must
  // re-assign it here and force the text box to refresh.
  if (showAsPercentage) {
    slider.textFromValueFunction = [suffix](double value) {
      return juce::String(juce::roundToInt(value * 100.0)) + suffix;
    };
    slider.valueFromTextFunction = [suffix](const juce::String &text) {
      auto stripped = text.trimCharactersAtEnd(suffix);
      return stripped.getDoubleValue() / 100.0;
    };
  } else if (suffix.isNotEmpty()) {
    // For non-percentage params, wrap the attachment's textFromValue
    // to append our suffix, since setTextValueSuffix may conflict.
    auto existingTextFromValue = slider.textFromValueFunction;
    slider.textFromValueFunction = [existingTextFromValue,
                                    suffix](double value) {
      if (existingTextFromValue)
        return existingTextFromValue(value) + suffix;
      return juce::String(value) + suffix;
    };
    slider.valueFromTextFunction = [suffix](const juce::String &text) {
      auto stripped = text.trimCharactersAtEnd(suffix);
      return stripped.getDoubleValue();
    };
  }

  // Force text box to re-render with the new formatting
  slider.updateText();
}

void RotaryKnob::resized() {
  auto bounds = getLocalBounds();

  // Label on top (18px)
  label.setBounds(bounds.removeFromTop(18));

  // Small bottom margin
  bounds.removeFromBottom(2);

  // Slider takes the rest
  slider.setBounds(bounds);
}
