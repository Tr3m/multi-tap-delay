/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Delay.h"
#include "Pitch.h"

//==============================================================================
/**
*/
class Multitap_delayAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Multitap_delayAudioProcessor();
    ~Multitap_delayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //Setters and Getters
    void setTone(float newValue);
    void setMix(float newValue);


    float getTone();
    int getMix();    

    

    Delay delays[4];
    Pitch pitches[4];

private:
    //==============================================================================

    float mixValue = 0.15;
    float toneFreq = 10000.0f;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter <float>, juce::dsp::IIR::Coefficients <float>> filter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Multitap_delayAudioProcessor)
};
