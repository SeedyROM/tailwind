#include "TopBar.h"
#include "BinaryData.h"

TopBar::TopBar() {
  // Load logo image
  int logoDataSize = 0;
  const char *logoData = BinaryData::getNamedResource("logo_png", logoDataSize);
  if (logoData != nullptr && logoDataSize > 0) {
    logo = juce::ImageFileFormat::loadFrom(logoData, static_cast<size_t>(logoDataSize));
  }
}

void TopBar::paint(juce::Graphics &g) {
  // Draw background
  g.fillAll(juce::Colour(0xff1a1a1a));

  // Draw logo if loaded (left side)
  if (logo.isValid()) {
    const int logoHeight = getHeight() - 20;
    const int logoWidth = logo.getWidth() * logoHeight / logo.getHeight();
    const int logoX = 15;
    const int logoY = (getHeight() - logoHeight) / 2;
    g.drawImage(logo, logoX, logoY, logoWidth, logoHeight, 0, 0, logo.getWidth(),
                logo.getHeight());
  }

  // Draw border at bottom
  g.setColour(juce::Colour(0xff333333));
  g.drawLine(0, getHeight() - 1, getWidth(), getHeight() - 1, 1.0f);
}

void TopBar::resized() {
  // No controls to layout in this simplified version
}
