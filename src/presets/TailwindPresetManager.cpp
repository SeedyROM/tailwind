#include "TailwindPresetManager.h"

namespace {

constexpr auto presetFileExtension = ".tailwindpreset";
constexpr auto presetRootType = "TailwindPluginState";

juce::CriticalSection presetCacheLock;
juce::Identifier cachedPluginStateType;
juce::ValueTree cachedReferenceState;
std::vector<TailwindPresetManager::PresetInfo> cachedFactoryPresets;
std::vector<TailwindPresetManager::PresetInfo> cachedAvailablePresets;
bool hasCachedFactoryPresets = false;
bool hasCachedAvailablePresets = false;
bool userPresetListDirty = true;

juce::ValueTree createPresetState(const juce::ValueTree& referenceState,
                                  std::initializer_list<std::pair<const char*, float>> values) {
  auto state = referenceState.createCopy();

  auto setParam = [&state](const juce::String& paramID, float value) {
    for (int i = 0; i < state.getNumChildren(); ++i) {
      auto child = state.getChild(i);
      if (child.hasProperty("id") && child["id"].toString() == paramID) {
        child.setProperty("value", value, nullptr);
        return;
      }
    }
  };

  for (const auto& [paramID, value] : values)
    setParam(paramID, value);

  return state;
}

std::vector<TailwindPresetManager::PresetInfo>
createFactoryPresets(const juce::ValueTree& referenceState,
                     const juce::Identifier& pluginStateType) {
  juce::ignoreUnused(pluginStateType);

  return {{"Init",
           true,
           {},
           createPresetState(referenceState,
                             {{"mix", 0.0f},
                              {"decay", 0.1f},
                              {"pre_delay_ms", 0.0f},
                              {"diffusion", 0.0f},
                              {"damping", 0.0f},
                              {"low_damp", 0.0f},
                              {"mod_rate_hz", 0.1f},
                              {"mod_depth", 0.0f},
                              {"low_cut_hz", 20.0f},
                              {"high_cut_hz", 20000.0f},
                              {"freeze", 0.6f},
                              {"freeze_on", 0.0f},
                              {"saturation", 0.0f},
                              {"input_gain_db", 0.0f},
                              {"output_gain_db", 0.0f}})},
          {"Short Room",
           true,
           {},
           createPresetState(referenceState,
                             {{"mix", 0.28f},
                              {"decay", 0.45f},
                              {"pre_delay_ms", 8.0f},
                              {"diffusion", 0.52f},
                              {"damping", 0.38f},
                              {"low_damp", 0.24f},
                              {"mod_rate_hz", 0.45f},
                              {"mod_depth", 0.12f},
                              {"low_cut_hz", 120.0f},
                              {"high_cut_hz", 7800.0f},
                              {"saturation", 0.08f}})},
          {"Wide Hall",
           true,
           {},
           createPresetState(referenceState,
                             {{"mix", 0.48f},
                              {"decay", 0.86f},
                              {"pre_delay_ms", 28.0f},
                              {"diffusion", 0.78f},
                              {"damping", 0.44f},
                              {"low_damp", 0.18f},
                              {"mod_rate_hz", 0.72f},
                              {"mod_depth", 0.27f},
                              {"low_cut_hz", 90.0f},
                              {"high_cut_hz", 11200.0f},
                              {"saturation", 0.11f}})},
          {"Dark Plate",
           true,
           {},
           createPresetState(referenceState,
                             {{"mix", 0.36f},
                              {"decay", 0.73f},
                              {"pre_delay_ms", 16.0f},
                              {"diffusion", 0.69f},
                              {"damping", 0.61f},
                              {"low_damp", 0.26f},
                              {"mod_rate_hz", 0.64f},
                              {"mod_depth", 0.18f},
                              {"low_cut_hz", 140.0f},
                              {"high_cut_hz", 6200.0f},
                              {"saturation", 0.15f}})},
          {"Mod Wash",
           true,
           {},
           createPresetState(referenceState,
                             {{"mix", 0.55f},
                              {"decay", 0.9f},
                              {"pre_delay_ms", 22.0f},
                              {"diffusion", 0.82f},
                              {"damping", 0.42f},
                              {"low_damp", 0.21f},
                              {"mod_rate_hz", 1.35f},
                              {"mod_depth", 0.42f},
                              {"low_cut_hz", 110.0f},
                              {"high_cut_hz", 9800.0f},
                              {"saturation", 0.1f}})},
          {"Frozen Bloom",
           true,
           {},
           createPresetState(referenceState,
                             {{"mix", 0.62f},
                              {"decay", 0.95f},
                              {"pre_delay_ms", 35.0f},
                              {"diffusion", 0.88f},
                              {"damping", 0.36f},
                              {"low_damp", 0.14f},
                              {"mod_rate_hz", 0.84f},
                              {"mod_depth", 0.36f},
                              {"low_cut_hz", 70.0f},
                              {"high_cut_hz", 12400.0f},
                              {"freeze", 1.0f},
                              {"saturation", 0.12f}})}};
}

TailwindPresetManager::PresetInfo*
findPresetByName(std::vector<TailwindPresetManager::PresetInfo>& presets,
                 const juce::String& presetName) {
  for (auto& preset : presets)
    if (preset.name == presetName)
      return &preset;

  return nullptr;
}

juce::ValueTree loadWrappedStateFromFile(const juce::File& file) {
  if (!file.existsAsFile())
    return {};

  auto xml = juce::XmlDocument::parse(file);
  return xml != nullptr ? juce::ValueTree::fromXml(*xml) : juce::ValueTree{};
}

juce::File getPresetDirectoryForCache() {
  auto directory = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
                       .getChildFile("SeedyROM")
                       .getChildFile("Tailwind")
                       .getChildFile("Presets");
  directory.createDirectory();
  return directory;
}

bool shouldRebuildFactoryPresets(const juce::ValueTree& referenceState,
                                 const juce::Identifier& pluginStateType) {
  if (!hasCachedFactoryPresets)
    return true;

  if (cachedPluginStateType != pluginStateType)
    return true;

  return !cachedReferenceState.isEquivalentTo(referenceState);
}

void rebuildFactoryPresetCache(const juce::ValueTree& referenceState,
                               const juce::Identifier& pluginStateType) {
  cachedFactoryPresets = createFactoryPresets(referenceState, pluginStateType);
  cachedReferenceState = referenceState.createCopy();
  cachedPluginStateType = pluginStateType;
  hasCachedFactoryPresets = true;
  userPresetListDirty = true;
}

void rebuildAvailablePresetCache() {
  cachedAvailablePresets = cachedFactoryPresets;

  auto directory = getPresetDirectoryForCache();
  auto files = directory.findChildFiles(
      juce::File::findFiles, false, "*" + juce::String(presetFileExtension));

  for (const auto& file : files)
    cachedAvailablePresets.push_back({file.getFileNameWithoutExtension(), false, file, {}});

  std::sort(cachedAvailablePresets.begin(),
            cachedAvailablePresets.end(),
            [](const TailwindPresetManager::PresetInfo& lhs,
               const TailwindPresetManager::PresetInfo& rhs) {
              if (lhs.isFactory != rhs.isFactory)
                return lhs.isFactory;
              return lhs.name < rhs.name;
            });

  hasCachedAvailablePresets = true;
  userPresetListDirty = false;
}

void ensurePresetCaches(const juce::ValueTree& referenceState,
                        const juce::Identifier& pluginStateType) {
  if (shouldRebuildFactoryPresets(referenceState, pluginStateType))
    rebuildFactoryPresetCache(referenceState, pluginStateType);

  if (!hasCachedAvailablePresets || userPresetListDirty)
    rebuildAvailablePresetCache();
}

} // namespace

