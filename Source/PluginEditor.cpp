/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Multitap_delayAudioProcessorEditor::Multitap_delayAudioProcessorEditor (Multitap_delayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
   
    setSize (600, 430);


        
    timeSlider.reset(new juce::Slider("new slider"));
    addAndMakeVisible(timeSlider.get());
    timeSlider->setRange(10, 1000, 1);
    timeSlider->setTextValueSuffix(" ms");
    timeSlider->setSliderStyle(juce::Slider::Rotary);
    timeSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    timeSlider->setValue(audioProcessor.delays[1].getParameter(Delay::delayLengthParam)*1000);
    timeSlider->addListener(this);
    timeSlider->setLookAndFeel(&graphics);
    timeSlider->setDoubleClickReturnValue(true, 500);

    

    feedbackSlider.reset(new juce::Slider("new slider"));
    addAndMakeVisible(feedbackSlider.get());
    feedbackSlider->setRange(0.01, 0.995, 0.01);
    feedbackSlider->setSliderStyle(juce::Slider::Rotary);
    feedbackSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    feedbackSlider->setValue(audioProcessor.delays[0].getParameter(Delay::feedbackParam));
    feedbackSlider->addListener(this);
    feedbackSlider->setLookAndFeel(&graphics);
    feedbackSlider->setDoubleClickReturnValue(true, 0.65);
   


    detune1Slider.reset(new juce::Slider("new slider"));
    addAndMakeVisible(detune1Slider.get());
    detune1Slider->setRange(-50, 50, 1);
    detune1Slider->setTextValueSuffix(" ct");
    detune1Slider->setSliderStyle(juce::Slider::Rotary);
    detune1Slider->setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    detune1Slider->setValue((audioProcessor.pitches[0].getParameter(Pitch::Parameters::cents)*100));
    detune1Slider->addListener(this);
    detune1Slider->setLookAndFeel(&graphics);
    detune1Slider->setDoubleClickReturnValue(true, 8);
   
    

    
    detune2Slider.reset(new juce::Slider("new slider"));
    addAndMakeVisible(detune2Slider.get());
    detune2Slider->setRange(-50, 50, 1);
    detune2Slider->setTextValueSuffix(" ct");
    detune2Slider->setSliderStyle(juce::Slider::Rotary);
    detune2Slider->setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    detune2Slider->setValue((audioProcessor.pitches[1].getParameter(Pitch::Parameters::cents) * 100));
    detune2Slider->addListener(this);
    detune2Slider->setLookAndFeel(&graphics);
    detune2Slider->setDoubleClickReturnValue(true, 4);
    

    

    detune3Slider.reset(new juce::Slider("new slider"));
    addAndMakeVisible(detune3Slider.get());
    detune3Slider->setRange(-50, 50, 1);
    detune3Slider->setTextValueSuffix(" ct");
    detune3Slider->setSliderStyle(juce::Slider::Rotary);
    detune3Slider->setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    detune3Slider->setValue((audioProcessor.pitches[2].getParameter(Pitch::Parameters::cents) * 100));
    detune3Slider->addListener(this);
    detune3Slider->setLookAndFeel(&graphics);
    detune3Slider->setDoubleClickReturnValue(true, -4);
    

    
    detune4Slider.reset(new juce::Slider("new slider"));
    addAndMakeVisible(detune4Slider.get());
    detune4Slider->setRange(-50, 50, 1);
    detune4Slider->setTextValueSuffix(" ct");
    detune4Slider->setSliderStyle(juce::Slider::Rotary);
    detune4Slider->setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    detune4Slider->setValue((audioProcessor.pitches[3].getParameter(Pitch::Parameters::cents) * 100));
    detune4Slider->addListener(this);
    detune4Slider->setLookAndFeel(&graphics);
    detune4Slider->setDoubleClickReturnValue(true, -8);
    


    toneSlider.reset(new juce::Slider("new slider"));
    addAndMakeVisible(toneSlider.get());
    toneSlider->setRange(450.0, 20000.0, 0.1);
    toneSlider->setValue(audioProcessor.getTone());
    toneSlider->setTextValueSuffix(" Hz");
    toneSlider->setSliderStyle(juce::Slider::Rotary);
    toneSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    toneSlider->addListener(this);
    toneSlider->setLookAndFeel(&graphics);
   

    mixSlider.reset(new juce::Slider("new slider"));
    addAndMakeVisible(mixSlider.get());
    mixSlider->setRange(0, 100, 1);
    mixSlider->setTextValueSuffix(" %");
    mixSlider->setSliderStyle(juce::Slider::Rotary);
    mixSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    mixSlider->setValue(audioProcessor.getMix());
    mixSlider->addListener(this);
    mixSlider->setLookAndFeel(&graphics);
    mixSlider->setDoubleClickReturnValue(true, 25);
   

    int knobSize = 90;
    int xOffset = 15;
    int yOffset = 115;
    int detuneKnobSize = 140;
    
    timeSlider->setBounds(30 + xOffset - 3, yOffset, knobSize, knobSize);
    feedbackSlider->setBounds(170 + xOffset, yOffset, knobSize, knobSize);
    toneSlider->setBounds(310 + xOffset, yOffset, knobSize, knobSize);
    mixSlider->setBounds(450 + xOffset, yOffset, knobSize, knobSize);
    detune1Slider->setBounds(73, 190, detuneKnobSize, 145);
    detune2Slider->setBounds(197, 270, detuneKnobSize, 145);
    detune3Slider->setBounds(353, 190, detuneKnobSize, 145);
    detune4Slider->setBounds(435, 270, detuneKnobSize, 145);
}

