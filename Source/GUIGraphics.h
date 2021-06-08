#pragma once
#include <JuceHeader.h>

class GUIGraphics : public juce::LookAndFeel_V4
{
public:

    GUIGraphics();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    juce::Image getBackground();
 

    
private:

    juce::Image knobImage, backgroundImage;
    int effectType;
};