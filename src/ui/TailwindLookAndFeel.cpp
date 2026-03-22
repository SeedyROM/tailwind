#include "TailwindLookAndFeel.h"
#include "TailwindColors.h"
#include <cmath>

TailwindLookAndFeel::TailwindLookAndFeel() {
  // Global colour overrides
  setColour(juce::Slider::textBoxTextColourId,
            juce::Colour(TailwindColors::valueText));
  setColour(juce::Slider::textBoxBackgroundColourId,
            juce::Colours::transparentBlack);
  setColour(juce::Slider::textBoxOutlineColourId,
            juce::Colours::transparentBlack);

  setColour(juce::Label::textColourId, juce::Colour(TailwindColors::labelText));

  setColour(juce::ToggleButton::textColourId,
            juce::Colour(TailwindColors::labelText));
  setColour(juce::ToggleButton::tickColourId,
            juce::Colour(TailwindColors::freezeOn));

  setColour(juce::TextEditor::backgroundColourId,
            juce::Colours::transparentBlack);
  setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentBlack);
  setColour(juce::TextEditor::textColourId,
            juce::Colour(TailwindColors::valueText));
}

void TailwindLookAndFeel::drawRotarySlider(
    juce::Graphics &g, int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, juce::Slider & /*slider*/) {
  // Geometry
  const float diameter =
      (static_cast<float>(juce::jmin(width, height)) - 10.0f) * 0.82f;
  const float radius = diameter * 0.5f;
  const float centreX =
      static_cast<float>(x) + static_cast<float>(width) * 0.5f;
  const float centreY =
      static_cast<float>(y) + static_cast<float>(height) * 0.5f;
  const float rx = centreX - radius;
  const float ry = centreY - radius;

  const float angle =
      rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

  // ---- Arc track (background) ----
  const float arcRadius = radius + 4.0f;
  const float arcThickness = 3.0f;

  juce::Path arcBg;
  arcBg.addCentredArc(centreX, centreY, arcRadius, arcRadius, 0.0f,
                      rotaryStartAngle, rotaryEndAngle, true);
  g.setColour(juce::Colour(TailwindColors::knobTrackBg));
  g.strokePath(arcBg,
               juce::PathStrokeType(arcThickness, juce::PathStrokeType::curved,
                                    juce::PathStrokeType::rounded));

  // ---- Arc fill (active) ----
  if (sliderPos > 0.0f) {
    juce::Path arcFill;
    arcFill.addCentredArc(centreX, centreY, arcRadius, arcRadius, 0.0f,
                          rotaryStartAngle, angle, true);

    juce::ColourGradient arcGrad(juce::Colour(TailwindColors::knobArc),
                                 centreX - arcRadius, centreY,
                                 juce::Colour(TailwindColors::knobArcBright),
                                 centreX + arcRadius, centreY, false);
    g.setGradientFill(arcGrad);
    g.strokePath(arcFill, juce::PathStrokeType(arcThickness,
                                               juce::PathStrokeType::curved,
                                               juce::PathStrokeType::rounded));
  }

  // ---- Knob shadow ----
  {
    juce::Path shadowPath;
    shadowPath.addEllipse(rx + 1.5f, ry + 2.0f, diameter, diameter);
    g.setColour(juce::Colour(0x30000000));
    g.fillPath(shadowPath);
  }

  // ---- Knob body (gradient) ----
  {
    juce::ColourGradient bodyGrad(
        juce::Colour(TailwindColors::knobBodyLight), centreX, ry,
        juce::Colour(TailwindColors::knobBody), centreX, ry + diameter, false);
    g.setGradientFill(bodyGrad);
    g.fillEllipse(rx, ry, diameter, diameter);
  }

  // ---- Knob outline ring ----
  g.setColour(juce::Colour(TailwindColors::knobOutline));
  g.drawEllipse(rx, ry, diameter, diameter, 1.5f);

  // ---- Inner bevel (subtle highlight ring) ----
  {
    const float inset = 2.0f;
    g.setColour(juce::Colour(0x18ffffff));
    g.drawEllipse(rx + inset, ry + inset, diameter - inset * 2.0f,
                  diameter - inset * 2.0f, 0.8f);
  }

  // ---- Pointer / notch ----
  {
    juce::Path pointer;
    const float pointerLength = radius * 0.58f;
    const float pointerThickness = 2.5f;
    pointer.addRoundedRectangle(-pointerThickness * 0.5f, -radius + 6.0f,
                                pointerThickness, pointerLength, 1.0f);

    pointer.applyTransform(
        juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(juce::Colour(TailwindColors::knobPointer));
    g.fillPath(pointer);
  }

  // ---- Centre dot ----
  {
    const float dotRadius = 2.5f;
    g.setColour(juce::Colour(TailwindColors::knobPointer).withAlpha(0.6f));
    g.fillEllipse(centreX - dotRadius, centreY - dotRadius, dotRadius * 2.0f,
                  dotRadius * 2.0f);
  }
}

void TailwindLookAndFeel::drawToggleButton(juce::Graphics &g,
                                           juce::ToggleButton &button,
                                           bool shouldDrawButtonAsHighlighted,
                                           bool /*shouldDrawButtonAsDown*/) {
  auto bounds = button.getLocalBounds().toFloat().reduced(2.0f);

  const bool isOn = button.getToggleState();

  // Background pill shape
  const float cornerRadius = bounds.getHeight() * 0.5f;

  if (isOn) {
    // Outer glow
    auto glowBounds = bounds.expanded(3.0f);
    g.setColour(juce::Colour(TailwindColors::freezeGlow));
    g.fillRoundedRectangle(glowBounds, cornerRadius + 3.0f);
  }

  // Pill background
  g.setColour(isOn ? juce::Colour(TailwindColors::freezeOn).withAlpha(0.3f)
                   : juce::Colour(TailwindColors::freezeOff));
  g.fillRoundedRectangle(bounds, cornerRadius);

  // Pill border
  g.setColour(isOn ? juce::Colour(TailwindColors::freezeOn)
                   : juce::Colour(TailwindColors::panelBorder));
  g.drawRoundedRectangle(bounds, cornerRadius, 1.5f);

  // Label text
  auto textBounds = bounds;
  g.setColour(isOn ? juce::Colour(TailwindColors::freezeOn)
                   : juce::Colour(TailwindColors::labelText));
  g.setFont(juce::Font(13.0f));
  g.drawText(button.getButtonText(), textBounds, juce::Justification::centred);

  // Highlight on hover
  if (shouldDrawButtonAsHighlighted) {
    g.setColour(juce::Colour(0x10ffffff));
    g.fillRoundedRectangle(bounds, cornerRadius);
  }
}

void TailwindLookAndFeel::drawLabel(juce::Graphics &g, juce::Label &label) {
  auto bounds = label.getLocalBounds().toFloat();

  // Draw rounded background/border for slider value readout labels
  // We detect these by checking if the parent is a Slider
  if (dynamic_cast<juce::Slider *>(label.getParentComponent()) != nullptr) {
    auto boxBounds = bounds.reduced(2.0f, 2.0f);
    g.setColour(juce::Colour(0xff222020)); // subtle dark background
    g.fillRoundedRectangle(boxBounds, 4.0f);
    g.setColour(juce::Colour(TailwindColors::panelBorder));
    g.drawRoundedRectangle(boxBounds, 4.0f, 1.0f);
  } else {
    g.fillAll(label.findColour(juce::Label::backgroundColourId));
  }

  if (!label.isBeingEdited()) {
    const auto alpha = label.isEnabled() ? 1.0f : 0.5f;
    const auto font = getLabelFont(label);

    g.setColour(
        label.findColour(juce::Label::textColourId).withMultipliedAlpha(alpha));
    g.setFont(font);

    auto textArea =
        getLabelBorderSize(label).subtractedFrom(label.getLocalBounds());
    g.drawFittedText(
        label.getText(), textArea, label.getJustificationType(),
        juce::jmax(1, (int)(textArea.getHeight() / font.getHeight())),
        label.getMinimumHorizontalScale());
  }
}

juce::Label *TailwindLookAndFeel::createSliderTextBox(juce::Slider &slider) {
  auto *label = LookAndFeel_V4::createSliderTextBox(slider);

  label->setColour(juce::Label::textColourId,
                   juce::Colour(TailwindColors::valueText));
  label->setColour(juce::Label::backgroundColourId,
                   juce::Colours::transparentBlack);
  label->setColour(juce::Label::outlineColourId,
                   juce::Colours::transparentBlack);
  // Editor colours (when user clicks to type)
  label->setColour(juce::TextEditor::backgroundColourId,
                   juce::Colour(0xff222020));
  label->setColour(juce::TextEditor::outlineColourId,
                   juce::Colour(TailwindColors::panelBorder));
  label->setColour(juce::TextEditor::textColourId,
                   juce::Colour(TailwindColors::valueText));

  return label;
}
