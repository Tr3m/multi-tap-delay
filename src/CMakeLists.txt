target_sources(${PROJECT_NAME}
    PRIVATE
        Delay.cpp
        Delay.h
        GUIGraphics.cpp
        GUIGraphics.h
        Pitch.cpp
        Pitch.h
        PluginEditor.cpp
        PluginEditor.h
        PluginProcessor.cpp
        PluginProcessor.h    
    )

add_subdirectory(utils)
include_directories(utils)