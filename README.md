# Tailwind

BigSky-inspired long tail reverb plugin.

[![Build](https://github.com/SeedyROM/tailwind/actions/workflows/build.yml/badge.svg)](https://github.com/SeedyROM/tailwind/actions/workflows/build.yml)

<img width="1083" height="644" alt="Screenshot 2026-03-23 at 2 45 31 AM" src="https://github.com/user-attachments/assets/5b45e59f-2a45-4f97-b9cc-b860e12a723e" />
<br />
<br />

Tailwind is a stereo-output algorithmic reverb built around an 8x8 Feedback Delay Network with Hadamard mixing, Zita-Rev1-style frequency-dependent damping, LFO-modulated tank delay lines, input diffusers, and a freeze mode. It accepts mono or stereo input and always produces stereo output. The DSP is written in [Faust](https://faust.grame.fr/) and the UI is built with [JUCE](https://juce.com/).

The freeze path is designed as a playable, automatable part of the effect rather than a static preset state. That means hosts can drive it with automation, macros, LFOs, CV, or arrangement changes for texture work, while the plugin avoids restoring into an accidentally frozen state.

## Platforms & Formats

| Platform | Architectures | Formats |
|---|---|---|
| macOS | Universal (arm64 + x86_64) | VST3, AU, Standalone |
| macOS Legacy | x86_64 (10.13+) | VST3, AU, Standalone |
| Windows | x86_64 | VST3, Standalone |
| Linux | x86_64 | VST3, Standalone |

## Downloads

Grab the latest build from [GitHub Releases](https://github.com/SeedyROM/tailwind/releases). CI builds run on every push to `main` and pull request. When a `v*` tag is pushed, a draft release is created automatically with per-platform zips (macOS Universal, macOS Legacy, Windows, Linux).

## Building

Requires CMake 3.22+ and a C++17 compiler. JUCE is fetched automatically during configure.

```bash
cmake -B build -G Ninja
cmake --build build --config Release
```

See [docs/building.md](docs/building.md) for platform-specific prerequisites, CMake options, and the `just` task runner.

## Faust DSP

The reverb DSP lives in `dsp/tailwind_reverb.dsp`. A codegen script compiles the Faust source to C++ and generates a bridge layer that maps Faust parameters to JUCE's `AudioProcessorValueTreeState`. The generated files are committed to git, so you don't need Faust installed for normal builds; Faust is only required when you intentionally regenerate the DSP outputs.

See [docs/faust-codegen.md](docs/faust-codegen.md) for details on the codegen pipeline and how to modify the DSP.

## License

[AGPLv3](LICENSE)
