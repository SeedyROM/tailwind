# Tailwind — Faust/JUCE audio plugin
# Run `just` or `just --list` to see available recipes.

# Default build type
build_type := "Debug"
build_dir := "build"
dsp_source := "dsp/tailwind_reverb.dsp"
gen_dir := "src/dsp/generated"

# List available recipes
default:
    @just --list

# Run the Faust codegen (regenerates bridge files from .dsp)
codegen:
    python3 scripts/codegen.py {{dsp_source}} --output {{gen_dir}}

# Configure the project with CMake + Ninja
configure: codegen
    cmake -B {{build_dir}} -G Ninja

# Build the plugin (all formats)
build: configure
    cmake --build {{build_dir}} --config {{build_type}}

# Build in Release mode
release:
    just build_type=Release build

# Clean the build directory
clean:
    rm -rf {{build_dir}}

# Clean and rebuild from scratch
rebuild: clean build

# Initialize/update git submodules (VST2 SDK, etc.)
submodules:
    git submodule update --init --recursive

# Full fresh setup: submodules + clean build
setup: submodules rebuild

# Launch the standalone plugin
run: build
    open {{build_dir}}/Tailwind_artefacts/Standalone/Tailwind.app

# Build and reload in Element.app
element: build
    @bash scripts/element_dev.sh

# Reconfigure and build (useful after CMakeLists.txt changes)
reconfigure: clean configure build