Multitap_delayAudioProcessorEditor::~Multitap_delayAudioProcessorEditor()
{
    timeSlider = nullptr;
    feedbackSlider = nullptr;   
    detune1Slider = nullptr;   
    detune2Slider = nullptr;    
    detune3Slider = nullptr;    
    detune4Slider = nullptr;    
    toneSlider = nullptr;
    mixSlider = nullptr;
    
}

//==============================================================================
void Multitap_delayAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(graphics.getBackground(), 0, 0);
}

void Multitap_delayAudioProcessorEditor::resized()
{
    
   
}

void Multitap_delayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == timeSlider.get())
    {
        setNewDelayTime(slider->getValue() / 1000);
        DBG(audioProcessor.delays[3].getParameter(Delay::Parameters::delayLengthParam));
    }
    else if (slider == feedbackSlider.get())
    {
        for (int unitNo = 0; unitNo <= 3; ++unitNo)
            audioProcessor.delays[unitNo].setParameter(Delay::Parameters::feedbackParam, slider->getValue());
    }
    else if (slider == detune1Slider.get())
    {
        audioProcessor.pitches[0].setParameter(Pitch::Parameters::cents, (slider->getValue()) / 100);
    }
    else if (slider == detune2Slider.get())
    {
        audioProcessor.pitches[1].setParameter(Pitch::Parameters::cents, (slider->getValue()) / 100);
    }
    else if (slider == detune3Slider.get())
    {
        audioProcessor.pitches[2].setParameter(Pitch::Parameters::cents, (slider->getValue()) / 100);
    }
    else if (slider == detune4Slider.get())
    {
        audioProcessor.pitches[3].setParameter(Pitch::Parameters::cents, (slider->getValue()) / 100);
    }
    else if (slider == mixSlider.get())
    {
        audioProcessor.setMix(slider->getValue());
    }
    else if (slider == toneSlider.get())
    {
        audioProcessor.setTone(slider->getValue());
    }
}

void Multitap_delayAudioProcessorEditor::setNewDelayTime(float newValue)
{
    float d1Value = newValue * 2;
    audioProcessor.delays[0].setParameter(Delay::Parameters::delayLengthParam, d1Value);
    audioProcessor.delays[1].setParameter(Delay::Parameters::delayLengthParam, newValue);
    audioProcessor.delays[2].setParameter(Delay::Parameters::delayLengthParam, (d1Value *3) / 4);
    audioProcessor.delays[3].setParameter(Delay::Parameters::delayLengthParam, (d1Value *6) / 4);
}