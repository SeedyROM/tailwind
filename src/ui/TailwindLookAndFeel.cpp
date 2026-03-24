#include "TailwindLookAndFeel.h"
#include "TailwindColors.h"
#include <cmath>

namespace {

constexpr auto topBarButtonComponentId = "topbarABButton";
constexpr auto topBarPresetComponentId = "topbarPresetBox";

bool isTopBarButton(const juce::Button& button) {
  return button.getComponentID() == topBarButtonComponentId;
}

bool isTopBarPreset(const juce::ComboBox& box) {
  return box.getComponentID() == topBarPresetComponentId;
}

class TailwindSliderLabel : public juce::Label {
public:
  void editorShown(juce::TextEditor* editor) override {
    juce::Label::editorShown(editor);

    if (editor == nullptr)
      return;

    editor->setJustification(juce::Justification::centred);
    editor->setSelectAllWhenFocused(false);
    editor->applyColourToAllText(findColour(juce::TextEditor::textColourId));
    editor->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xff222020));
    editor->setColour(juce::TextEditor::outlineColourId, juce::Colour(TailwindColors::panelBorder));
    editor->setColour(juce::TextEditor::highlightColourId, juce::Colour(0x00000000));
    editor->setColour(juce::TextEditor::highlightedTextColourId,
                      findColour(juce::TextEditor::textColourId));
    editor->setCaretPosition(editor->getTotalNumChars());
    editor->setHighlightedRegion({editor->getCaretPosition(), editor->getCaretPosition()});
  }
};

} // namespace

TailwindLookAndFeel::TailwindLookAndFeel() {
  // Global colour overrides
  setColour(juce::Slider::textBoxTextColourId, juce::Colour(TailwindColors::valueText));
  setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
  setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);

  setColour(juce::Label::textColourId, juce::Colour(TailwindColors::labelText));

  setColour(juce::ToggleButton::textColourId, juce::Colour(TailwindColors::labelText));
  setColour(juce::ToggleButton::tickColourId, juce::Colour(TailwindColors::freezeOn));

  setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentBlack);
  setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentBlack);
  setColour(juce::TextEditor::textColourId, juce::Colour(TailwindColors::valueText));

  setColour(juce::ComboBox::textColourId, juce::Colour(TailwindColors::labelText));
  setColour(juce::ComboBox::outlineColourId, juce::Colour(TailwindColors::panelBorder));
  setColour(juce::ComboBox::arrowColourId, juce::Colour(TailwindColors::accentBright));

  setColour(juce::PopupMenu::backgroundColourId, juce::Colour(TailwindColors::panelBg));
  setColour(juce::PopupMenu::textColourId, juce::Colour(TailwindColors::labelText));
  setColour(juce::PopupMenu::highlightedBackgroundColourId,
            juce::Colour(TailwindColors::accentWarm).withAlpha(0.24f));
  setColour(juce::PopupMenu::highlightedTextColourId, juce::Colour(TailwindColors::accentBright));
}

void TailwindLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                           int x,
                                           int y,
                                           int width,
                                           int height,
                                           float sliderPos,
                                           float rotaryStartAngle,
                                           float rotaryEndAngle,
                                           juce::Slider& slider) {
  // Geometry
  const float diameter = (static_cast<float>(juce::jmin(width, height)) - 10.0f) * 0.82f;
  const float radius = diameter * 0.5f;
  const float centreX = static_cast<float>(x) + static_cast<float>(width) * 0.5f;
  const float centreY = static_cast<float>(y) + static_cast<float>(height) * 0.5f;
  const float rx = centreX - radius;
  const float ry = centreY - radius;

  const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

  const auto meterPeak = static_cast<float>(slider.getProperties()["tailwindMeterPeak"]);
  const auto showMeter = static_cast<bool>(slider.getProperties()["tailwindShowMeter"]);
  const auto meterPos = TailwindColors::peakToMeterNormalised(meterPeak);
  const auto meterAngle = rotaryStartAngle + meterPos * (rotaryEndAngle - rotaryStartAngle);

  if (showMeter) {
    const float meterArcRadius = radius + 10.0f;
    const float meterArcThickness = 2.5f;

    juce::Path meterArcBg;
    meterArcBg.addCentredArc(centreX,
                             centreY,
                             meterArcRadius,
                             meterArcRadius,
                             0.0f,
                             rotaryStartAngle,
                             rotaryEndAngle,
                             true);
    g.setColour(juce::Colour(TailwindColors::knobTrackBg).brighter(0.1f));
    g.strokePath(meterArcBg,
                 juce::PathStrokeType(meterArcThickness,
                                      juce::PathStrokeType::curved,
                                      juce::PathStrokeType::rounded));

    if (meterPos > 0.0f) {
      juce::Path meterArc;
      meterArc.addCentredArc(centreX,
                             centreY,
                             meterArcRadius,
                             meterArcRadius,
                             0.0f,
                             rotaryStartAngle,
                             meterAngle,
                             true);
      g.setColour(TailwindColors::meterColourForPeak(meterPeak));
      g.strokePath(meterArc,
                   juce::PathStrokeType(meterArcThickness,
                                        juce::PathStrokeType::curved,
                                        juce::PathStrokeType::rounded));
    }
  }

  // ---- Arc track (background) ----
  const float arcRadius = radius + 4.0f;
  const float arcThickness = 3.0f;

  juce::Path arcBg;
  arcBg.addCentredArc(
      centreX, centreY, arcRadius, arcRadius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
  g.setColour(juce::Colour(TailwindColors::knobTrackBg));
  g.strokePath(arcBg,
               juce::PathStrokeType(
                   arcThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

  // ---- Arc fill (active) ----
  if (sliderPos > 0.0f) {
    juce::Path arcFill;
    arcFill.addCentredArc(
        centreX, centreY, arcRadius, arcRadius, 0.0f, rotaryStartAngle, angle, true);

    juce::ColourGradient arcGrad(juce::Colour(TailwindColors::knobArc),
                                 centreX - arcRadius,
                                 centreY,
                                 juce::Colour(TailwindColors::knobArcBright),
                                 centreX + arcRadius,
                                 centreY,
                                 false);
    g.setGradientFill(arcGrad);
    g.strokePath(arcFill,
                 juce::PathStrokeType(
                     arcThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
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
    juce::ColourGradient bodyGrad(juce::Colour(TailwindColors::knobBodyLight),
                                  centreX,
                                  ry,
                                  juce::Colour(TailwindColors::knobBody),
                                  centreX,
                                  ry + diameter,
                                  false);
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
    g.drawEllipse(rx + inset, ry + inset, diameter - inset * 2.0f, diameter - inset * 2.0f, 0.8f);
  }

  // ---- Pointer / notch ----
  {
    juce::Path pointer;
    const float pointerLength = radius * 0.58f;
    const float pointerThickness = 2.5f;
    pointer.addRoundedRectangle(
        -pointerThickness * 0.5f, -radius + 6.0f, pointerThickness, pointerLength, 1.0f);

    pointer.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(juce::Colour(TailwindColors::knobPointer));
    g.fillPath(pointer);
  }

  // ---- Centre dot ----
  {
    const float dotRadius = 2.5f;
    g.setColour(juce::Colour(TailwindColors::knobPointer).withAlpha(0.6f));
    g.fillEllipse(centreX - dotRadius, centreY - dotRadius, dotRadius * 2.0f, dotRadius * 2.0f);
  }
}

void TailwindLookAndFeel::drawToggleButton(juce::Graphics& g,
                                           juce::ToggleButton& button,
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

void TailwindLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label) {
  auto bounds = label.getLocalBounds().toFloat();

  // Draw rounded background/border for slider value readout labels
  // We detect these by checking if the parent is a Slider
  if (dynamic_cast<juce::Slider*>(label.getParentComponent()) != nullptr) {
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

    g.setColour(label.findColour(juce::Label::textColourId).withMultipliedAlpha(alpha));
    g.setFont(font);

    auto textArea = getLabelBorderSize(label).subtractedFrom(label.getLocalBounds());
    g.drawFittedText(label.getText(),
                     textArea,
                     label.getJustificationType(),
                     juce::jmax(1, (int)(textArea.getHeight() / font.getHeight())),
                     label.getMinimumHorizontalScale());
  }
}

juce::Label* TailwindLookAndFeel::createSliderTextBox(juce::Slider& slider) {
  juce::ignoreUnused(slider);

  auto* label = new TailwindSliderLabel();
  label->setJustificationType(juce::Justification::centred);
  label->setEditable(false, true, false);
  label->setBorderSize(juce::BorderSize<int>(0));

  label->setColour(juce::Label::textColourId, juce::Colour(TailwindColors::valueText));
  label->setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
  label->setColour(juce::Label::outlineColourId, juce::Colours::transparentBlack);
  // Editor colours (when user clicks to type)
  label->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xff222020));
  label->setColour(juce::TextEditor::outlineColourId, juce::Colour(TailwindColors::panelBorder));
  label->setColour(juce::TextEditor::highlightColourId, juce::Colour(0x00000000));
  label->setColour(juce::TextEditor::highlightedTextColourId,
                   juce::Colour(TailwindColors::valueText));
  label->setColour(juce::TextEditor::textColourId, juce::Colour(TailwindColors::valueText));

  return label;
}

juce::Slider::SliderLayout TailwindLookAndFeel::getSliderLayout(juce::Slider& slider) {
  auto layout = LookAndFeel_V4::getSliderLayout(slider);

  if (slider.isBar())
    return layout;

  auto bounds = slider.getLocalBounds();
  layout.sliderBounds = bounds.withTrimmedTop(6).withTrimmedBottom(28);
  layout.textBoxBounds =
      juce::Rectangle<int>(bounds.getX() + 8, bounds.getBottom() - 26, bounds.getWidth() - 16, 22);
  return layout;
}

void TailwindLookAndFeel::drawButtonBackground(juce::Graphics& g,
                                               juce::Button& button,
                                               const juce::Colour& backgroundColour,
                                               bool shouldDrawButtonAsHighlighted,
                                               bool shouldDrawButtonAsDown) {
  if (!isTopBarButton(button)) {
    LookAndFeel_V4::drawButtonBackground(
        g, button, backgroundColour, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
    return;
  }

  auto bounds = button.getLocalBounds().toFloat().reduced(0.5f);
  const auto cornerSize = 4.5f;
  const bool isOn = button.getToggleState();
  const bool isPressed = isOn || shouldDrawButtonAsDown;

  juce::ColourGradient fillGradient(
      isPressed ? juce::Colour(TailwindColors::accentWarm).withAlpha(0.26f)
                : juce::Colour(TailwindColors::panelBg).brighter(0.09f),
      0.0f,
      bounds.getY(),
      isPressed ? juce::Colour(TailwindColors::accentWarm).withAlpha(0.14f)
                : juce::Colour(TailwindColors::panelBg).brighter(0.02f),
      0.0f,
      bounds.getBottom(),
      false);
  g.setGradientFill(fillGradient);
  g.fillRoundedRectangle(bounds, cornerSize);

  auto borderColour = isPressed ? juce::Colour(TailwindColors::accentWarm)
                                : juce::Colour(TailwindColors::panelBorder).brighter(0.12f);
  if (shouldDrawButtonAsHighlighted && !isPressed)
    borderColour = borderColour.brighter(0.25f);

  g.setColour(borderColour);
  g.drawRoundedRectangle(bounds, cornerSize, 1.0f);

  if (shouldDrawButtonAsHighlighted && !isPressed) {
    g.setColour(juce::Colour(0x14ffffff));
    g.fillRoundedRectangle(bounds.reduced(1.0f), cornerSize - 0.8f);
  }
}

void TailwindLookAndFeel::drawButtonText(juce::Graphics& g,
                                         juce::TextButton& button,
                                         bool shouldDrawButtonAsHighlighted,
                                         bool shouldDrawButtonAsDown) {
  if (!isTopBarButton(button)) {
    LookAndFeel_V4::drawButtonText(
        g, button, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
    return;
  }

  const bool isOn = button.getToggleState() || shouldDrawButtonAsDown;
  auto textColour =
      isOn ? juce::Colour(TailwindColors::accentBright) : juce::Colour(TailwindColors::labelText);

  if (shouldDrawButtonAsHighlighted && !isOn)
    textColour = textColour.brighter(0.15f);

  g.setColour(textColour);
  g.setFont(getTextButtonFont(button, button.getHeight()));
  g.drawFittedText(button.getButtonText(),
                   button.getLocalBounds().reduced(2, 0),
                   juce::Justification::centred,
                   1);
}

void TailwindLookAndFeel::drawComboBox(juce::Graphics& g,
                                       int width,
                                       int height,
                                       bool isButtonDown,
                                       int buttonX,
                                       int buttonY,
                                       int buttonW,
                                       int buttonH,
                                       juce::ComboBox& box) {
  if (!isTopBarPreset(box)) {
    LookAndFeel_V4::drawComboBox(
        g, width, height, isButtonDown, buttonX, buttonY, buttonW, buttonH, box);
    return;
  }

  auto bounds =
      juce::Rectangle<float>(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height))
          .reduced(0.5f);
  const auto cornerSize = 4.5f;
  const bool highlighted = box.isMouseOver(true);
  const bool active = isButtonDown || box.hasKeyboardFocus(true) || box.isPopupActive();

  juce::ColourGradient fillGradient(active ? juce::Colour(TailwindColors::panelBg).brighter(0.15f)
                                           : juce::Colour(TailwindColors::panelBg).brighter(0.1f),
                                    0.0f,
                                    bounds.getY(),
                                    juce::Colour(TailwindColors::panelBg).brighter(0.03f),
                                    0.0f,
                                    bounds.getBottom(),
                                    false);
  g.setGradientFill(fillGradient);
  g.fillRoundedRectangle(bounds, cornerSize);

  g.setColour(active
                  ? juce::Colour(TailwindColors::accentWarm)
                  : juce::Colour(TailwindColors::panelBorder).brighter(highlighted ? 0.25f : 0.1f));
  g.drawRoundedRectangle(bounds, cornerSize, 1.0f);

  auto arrowZone = juce::Rectangle<float>(static_cast<float>(buttonX),
                                          static_cast<float>(buttonY),
                                          static_cast<float>(buttonW),
                                          static_cast<float>(buttonH));
  g.setColour(juce::Colour(TailwindColors::panelBorder).withAlpha(0.8f));
  g.drawLine(arrowZone.getX(),
             arrowZone.getY() + 3.0f,
             arrowZone.getX(),
             arrowZone.getBottom() - 3.0f,
             1.0f);

  juce::Path arrow;
  const auto arrowCentreX = arrowZone.getCentreX();
  const auto arrowCentreY = arrowZone.getCentreY() + 0.5f;
  constexpr float arrowHalfWidth = 4.0f;
  constexpr float arrowHeight = 2.8f;
  arrow.startNewSubPath(arrowCentreX - arrowHalfWidth, arrowCentreY - 1.0f);
  arrow.lineTo(arrowCentreX, arrowCentreY + arrowHeight);
  arrow.lineTo(arrowCentreX + arrowHalfWidth, arrowCentreY - 1.0f);

  g.setColour(active ? juce::Colour(TailwindColors::accentBright)
                     : juce::Colour(TailwindColors::labelText));
  g.strokePath(
      arrow,
      juce::PathStrokeType(1.6f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
}

juce::Font TailwindLookAndFeel::getTextButtonFont(juce::TextButton& button, int buttonHeight) {
  if (button.getComponentID() == topBarButtonComponentId)
    return juce::Font(13.0f, juce::Font::bold);

  return juce::Font(static_cast<float>(juce::jmax(10, buttonHeight - 12)), juce::Font::bold);
}

juce::Font TailwindLookAndFeel::getComboBoxFont(juce::ComboBox& box) {
  juce::ignoreUnused(box);
  return juce::Font(13.0f, juce::Font::plain);
}
