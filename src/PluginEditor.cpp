#include "PluginEditor.h"
#include "FaustParams.h"
#include "ui/TailwindColors.h"

TailwindAudioProcessorEditor::TailwindAudioProcessorEditor(
    TailwindAudioProcessor &p)
    : AudioProcessorEditor(&p),
      // MAIN
      mixKnob(p.apvts, FaustParamIDs::mix, "MIX", " %", true),
      decayKnob(p.apvts, FaustParamIDs::decay, "DECAY", " %", true),
      preDelayKnob(p.apvts, FaustParamIDs::preDelayMs, "PRE-DELAY", " ms"),
      diffusionKnob(p.apvts, FaustParamIDs::diffusion, "DIFFUSION", " %", true),
      // TONE
      dampingKnob(p.apvts, FaustParamIDs::damping, "DAMPING", " %", true),
      lowDampKnob(p.apvts, FaustParamIDs::lowDamp, "LOW DAMP", " %", true),
      lowCutKnob(p.apvts, FaustParamIDs::lowCutHz, "LOW CUT", " Hz"),
      highCutKnob(p.apvts, FaustParamIDs::highCutHz, "HIGH CUT", " Hz"),
      // MODULATION
      modRateKnob(p.apvts, FaustParamIDs::modRateHz, "RATE", " Hz"),
      modDepthKnob(p.apvts, FaustParamIDs::modDepth, "DEPTH", " %", true),
      // CHARACTER
      saturationKnob(p.apvts, FaustParamIDs::saturation, "SATURATION", " %",
                     true),
      freezeKnob(p.apvts, FaustParamIDs::freeze, "FREEZE", " %", true),
      freezeOnBtn(p.apvts, FaustParamIDs::freezeOn),
      // GAIN STAGING
      inputGainKnob(p.apvts, FaustParamIDs::inputGainDb, "INPUT", " dB"),
      outputGainKnob(p.apvts, FaustParamIDs::outputGainDb, "OUTPUT", " dB") {

  // Apply custom look and feel
  setLookAndFeel(&tailwindLnf);

  // Top bar
  addAndMakeVisible(topBar);

  // Main section knobs
  addAndMakeVisible(mixKnob);
  addAndMakeVisible(decayKnob);
  addAndMakeVisible(preDelayKnob);
  addAndMakeVisible(diffusionKnob);

  // Tone section knobs
  addAndMakeVisible(dampingKnob);
  addAndMakeVisible(lowDampKnob);
  addAndMakeVisible(lowCutKnob);
  addAndMakeVisible(highCutKnob);

  // Modulation section knobs
  addAndMakeVisible(modRateKnob);
  addAndMakeVisible(modDepthKnob);

  // Character section knobs
  addAndMakeVisible(saturationKnob);
  addAndMakeVisible(freezeKnob);
  addAndMakeVisible(freezeOnBtn);

  // Gain staging section knobs
  addAndMakeVisible(inputGainKnob);
  addAndMakeVisible(outputGainKnob);

  setResizable(true, true);
  setResizeLimits(minEditorWidth, minEditorHeight, 1280, 780);
  setSize(900, 560);
}

TailwindAudioProcessorEditor::~TailwindAudioProcessorEditor() {
  setLookAndFeel(nullptr);
}

void TailwindAudioProcessorEditor::paint(juce::Graphics &g) {
  // Main background
  g.fillAll(juce::Colour(TailwindColors::background));

  // Compute section bounds (same as resized) for painting panels
  auto bounds = getLocalBounds();
  bounds.removeFromTop(50); // topBar
  bounds.reduce(12, 8);

  const int topRowHeight =
      juce::jlimit(280, 420, (bounds.getHeight() * 2) / 3);
  const int bottomRowHeight = bounds.getHeight() - topRowHeight - 8;

  auto topRow = bounds.removeFromTop(topRowHeight);
  bounds.removeFromTop(8); // gap
  auto bottomRow = bounds.removeFromTop(bottomRowHeight);

  // Top row: MAIN (4 knobs), TONE (4 knobs), MODULATION (2 knobs)
  const int sectionGap = 8;
  const int mainW = (topRow.getWidth() - sectionGap * 2) * 2 / 5;
  const int toneW = (topRow.getWidth() - sectionGap * 2) * 2 / 5;
  auto mainBounds = topRow.removeFromLeft(mainW);
  topRow.removeFromLeft(sectionGap);
  auto toneBounds = topRow.removeFromLeft(toneW);
  topRow.removeFromLeft(sectionGap);
  auto modBounds = topRow;

  // Draw section panels
  drawSectionPanel(g, mainBounds, "MAIN");
  drawSectionPanel(g, toneBounds, "TONE");
  drawSectionPanel(g, modBounds, "MODULATION");
  const int lowerGap = 8;
  const int characterWidth = (bottomRow.getWidth() - lowerGap) * 3 / 5;
  auto characterBounds = bottomRow.removeFromLeft(characterWidth);
  bottomRow.removeFromLeft(lowerGap);
  auto gainBounds = bottomRow;

  drawSectionPanel(g, characterBounds, "CHARACTER");
  drawSectionPanel(g, gainBounds, "GAIN STAGING");
}

