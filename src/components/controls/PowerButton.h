#pragma once

#include "ui/TailwindColors.h"
#include <juce_gui_basics/juce_gui_basics.h>

/**
 * A small power-symbol toggle button styled like a hardware on/off switch.
 *
 * Renders the IEC 5009 power icon drawn from an inline SVG. When the toggle
 * is ON (active) the icon glows in onColour; when OFF it is dimmed to
 * offColour at 50% alpha.
 *
 * The underlying juce::ToggleButton is publicly accessible so you can attach
 * an APVTS ButtonAttachment to it directly.
 */
class PowerButton : public juce::Component {
public:
  PowerButton() {
    addAndMakeVisible(toggle);
    toggle.setLookAndFeel(&lnf);
    rebuildIcon();
  }

  ~PowerButton() override {
    toggle.setLookAndFeel(nullptr);
  }

  /** Access the underlying toggle for APVTS attachment. */
  juce::ToggleButton& getToggle() {
    return toggle;
  }

  /** Set the callback invoked when the toggle state changes. */
  void setOnClick(std::function<void()> fn) {
    toggle.onClick = std::move(fn);
  }

  /** Customise colours. Call before the component is shown, or call repaint() after. */
  void setOnColour(juce::Colour c) {
    onColour = c;
    rebuildIcon();
    repaint();
  }
  void setOffColour(juce::Colour c) {
    offColour = c;
    rebuildIcon();
    repaint();
  }
  void setBackgroundColour(juce::Colour c) {
    bgColour = c;
    repaint();
  }
  void setBorderColour(juce::Colour c) {
    borderColour = c;
    repaint();
  }

  void resized() override {
    toggle.setBounds(getLocalBounds());
  }

private:
  // ---- Inline SVG source (IEC 5009 power symbol) ----
  // stroke must be "black" so replaceColour() can swap it at paint time.
  static constexpr const char* powerSvg = R"SVG(
    <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24"
         viewBox="0 0 24 24" fill="none" stroke="black"
         stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round">
      <path d="M18.36 6.64a9 9 0 1 1-12.73 0"></path>
      <line x1="12" y1="2" x2="12" y2="12"></line>
    </svg>
  )SVG";

  void rebuildIcon() {
    auto xml = juce::XmlDocument::parse(powerSvg);
    if (xml != nullptr)
      iconDrawable = juce::Drawable::createFromSVG(*xml);
  }

  // ---- Colours ----
  // ON  = bypassed / inactive → muted warm off-white at 50% alpha
  // OFF = active              → ice blue glow
  juce::Colour onColour{TailwindColors::freezeOn};
  juce::Colour offColour{TailwindColors::labelText};
  juce::Colour bgColour{TailwindColors::panelBg};
  juce::Colour borderColour{TailwindColors::panelBorder};

  // ---- Members ----
  juce::ToggleButton toggle;
  std::unique_ptr<juce::Drawable> iconDrawable;

  // ---- Private LookAndFeel that draws the power button ----
  struct PowerLnF : public juce::LookAndFeel_V4 {
    PowerButton* owner = nullptr;
    explicit PowerLnF(PowerButton* o) : owner(o) {}

    void drawToggleButton(juce::Graphics& g,
                          juce::ToggleButton& button,
                          bool /*highlighted*/,
                          bool /*down*/) override {
      if (owner == nullptr)
        return;

      auto bounds = button.getLocalBounds().toFloat();
      const bool isOn = button.getToggleState();

      if (owner->iconDrawable != nullptr) {
        // ON (active) = ice blue glow; OFF (inactive) = dimmed warm white
        auto iconColour = isOn ? owner->onColour : owner->offColour.withAlpha(0.5f);
        owner->iconDrawable->replaceColour(juce::Colours::black, iconColour);
        owner->iconDrawable->drawWithin(g, bounds, juce::RectanglePlacement::centred, 1.0f);
        // Reset to black so the next paint picks up the right replacement
        owner->iconDrawable->replaceColour(iconColour, juce::Colours::black);
      }
    }
  };

  PowerLnF lnf{this};

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PowerButton)
};
