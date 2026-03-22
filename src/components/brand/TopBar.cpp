#include "TopBar.h"
#include "BinaryData.h"

TopBar::TopBar() {
  // Load logo image
  int logoDataSize = 0;
  const char *logoData = BinaryData::getNamedResource("logo_png", logoDataSize);
  if (logoData != nullptr && logoDataSize > 0) {
    logo = juce::ImageFileFormat::loadFrom(logoData,
                                           static_cast<size_t>(logoDataSize));
  }
}

void TopBar::paint(juce::Graphics &g) {
  auto bounds = getLocalBounds().toFloat();

  // Background — subtle warm gradient
  {
    juce::ColourGradient bg(juce::Colour(TailwindColors::topBarBg), 0.0f, 0.0f,
                            juce::Colour(TailwindColors::background),
                            bounds.getWidth(), 0.0f, false);
    g.setGradientFill(bg);
    g.fillRect(bounds);
  }

  // Draw logo if loaded (left side)
  if (logo.isValid()) {
    const int logoHeight = getHeight() - 20;
    const int logoWidth = logo.getWidth() * logoHeight / logo.getHeight();
    const int logoX = 15;
    const int logoY = (getHeight() - logoHeight) / 2;
    g.drawImage(logo, logoX, logoY, logoWidth, logoHeight, 0, 0,
                logo.getWidth(), logo.getHeight());
  }

  // Plugin name on the right side
  {
    auto textBounds = getLocalBounds().reduced(16, 0);
    g.setColour(juce::Colour(TailwindColors::titleText));
    g.setFont(juce::Font(15.0f, juce::Font::bold));
    g.drawText("TAILWIND", textBounds, juce::Justification::centredRight);
  }

  // Subtitle
  {
    auto subtitleBounds = getLocalBounds().reduced(16, 0);
    subtitleBounds.removeFromRight(100);
    g.setColour(juce::Colour(TailwindColors::sectionTitle));
    g.setFont(juce::Font(10.0f));
    g.drawText("Long Tail Reverb", subtitleBounds,
               juce::Justification::centredRight);
  }

  // Bottom border — warm accent line
  g.setColour(juce::Colour(TailwindColors::accentWarm).withAlpha(0.4f));
  g.drawLine(0.0f, bounds.getBottom() - 1.0f, bounds.getWidth(),
             bounds.getBottom() - 1.0f, 1.0f);
}

void TopBar::resized() {
  // No child components to layout
}
