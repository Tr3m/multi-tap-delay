/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUIGraphics.h"

//==============================================================================
/**
*/
class Multitap_delayAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    Multitap_delayAudioProcessorEditor (Multitap_delayAudioProcessor&);
    ~Multitap_delayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void setNewDelayTime(float newValue);

private:
    
    std::unique_ptr<juce::Slider> timeSlider;
    std::unique_ptr<juce::Slider> feedbackSlider;
    std::unique_ptr<juce::Slider> detune1Slider;
    std::unique_ptr<juce::Slider> detune2Slider;   
    std::unique_ptr<juce::Slider> detune3Slider;
    std::unique_ptr<juce::Slider> detune4Slider;   
    std::unique_ptr<juce::Slider> toneSlider;
    std::unique_ptr<juce::Slider> mixSlider;

    GUIGraphics graphics;


    Multitap_delayAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Multitap_delayAudioProcessorEditor)
};