void TailwindAudioProcessorEditor::resized() {
  auto bounds = getLocalBounds();

  // Top bar
  topBar.setBounds(bounds.removeFromTop(50));

  // Content area with padding
  bounds.reduce(12, 8);

  const int topRowHeight =
      juce::jlimit(280, 420, (bounds.getHeight() * 2) / 3);
  const int bottomRowHeight = bounds.getHeight() - topRowHeight - 8;

  auto topRow = bounds.removeFromTop(topRowHeight);
  bounds.removeFromTop(8); // gap between rows
  auto bottomRow = bounds.removeFromTop(bottomRowHeight);

  // ---- Top row section widths ----
  const int sectionGap = 8;
  const int topRowContentWidth = topRow.getWidth() - sectionGap * 2;
  const int mainW = topRowContentWidth * 2 / 5;
  const int toneW = topRowContentWidth * 2 / 5;

  auto mainBounds = topRow.removeFromLeft(mainW);
  topRow.removeFromLeft(sectionGap);
  auto toneBounds = topRow.removeFromLeft(toneW);
  topRow.removeFromLeft(sectionGap);
  auto modBounds = topRow;

  const int lowerGap = 8;
  const int characterWidth = (bottomRow.getWidth() - lowerGap) * 3 / 5;
  auto characterBounds = bottomRow.removeFromLeft(characterWidth);
  bottomRow.removeFromLeft(lowerGap);
  auto gainBounds = bottomRow;

  // ---- MAIN section (2x2 grid) ----
  {
    auto area = mainBounds.reduced(8);
    area.removeFromTop(24); // space for section title

    const int hGap = 8;
    const int vGap = 16;
    const int knobW = (area.getWidth() - hGap) / 2;
    const int knobH = (area.getHeight() - vGap) / 2;

    auto row1 = area.removeFromTop(knobH);
    area.removeFromTop(vGap);
    auto row2 = area;

    mixKnob.setBounds(row1.removeFromLeft(knobW));
    row1.removeFromLeft(hGap);
    decayKnob.setBounds(row1);
    preDelayKnob.setBounds(row2.removeFromLeft(knobW));
    row2.removeFromLeft(hGap);
    diffusionKnob.setBounds(row2);
  }

  // ---- TONE section (2x2 grid) ----
  {
    auto area = toneBounds.reduced(8);
    area.removeFromTop(24);

    const int hGap = 8;
    const int vGap = 16;
    const int knobW = (area.getWidth() - hGap) / 2;
    const int knobH = (area.getHeight() - vGap) / 2;

    auto row1 = area.removeFromTop(knobH);
    area.removeFromTop(vGap);
    auto row2 = area;

    dampingKnob.setBounds(row1.removeFromLeft(knobW));
    row1.removeFromLeft(hGap);
    lowDampKnob.setBounds(row1);
    lowCutKnob.setBounds(row2.removeFromLeft(knobW));
    row2.removeFromLeft(hGap);
    highCutKnob.setBounds(row2);
  }

  // ---- MODULATION section (2x1 vertical) ----
  {
    auto area = modBounds.reduced(8);
    area.removeFromTop(24);

    const int vGap = 16;
    const int knobH = (area.getHeight() - vGap) / 2;

    modRateKnob.setBounds(area.removeFromTop(knobH));
    area.removeFromTop(vGap);
    modDepthKnob.setBounds(area);
  }

  // ---- CHARACTER section (horizontal) ----
  {
    auto area = characterBounds.reduced(8);
    area.removeFromTop(24);

    const int contentHeight = juce::jmin(220, area.getHeight());
    area.setHeight(contentHeight);

    const int sidePadding = 12;
    const int availableWidth = juce::jmax(0, area.getWidth() - sidePadding * 2);
    const int freezeBtnW = juce::jlimit(100, 160, availableWidth / 3);
    const int knobW = juce::jlimit(96, 160, juce::jmin(availableWidth / 3, availableWidth - freezeBtnW));

    auto contentArea = area.reduced(sidePadding, 0);
    auto leftKnobArea = contentArea.removeFromLeft(knobW);
    auto rightButtonArea = contentArea.removeFromRight(freezeBtnW);
    auto centreArea = contentArea;

    saturationKnob.setBounds(leftKnobArea);

    auto freezeKnobArea = centreArea.withSizeKeepingCentre(knobW, contentHeight);
    freezeKnob.setBounds(freezeKnobArea);

    // Centre the freeze button vertically in remaining space
    auto btnArea = rightButtonArea;
    const int btnH = 36;
    btnArea.setY(btnArea.getY() + (btnArea.getHeight() - btnH) / 2);
    btnArea.setHeight(btnH);
    freezeOnBtn.setBounds(btnArea);
  }

  // ---- GAIN STAGING section (2x1 vertical) ----
  {
    auto area = gainBounds.reduced(8);
    area.removeFromTop(24);

    const int contentHeight = juce::jmin(180, area.getHeight());
    area.setHeight(contentHeight);

    const int hGap = 12;
    const int knobW = (area.getWidth() - hGap) / 2;

    inputGainKnob.setBounds(area.removeFromLeft(knobW));
    area.removeFromLeft(hGap);
    outputGainKnob.setBounds(area);
  }
}

void TailwindAudioProcessorEditor::drawSectionPanel(juce::Graphics &g,
                                                    juce::Rectangle<int> bounds,
                                                    const juce::String &title) {
  auto fb = bounds.toFloat();

  // Panel background
  g.setColour(juce::Colour(TailwindColors::panelBg));
  g.fillRoundedRectangle(fb, 6.0f);

  // Panel border
  g.setColour(juce::Colour(TailwindColors::panelBorder));
  g.drawRoundedRectangle(fb.reduced(0.5f), 6.0f, 1.0f);

  // Section title
  auto titleBounds = bounds.reduced(12, 0);
  titleBounds.setHeight(24);
  titleBounds.setY(bounds.getY() + 2);

  g.setColour(juce::Colour(TailwindColors::sectionTitle));
  g.setFont(juce::Font(11.0f, juce::Font::bold));
  g.drawText(title, titleBounds, juce::Justification::centredLeft);
}
