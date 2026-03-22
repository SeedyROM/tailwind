#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

/**
 * Tailwind UI colour palette — warm analog aesthetic.
 *
 * Dark charcoal base with warm amber/orange accents,
 * inspired by hardware studio gear.
 */
namespace TailwindColors {

// ---- Backgrounds ----
inline constexpr juce::uint32 background = 0xff1e1c1a; // Main background
inline constexpr juce::uint32 panelBg = 0xff2a2725;    // Section panels
inline constexpr juce::uint32 panelBorder =
    0xff3a3632; // Panel border / subtle dividers
inline constexpr juce::uint32 topBarBg =
    0xff1a1816; // Top bar (slightly darker)

// ---- Knob ----
inline constexpr juce::uint32 knobBody = 0xff3a3632;      // Knob fill
inline constexpr juce::uint32 knobBodyLight = 0xff4a4642; // Knob gradient top
inline constexpr juce::uint32 knobOutline = 0xff2a2725;   // Knob border
inline constexpr juce::uint32 knobPointer = 0xffe8a96a; // Knob pointer / notch
inline constexpr juce::uint32 knobTrackBg = 0xff2a2725; // Arc background
inline constexpr juce::uint32 knobArc = 0xffd4874d; // Active arc (warm amber)
inline constexpr juce::uint32 knobArcBright = 0xffe8a96a; // Arc highlight end

// ---- Text ----
inline constexpr juce::uint32 labelText =
    0xffc8bfb4; // Label text (warm off-white)
inline constexpr juce::uint32 valueText = 0xffe8a96a; // Value readout (amber)
inline constexpr juce::uint32 sectionTitle =
    0xff8a7e72; // Section header text (muted warm)
inline constexpr juce::uint32 titleText = 0xffd4c5b0; // Plugin title text

// ---- Freeze / Special ----
inline constexpr juce::uint32 freezeOff = 0xff4a4642; // Freeze button inactive
inline constexpr juce::uint32 freezeOn =
    0xff7ab8d4; // Freeze button active (ice blue)
inline constexpr juce::uint32 freezeGlow =
    0x407ab8d4; // Freeze glow (transparent ice blue)

// ---- Accent ----
inline constexpr juce::uint32 accentWarm = 0xffd4874d;   // Primary warm accent
inline constexpr juce::uint32 accentBright = 0xffe8a96a; // Bright warm accent

} // namespace TailwindColors
