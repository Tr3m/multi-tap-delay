juce_add_binary_data(BinaryData SOURCES
    background.png
    labels1.png
    knob.png
    varela-round.regular.ttf
)

# Need to build BinaryData with -fPIC flag on Linux
set_target_properties(BinaryData PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE)