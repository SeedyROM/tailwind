#include "RotaryKnob.h"

#include <cmath>

namespace {

juce::Label *findSliderValueLabel(juce::Slider &slider) {
  for (int i = 0; i < slider.getNumChildComponents(); ++i)
    if (auto *label = dynamic_cast<juce::Label *>(slider.getChildComponent(i)))
      return label;

  return nullptr;
}

} // namespace

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
  slider.getProperties().set("tailwindShowMeter", false);

  slider.onValueChange = [this] { refreshMeter(); };

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

  valueLabel = findSliderValueLabel(slider);

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
      if (suffix == " Hz" && value >= 1000.0) {
        const auto truncatedKhz = std::floor(value / 10.0) / 100.0;
        return juce::String(truncatedKhz, 2) + " kHz";
      }

      if (existingTextFromValue)
        return existingTextFromValue(value) + suffix;
      return juce::String(value) + suffix;
    };
    slider.valueFromTextFunction = [suffix](const juce::String &text) {
      auto trimmed = text.trim();
      if (suffix == " Hz" && trimmed.endsWithIgnoreCase("kHz"))
        return trimmed.upToLastOccurrenceOf("k", false, false).trim()
                   .getDoubleValue() *
               1000.0;

      auto stripped = trimmed.trimCharactersAtEnd(suffix);
      return stripped.getDoubleValue();
    };
  }

  // Force text box to re-render with the new formatting
  slider.updateText();
  refreshMeter();
}

void RotaryKnob::setMeterSource(std::function<float()> newMeterSource,
                                bool shouldMeterColourValueText) {
  meterSource = std::move(newMeterSource);
  meterColourValueText = shouldMeterColourValueText;
  slider.getProperties().set("tailwindShowMeter", meterSource != nullptr);
  refreshMeter();
}

void RotaryKnob::refreshMeter() {
  meterPeak = meterSource ? meterSource() : 0.0f;

  slider.getProperties().set("tailwindMeterPeak", meterPeak);

  if (valueLabel != nullptr) {
    const auto useActiveMeterColour = meterColourValueText && meterPeak > 1.0e-4f;
    valueLabel->setColour(
        juce::Label::textColourId,
        useActiveMeterColour ? TailwindColors::meterColourForPeak(meterPeak)
                             : juce::Colour(TailwindColors::valueText));
    valueLabel->repaint();
  }

  slider.repaint();
}

void RotaryKnob::resized() {
  auto bounds = getLocalBounds();

  // Label on top (18px)
  label.setBounds(bounds.removeFromTop(18));

  // Small bottom margin
  bounds.removeFromBottom(2);

  // Slider takes the rest
  slider.setBounds(bounds);
  valueLabel = findSliderValueLabel(slider);
  refreshMeter();
}
