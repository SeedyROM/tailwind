# Presets, A/B Compare, and State Versioning Plan

## Goal

Add a clean state backbone for:

- session-safe A/B compare
- factory presets
- user presets saved as XML
- future-safe state versioning

This should stay simple, JUCE-native, and use APVTS/ValueTree as the main source of truth.

## Core Rules

- APVTS remains the live state source of truth.
- A/B compare is session-only and ephemeral.
- Preset files save only the active canonical plugin state.
- DAW session state saves canonical state plus A/B snapshots.
- No extra compatibility layer beyond JUCE XML/ValueTree.
- XML is the preset format.

## Architecture Overview

### Live State

The current live plugin state comes from:

- `juce::AudioProcessorValueTreeState apvts`

All parameter edits update APVTS.

### Versioned Canonical State

Introduce a canonical wrapped state format containing:

- `schemaVersion`
- `pluginVersion`
- `pluginState`

Where `pluginState` is the APVTS state tree.

This wrapped state is used for:

- DAW session save/load
- preset save/load

### A/B State

A/B lives only inside the plugin instance and DAW session data.

Processor-owned state:

- `slotAState`
- `slotBState`
- `activeSlot`

A/B is not stored in user preset XML files.

### Presets

Presets come in two kinds:

- factory presets, defined in code
- user presets, saved as XML files on disk

User preset location should use JUCE app data paths, e.g.:

- macOS: `~/Library/Application Support/SeedyROM/Tailwind/Presets`

## Implementation Plan

## Phase 1: Versioned State Backbone

### Files

- `src/PluginProcessor.h`
- `src/PluginProcessor.cpp`

### Add

- `static constexpr int stateSchemaVersion = 1;`
- helper to create wrapped plugin state
- helper to unwrap/migrate saved state
- helper to migrate old schema versions forward

### Save Format

Wrapped state should contain:

- `schemaVersion`
- `pluginVersion`
- `pluginState`

### Tasks

- Add `createWrappedPluginState()`
- Add `extractPluginStateFromSavedTree(...)`
- Add `migrateStateTree(...)`
- Update `getStateInformation()` to save wrapped state
- Update `setStateInformation()` to:
  - load legacy unwrapped state if needed
  - load wrapped state if present
  - migrate before applying

### Notes

- `pluginVersion` should come from project version metadata
- `schemaVersion` is independent and only changes when serialized structure changes

## Phase 2: A/B Compare Engine

### Files

- `src/PluginProcessor.h`
- `src/PluginProcessor.cpp`

### Add

Processor state:

- `juce::ValueTree slotAState;`
- `juce::ValueTree slotBState;`
- `enum class ABSlot { A, B };`
- `ABSlot activeSlot = ABSlot::A;`
- restore/update guard flag

### Methods

- `juce::ValueTree captureCurrentState() const;`
- `void applyStateToApvts(const juce::ValueTree&);`
- `void initialiseABSlotsFromCurrentState();`
- `void setActiveABSlot(ABSlot);`
- `ABSlot getActiveABSlot() const;`
- `void copyABSlot(ABSlot from, ABSlot to);`
- `void swapABSlots();`

### Behavior

- both slots initialize from current state on first open
- active slot defaults to `A`
- switching A/B applies the selected slot immediately
- edits affect the active slot only
- inactive slot remains unchanged unless copied/swapped/reset

### Tracking Edits

Need a way for the active slot snapshot to stay current when parameters change.

Recommended options:

- attach an APVTS listener path and refresh the active slot snapshot when state changes
- or capture current APVTS state after relevant edits/actions

Preferred approach:

- lightweight APVTS/state listener in processor so active slot is always current

## Phase 3: Save A/B In DAW Sessions Only

### Files

- `src/PluginProcessor.cpp`

### Extend Wrapped Session State

For DAW session state only, save:

- `schemaVersion`
- `pluginVersion`
- `pluginState`
- `activeABSlot`
- `slotAState`
- `slotBState`

### Tasks

- create DAW-session save wrapper that includes A/B
- update DAW-session load path to restore:
  - active slot
  - slot A
  - slot B
  - current live state

### Legacy Handling

If old session data does not include A/B:

- restore plugin state normally
- initialize both A and B from restored state
- set active slot to `A`

## Phase 4: Preset Manager

### Files

- `src/presets/TailwindPresetManager.h`
- `src/presets/TailwindPresetManager.cpp`
- optional `src/presets/FactoryPresets.h`

### Responsibilities

- resolve preset directory
- list factory presets
- list user presets
- load preset XML
- save preset XML
- overwrite preset
- delete preset
- reveal preset folder

### Preset Data Model

Suggested structure:

- `name`
- `isFactory`
- `sourceFile`
- `juce::ValueTree state`

### Preset File Format

Preset XML should contain:

- `schemaVersion`
- `pluginVersion`
- `pluginState`

Preset XML should not contain:

- `slotAState`
- `slotBState`
- `activeABSlot`

## Phase 5: Factory Presets

### Files

- `src/presets/FactoryPresets.h`
- or embed in preset manager first

### Initial Presets

Recommended starter set:

- `Init`
- `Short Room`
- `Wide Hall`
- `Dark Plate`
- `Mod Wash`
- `Frozen Bloom`

### Notes

- store them in code for now
- use same canonical plugin state format as user presets
- treat as read-only

## Phase 6: User Preset XML Save/Load

### Files

- `src/presets/TailwindPresetManager.cpp`
- `src/PluginProcessor.cpp`

### Tasks

- save active canonical plugin state as XML
- load preset XML into active slot only
- support:
  - save
  - save as
  - overwrite
  - delete
  - reveal folder

### Behavior

- loading a preset affects only the active A/B slot
- saving a preset captures only the active live state
- preset files are independent of A/B compare state

## Phase 7: Top Bar UI

### Files

- `src/components/brand/TopBar.h`
- `src/components/brand/TopBar.cpp`
- `src/PluginEditor.h`
- `src/PluginEditor.cpp`

### Add Visible Controls

- preset combo box
- A/B toggle

### Put Management In Options Menu

- `Copy A to B`
- `Copy B to A`
- `Swap A/B`
- `Save Preset`
- `Save Preset As`
- `Delete Preset`
- `Reveal Presets Folder`

### Notes

Keep v1 simple:

- visible A/B toggle
- visible preset selector
- management actions under `Options`

## Phase 8: Editor Wiring

### Files

- `src/PluginEditor.h`
- `src/PluginEditor.cpp`

### Tasks

- wire top bar actions to processor methods
- refresh A/B toggle state on slot change
- refresh preset combo contents
- update UI after preset load or A/B switch
- keep current metering/timer logic working cleanly

## Phase 9: Verification Checklist

### A/B Behavior

- switching A/B restores the correct slot
- editing A does not modify B
- editing B does not modify A
- copy A to B works
- copy B to A works
- swap works

### Presets

- factory presets load correctly
- user presets save/load correctly
- deleting user preset works
- factory presets cannot be overwritten/deleted
- preset load affects active slot only

### Session State

- DAW session restores active slot
- DAW session restores A and B contents
- old sessions without A/B data still load

### Build / Runtime

- Debug build works
- Release build works
- standalone works
- VST3 works
- VST2 still works if enabled

## Recommended Execution Order

1. versioned state wrapper
2. processor A/B engine
3. DAW session save/load with A/B
4. top bar A/B UI
5. preset manager
6. factory presets
7. user preset save/load
8. preset UI wiring
9. verification pass
