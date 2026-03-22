cmake_minimum_required(VERSION 3.22)

project(Tailwind VERSION 0.1.0)

# Suppress developer warnings from JUCE
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON CACHE INTERNAL "")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# VST2 SDK Path - must be set BEFORE fetching JUCE
set(VST2_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/vst-2.4-sdk/vstsdk2.4" CACHE PATH "Path to VST2 SDK")

if(EXISTS "${VST2_SDK_PATH}/pluginterfaces/vst2.x/aeffect.h")
    message(STATUS "VST2 SDK found at: ${VST2_SDK_PATH}")
else()
    message(WARNING "VST2 SDK not found at: ${VST2_SDK_PATH}")
    message(WARNING "Run: git submodule update --init --recursive")
endif()

# Fetch JUCE from GitHub (release archive — fast, no git overhead)
include(FetchContent)
FetchContent_Declare(
    JUCE
    URL https://github.com/juce-framework/JUCE/archive/refs/tags/7.0.12.tar.gz
)
FetchContent_MakeAvailable(JUCE)

# Set VST2 SDK path for JUCE (must be after FetchContent_MakeAvailable)
if(EXISTS "${VST2_SDK_PATH}/pluginterfaces/vst2.x/aeffect.h")
    juce_set_vst2_sdk_path("${VST2_SDK_PATH}")
endif()

# ==========================================================================
# Faust DSP Codegen
# ==========================================================================
# Regenerates the Faust C++ DSP and JUCE parameter bridge when the .dsp changes.
# The generated files are committed to git, so Faust is only needed when
# modifying the DSP source.

set(FAUST_DSP "${CMAKE_SOURCE_DIR}/dsp/tailwind_reverb.dsp")
set(FAUST_GEN_DIR "${CMAKE_SOURCE_DIR}/src/dsp/generated")
set(FAUST_CODEGEN "${CMAKE_SOURCE_DIR}/scripts/codegen.py")

set(FAUST_GENERATED_FILES
    ${FAUST_GEN_DIR}/FaustDefs.h
    ${FAUST_GEN_DIR}/FaustDSP.h
    ${FAUST_GEN_DIR}/FaustParams.h
    ${FAUST_GEN_DIR}/FaustBridge.h
)

add_custom_command(
    OUTPUT ${FAUST_GENERATED_FILES}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${FAUST_GEN_DIR}
    COMMAND python3 ${FAUST_CODEGEN} ${FAUST_DSP} --output ${FAUST_GEN_DIR}
    DEPENDS ${FAUST_DSP} ${FAUST_CODEGEN}
    COMMENT "Generating Faust DSP and parameter bridge from tailwind_reverb.dsp..."
    VERBATIM
)

add_custom_target(faust_codegen DEPENDS ${FAUST_GENERATED_FILES})

# ==========================================================================
# Plugin Target
# ==========================================================================

# Define the plugin
juce_add_plugin(Tailwind
    COMPANY_NAME "SeedyROM"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Seed
    PLUGIN_CODE Tail
    FORMATS VST VST3 AU Standalone
    PRODUCT_NAME "Tailwind"
)

# Ensure codegen runs before compiling plugin sources
add_dependencies(Tailwind faust_codegen)

# Add binary resources (fonts, images, etc)
juce_add_binary_data(TailwindAssets SOURCES
    assets/images/logo.png
)

# Add source files
target_sources(Tailwind PRIVATE
    src/PluginProcessor.cpp
    src/PluginEditor.cpp
    src/components/brand/TopBar.cpp
)

# Include path for generated Faust headers
target_include_directories(Tailwind PRIVATE
    ${FAUST_GEN_DIR}
)

# Set compile definitions
target_compile_definitions(Tailwind PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

# ==========================================================================
# DSP Optimization Flags
# ==========================================================================
# These flags enable the compiler to fully auto-vectorize the Faust-generated
# DSP code using SIMD instructions (NEON on Apple Silicon, AVX2/SSE on x86).

# -ffast-math: enables FP contraction, reciprocal approximations, and
#              reassociation — critical for auto-vectorization of DSP code.
#              Safe here because we control the numeric range (audio floats).
# -march=native: target the build machine's exact CPU (enables AVX2, NEON, etc.)
# -funroll-loops: unroll inner DSP loops for better ILP and SIMD utilization.

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(Tailwind PRIVATE
        # Release-only optimizations
        $<$<CONFIG:Release>:-O3>
        $<$<CONFIG:Release>:-ffast-math>
        $<$<CONFIG:Release>:-funroll-loops>
    )

    # Architecture-specific SIMD flags
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
        # Apple Silicon / ARM64: NEON is always available, no extra flags needed.
        # But we can still hint the compiler for better scheduling.
        message(STATUS "Target: ARM64 (NEON intrinsics available by default)")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
        # x86-64: enable AVX2 + FMA for widest SIMD on modern CPUs.
        # Falls back gracefully if building on older CPUs via -march=native.
        target_compile_options(Tailwind PRIVATE
            $<$<CONFIG:Release>:-march=native>
        )
        message(STATUS "Target: x86_64 (using -march=native for AVX2/FMA)")
    endif()

    # Flush-to-zero at the compiler level (supplement Faust -ftz 2 and JUCE ScopedNoDenormals)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(Tailwind PRIVATE
            $<$<CONFIG:Release>:-fdenormal-fp-math=positive-zero>
        )
    endif()
elseif(MSVC)
    target_compile_options(Tailwind PRIVATE
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:Release>:/fp:fast>
        $<$<CONFIG:Release>:/arch:AVX2>
    )
endif()

# Link JUCE modules
target_link_libraries(Tailwind PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_graphics
    juce::juce_dsp
    TailwindAssets
PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
