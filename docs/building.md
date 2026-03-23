# Building Tailwind

## Prerequisites

- **CMake 3.22+**
- **Ninja** (recommended) or your platform's default generator
- **C++17 compiler**

### macOS

Xcode Command Line Tools:

```bash
xcode-select --install
```

### Windows

Visual Studio 2019 or later with the C++ desktop workload.

### Linux

```bash
sudo apt-get install -y \
    build-essential cmake ninja-build \
    libasound2-dev \
    libx11-dev libxcomposite-dev libxcursor-dev libxext-dev \
    libxinerama-dev libxrandr-dev libxrender-dev \
    libfreetype6-dev libglu1-mesa-dev mesa-common-dev \
    libcurl4-openssl-dev libwebkit2gtk-4.1-dev
```

## Quick Start

If you have [just](https://github.com/casey/just) installed:

```bash
just setup    # init submodules + clean build
just build    # debug build
just release  # release build
just run      # launch standalone
```

Or with raw CMake:

```bash
cmake -B build -G Ninja
cmake --build build --config Release
```

JUCE 7.0.12 is fetched automatically via CMake `FetchContent` from a release archive -- no git clone overhead, no submodule needed.

## Pre-commit Formatting

Install the formatter and hook runner locally:

```bash
brew install pre-commit clang-format
pre-commit install
```

The repo ships with a `clang-format` pre-commit hook for C and C++ sources under `src/`. Vendored and generated code is excluded.

Run it manually across tracked files at any time:

```bash
pre-commit run --all-files
```

## CMake Options

| Option | Default | Description |
|---|---|---|
| `TAILWIND_COPY_AFTER_BUILD` | `ON` | Copy built plugins to system plugin directories |
| `TAILWIND_USE_MARCH_NATIVE` | `ON` | Use `-march=native` for local builds (AVX2/FMA on x86) |
| `TAILWIND_ENABLE_CODEGEN` | `ON` | Run Faust codegen when `.dsp` changes (requires `faust` on PATH) |
| `TAILWIND_ENABLE_VST2` | `OFF` | Enable legacy VST2 builds if you have a private SDK checkout |
| `TAILWIND_FORMATS` | `"VST3 AU Standalone"` | Space-separated list of plugin formats to build |

Example -- release build without copying to system dirs:

```bash
cmake -B build -G Ninja -DTAILWIND_COPY_AFTER_BUILD=OFF
cmake --build build --config Release
```

## VST2 (Optional)

VST2 requires the Steinberg VST2 SDK, which is no longer publicly distributed. If you have access to it:

```bash
git submodule add https://github.com/sysfce2/vst-2.4-sdk.git external/vst-2.4-sdk
git submodule update --init --recursive
```

Enable it explicitly:

```bash
cmake -B build -G Ninja -DTAILWIND_ENABLE_VST2=ON -DTAILWIND_FORMATS="VST VST3 AU Standalone"
```

## DSP Optimization

The build system applies aggressive DSP-specific compiler flags in Release mode:

- **Clang/GCC**: `-O3`, `-ffast-math`, `-funroll-loops`
- **ARM64**: NEON is always available, no extra flags needed
- **x86_64 local** (`TAILWIND_USE_MARCH_NATIVE=ON`): `-march=native` for AVX2/FMA
- **x86_64 distributable** (`TAILWIND_USE_MARCH_NATIVE=OFF`): `-msse4.2` baseline
- **MSVC**: `/O2`, `/fp:fast`, `/arch:AVX2` (local) or SSE2 baseline (distributable)
- **Denormals**: Flushed to zero via compiler flags (`-fdenormal-fp-math=positive-zero` on Clang) and JUCE's `ScopedNoDenormals`

## CI Builds

The GitHub Actions pipeline builds 4 configurations on every push to `main` and on pull requests:

| Build | Runner | Notes |
|---|---|---|
| macOS | `macos-14` | Universal Binary (arm64 + x86_64) |
| macOS-Legacy | `macos-14` | x86_64 only, deployment target 10.13 |
| Windows | `windows-latest` | MSVC |
| Linux | `ubuntu-latest` | GCC |

CI uses conservative settings for portable binaries:

- `TAILWIND_USE_MARCH_NATIVE=OFF` -- SSE4.2 baseline instead of AVX2
- `TAILWIND_COPY_AFTER_BUILD=OFF` -- no system install
- `TAILWIND_ENABLE_CODEGEN=OFF` -- uses committed generated files, no Faust compiler needed
- Linux CI also runs `pluginval` against the built VST3 artifact as a smoke-level validation pass

When a `v*` tag is pushed, the release job zips all platform artifacts and creates a draft GitHub Release.

## Element.app Dev Workflow

For rapid iteration using [Element](https://kushview.net/element/) as a host:

```bash
cp scripts/element_project.conf.example scripts/element_project.conf
# Edit element_project.conf with your .els project path
just element
```

This builds the plugin and reloads it in Element automatically.

## Just Recipes

Run `just --list` for the full list. Key recipes:

| Recipe | Description |
|---|---|
| `just codegen` | Run Faust codegen |
| `just configure` | CMake configure using committed generated files |
| `just configure-codegen` | Configure with explicit Faust codegen enabled |
| `just build` | Debug build |
| `just build-codegen` | Debug build after regenerating Faust outputs |
| `just release` | Release build |
| `just run` | Launch standalone app |
| `just element` | Build and reload in Element |
| `just clean` | Remove build directory |
| `just setup` | Full fresh setup (submodules + clean build) |
