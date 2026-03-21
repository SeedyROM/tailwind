# Tailwind

BigSky-inspired Long Tail Reverb

## About

- **Author**: Zack Kollar (rallokkcaz@gmail.com)
- **Company**: SeedyROM
- **Formats**: VST2, VST3, AU, Standalone

## Building

This project uses CMake and fetches JUCE automatically.

### Prerequisites

- CMake 3.22 or higher
- C++17 compatible compiler
- macOS: Xcode Command Line Tools
- Windows: Visual Studio 2019 or later
- Linux: GCC or Clang

### VST2 Setup

To build VST2 plugins, add and initialize the VST2 SDK submodule:

```bash
git submodule add https://github.com/sysfce2/vst-2.4-sdk.git external/vst-2.4-sdk
git submodule update --init --recursive
```

### Build Steps

```bash
# Configure
cmake -B build

# Build
cmake --build build --config Release
```

### Development Build Script

For rapid iteration with Element.app DAW:

```bash
# Optional: Configure Element project path
cp scripts/element_project.conf.example scripts/element_project.conf
# Edit scripts/element_project.conf with your .els project path

# Build and reload in Element
./scripts/element_dev.sh
```

## Project Structure

```
tailwind/
├── CMakeLists.txt              # Build configuration
├── src/
│   ├── PluginProcessor.h/cpp   # Audio processing
│   ├── PluginEditor.h/cpp      # UI editor
│   ├── components/
│   │   ├── brand/
│   │   │   └── TopBar.h/cpp    # Top bar with logo
│   │   ├── controls/           # UI controls (knobs, sliders, etc.)
│   │   └── graphs/             # Visualizations (waveforms, spectrums)
│   ├── data/                   # Data models and state
│   ├── dsp/                    # DSP processing (filters, effects)
│   └── utils/                  # Utilities and helpers
├── assets/
│   └── images/
│       └── logo.png            # Company logo
├── scripts/
│   └── element_dev.sh          # Build & reload script
└── external/                   # Git submodules
    └── vst-2.4-sdk/            # VST2 SDK
```

## License

[Your License Here]