juce::File TailwindPresetManager::getPresetDirectory() {
  auto directory = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
                       .getChildFile("SeedyROM")
                       .getChildFile("Tailwind")
                       .getChildFile("Presets");
  directory.createDirectory();
  return directory;
}

std::vector<TailwindPresetManager::PresetInfo>
TailwindPresetManager::getAvailablePresets(const juce::ValueTree& referenceState,
                                           const juce::Identifier& pluginStateType) {
  const juce::ScopedLock lock(presetCacheLock);
  ensurePresetCaches(referenceState, pluginStateType);
  return cachedAvailablePresets;
}

juce::ValueTree TailwindPresetManager::loadPresetState(const juce::String& presetName,
                                                       const juce::ValueTree& referenceState,
                                                       const juce::Identifier& pluginStateType) {
  std::vector<TailwindPresetManager::PresetInfo> presets;
  {
    const juce::ScopedLock lock(presetCacheLock);
    ensurePresetCaches(referenceState, pluginStateType);
    presets = cachedAvailablePresets;
  }

  auto* preset = findPresetByName(presets, presetName);
  if (preset == nullptr)
    return {};

  if (preset->isFactory)
    return preset->state.createCopy();

  auto wrappedState = loadWrappedStateFromFile(preset->file);
  if (!wrappedState.hasType(presetRootType))
    return {};

  auto pluginState = wrappedState.getChildWithName(pluginStateType);
  return pluginState.isValid() ? pluginState.createCopy() : juce::ValueTree{};
}

bool TailwindPresetManager::saveUserPreset(const juce::String& presetName,
                                           const juce::ValueTree& wrappedState) {
  if (presetName.trim().isEmpty() || !wrappedState.isValid())
    return false;

  auto file = getPresetDirectory().getChildFile(presetName + presetFileExtension);
  std::unique_ptr<juce::XmlElement> xml(wrappedState.createXml());
  const auto didSave = xml != nullptr && xml->writeTo(file);
  if (didSave) {
    const juce::ScopedLock lock(presetCacheLock);
    userPresetListDirty = true;
  }

  return didSave;
}

bool TailwindPresetManager::deleteUserPreset(const juce::String& presetName) {
  auto file = getPresetDirectory().getChildFile(presetName + presetFileExtension);
  const auto didDelete = file.existsAsFile() && file.deleteFile();
  if (didDelete) {
    const juce::ScopedLock lock(presetCacheLock);
    userPresetListDirty = true;
  }

  return didDelete;
}

void TailwindPresetManager::revealPresetDirectory() {
  getPresetDirectory().revealToUser();
}

bool TailwindPresetManager::isFactoryPreset(const juce::String& presetName,
                                            const juce::ValueTree& referenceState,
                                            const juce::Identifier& pluginStateType) {
  std::vector<TailwindPresetManager::PresetInfo> presets;
  {
    const juce::ScopedLock lock(presetCacheLock);
    ensurePresetCaches(referenceState, pluginStateType);
    presets = cachedAvailablePresets;
  }

  auto* preset = findPresetByName(presets, presetName);
  return preset != nullptr && preset->isFactory;
}
