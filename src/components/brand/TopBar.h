#pragma once

#include "ui/TailwindColors.h"
#include <juce_gui_basics/juce_gui_basics.h>

#include <functional>

class TopBar : public juce::Component {
public:
  TopBar();
  ~TopBar() override = default;

  void paint(juce::Graphics &g) override;
  void resized() override;
  void setActiveABSlot(bool isSlotA);
  void setPresetNames(const juce::StringArray &presetNames);
  void setSelectedPresetName(const juce::String &presetName);
  juce::Component *getOptionsTargetComponent();

  std::function<void()> onSelectSlotA;
  std::function<void()> onSelectSlotB;
  std::function<void(const juce::String &presetName)> onPresetSelected;
  std::function<void()> onShowOptionsMenu;

private:
  // Logo
  juce::Image logo;
  juce::ComboBox presetBox;
  juce::TextButton slotAButton{"A"};
  juce::TextButton slotBButton{"B"};
  juce::TextButton optionsButton{"..."};

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopBar)
};
