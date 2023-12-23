#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <utils/extras/AudioChannelUtilities.h>
#include <utils/extras/GainUtilities.h>
#include <Delay.h>
#include <Pitch.h>

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

    void updateParameters();

    juce::AudioProcessorValueTreeState apvts;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    void setBPM(int newBPM);
    int getBPM();

private:
    //==============================================================================

    Delay<float> delays[4];
    Pitch pitches[4];

    juce::AudioBuffer<float> delayBuffers[4];

    int BPM {120};
    float mix {0.5};

    juce::IIRFilter lowCut, highCut;
    juce::IIRCoefficients lowCutCoeffs, highCutCoeffs;

    juce::AudioPlayHead* playHead;
    juce::AudioPlayHead::CurrentPositionInfo currentPositionInfo;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Multitap_delayAudioProcessor)
};
