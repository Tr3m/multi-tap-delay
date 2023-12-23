cmake_minimum_required(VERSION 3.15)

project(multi_tap_delay VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(SOUNDTOUCH_DLL "Build SoundTouchDLL C wrapper library" ON)
add_subdirectory(modules/soundtouch)

set(PROJECT_NAME "multi_tap_delay")


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(JUCE CONFIG REQUIRED)

juce_add_plugin(${PROJECT_NAME}
    # VERSION ...                              
    # ICON_BIG ...                            
    # ICON_SMALL ...
    COMPANY_NAME "Manos Labrakis"
    # IS_SYNTH TRUE/FALSE                 
    # NEEDS_MIDI_INPUT TRUE/FALSE           
    # NEEDS_MIDI_OUTPUT TRUE/FALSE        
    # IS_MIDI_EFFECT TRUE/FALSE         
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE
    # COPY_PLUGIN_AFTER_BUILD TRUE/FALSE  
    PLUGIN_MANUFACTURER_CODE Juce             
    PLUGIN_CODE Mtd0                                                            
    FORMATS AU VST3 Standalone                  
    PRODUCT_NAME "Multi-Tap Delay")        
    

    juce_generate_juce_header(${PROJECT_NAME})
    
    add_subdirectory(assets)
    add_subdirectory(src)
    include_directories(src)


target_sources(${PROJECT_NAME}
    PRIVATE
        )

    
target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0)     

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        # AudioPluginData           # If we'd created a binary data target, we'd link to it here
        BinaryData
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        SoundTouch
        )

target_include_directories(${PROJECT_NAME}
    PUBLIC
        modules
        modules/soundtouch/include
    #INTERFACE
        #$<TARGET_PROPERTY:juce_plugin_modules,INCLUDE_DIRECTORIES>
    )