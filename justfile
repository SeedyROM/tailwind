# Tailwind — Faust/JUCE audio plugin
# Run `just` or `just --list` to see available recipes.

# Default build type
build_type := "Debug"
build_dir := "build"
dsp_source := "dsp/tailwind_reverb.dsp"
gen_dir := "src/dsp/generated"
tailwind_formats := "VST3 AU Standalone"
tailwind_enable_vst2 := "OFF"
tailwind_copy_after_build := "ON"
tailwind_enable_codegen := "OFF"

# List available recipes
default:
    @just --list

# Run the Faust codegen (regenerates bridge files from .dsp)
codegen:
    python3 scripts/codegen.py {{dsp_source}} --output {{gen_dir}}

# Configure the project with CMake + Ninja
configure *flags:
    @enable_vst2="{{tailwind_enable_vst2}}"; formats='{{tailwind_formats}}'; enable_codegen="{{tailwind_enable_codegen}}"; for flag in {{flags}}; do if [ "$flag" = "--enable-vst2" ]; then enable_vst2=ON; formats="VST VST3 AU Standalone"; elif [ "$flag" = "--enable-codegen" ]; then enable_codegen=ON; else echo "Unknown flag: $flag" >&2; exit 1; fi; done; cmake -B {{build_dir}} -G Ninja -DCMAKE_BUILD_TYPE={{build_type}} -DTAILWIND_FORMATS="$formats" -DTAILWIND_ENABLE_VST2=$enable_vst2 -DTAILWIND_COPY_AFTER_BUILD={{tailwind_copy_after_build}} -DTAILWIND_ENABLE_CODEGEN=$enable_codegen

# Build the plugin (all formats)
build *flags:
    @enable_vst2="{{tailwind_enable_vst2}}"; for flag in {{flags}}; do if [ "$flag" = "--enable-vst2" ]; then enable_vst2=ON; fi; done; just build_type={{build_type}} tailwind_formats="{{tailwind_formats}}" tailwind_enable_vst2={{tailwind_enable_vst2}} tailwind_copy_after_build={{tailwind_copy_after_build}} tailwind_enable_codegen={{tailwind_enable_codegen}} configure {{flags}}; cmake --build {{build_dir}} --config {{build_type}}; if [ "$enable_vst2" = "ON" ]; then cmake --build {{build_dir}} --config {{build_type}} --target Tailwind_VST; fi

# Configure with Faust codegen enabled explicitly
configure-codegen: codegen
    just tailwind_enable_codegen=ON configure

# Build after regenerating Faust outputs
build-codegen: configure-codegen
    cmake --build {{build_dir}} --config {{build_type}}

# Build in Release mode
release *flags:
    just build_type=Release build {{flags}}

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
run *flags:
    just build_type={{build_type}} tailwind_formats="{{tailwind_formats}}" tailwind_enable_vst2={{tailwind_enable_vst2}} tailwind_copy_after_build={{tailwind_copy_after_build}} tailwind_enable_codegen={{tailwind_enable_codegen}} build {{flags}}
    open {{build_dir}}/Tailwind_artefacts/{{build_type}}/Standalone/Tailwind.app

# Build and reload in Element.app
element *flags:
    just build_type={{build_type}} tailwind_formats="{{tailwind_formats}}" tailwind_enable_vst2={{tailwind_enable_vst2}} tailwind_copy_after_build={{tailwind_copy_after_build}} tailwind_enable_codegen={{tailwind_enable_codegen}} build {{flags}}
    @bash scripts/element_dev.sh

# Reconfigure and build (useful after CMakeLists.txt changes)
reconfigure: clean configure build
