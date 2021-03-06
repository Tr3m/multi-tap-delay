/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Multitap_delayAudioProcessor::Multitap_delayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                            filter(juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), toneFreq, 1.0f))
#endif
{
}

Multitap_delayAudioProcessor::~Multitap_delayAudioProcessor()
{
}

//==============================================================================
const juce::String Multitap_delayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Multitap_delayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Multitap_delayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Multitap_delayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Multitap_delayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Multitap_delayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Multitap_delayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Multitap_delayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Multitap_delayAudioProcessor::getProgramName (int index)
{
    return {};
}

void Multitap_delayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Multitap_delayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int unitNo = 0; unitNo <= 3; ++unitNo)
    {
        delays[unitNo].prepare(sampleRate, samplesPerBlock);
        delays[unitNo].setParameter(Delay::Parameters::dryMixParam, 0.0);
        delays[unitNo].setParameter(Delay::Parameters::wetMixParam, 1.0);
        delays[unitNo].setParameter(Delay::Parameters::feedbackParam, 0.4);

        pitches[unitNo].prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    }

    delays[0].setParameter(Delay::Parameters::delayLengthParam, 0.5);
    delays[1].setParameter(Delay::Parameters::delayLengthParam, 0.25);
    delays[2].setParameter(Delay::Parameters::delayLengthParam, 0.37);
    delays[3].setParameter(Delay::Parameters::delayLengthParam, 0.75);

    pitches[0].setParameter(Pitch::Parameters::cents, 0.08); //min -0,5 max 0,5
    pitches[1].setParameter(Pitch::Parameters::cents, 0.04);
    pitches[2].setParameter(Pitch::Parameters::cents, -0.04);
    pitches[3].setParameter(Pitch::Parameters::cents, -0.08);   

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getNumOutputChannels();

    filter.reset();
    filter.prepare(spec);
        
}

void Multitap_delayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Multitap_delayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Multitap_delayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //Update Filter State
    *filter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), toneFreq, 1.0f);
    
    //Initialize delay buffers
    juce::AudioBuffer<float> buff_1(2, buffer.getNumSamples());
    juce::AudioBuffer<float> buff_2(2, buffer.getNumSamples());
    juce::AudioBuffer<float> buff_3(2, buffer.getNumSamples());
    juce::AudioBuffer<float> buff_4(2, buffer.getNumSamples());
    
    //Fill delay buffers
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        buff_1.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());
        buff_2.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());
        buff_3.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());
        buff_4.copyFrom(channel, 0, buffer.getWritePointer(channel), buffer.getNumSamples());

    }

    //Process
    delays[0].process(buff_1, totalNumInputChannels, totalNumOutputChannels);
    pitches[0].process(buff_1, midiMessages, totalNumInputChannels, totalNumOutputChannels);

    delays[1].process(buff_2, totalNumInputChannels, totalNumOutputChannels);
    pitches[1].process(buff_2, midiMessages, totalNumInputChannels, totalNumOutputChannels);

    delays[2].process(buff_3, totalNumInputChannels, totalNumOutputChannels);
    pitches[2].process(buff_3, midiMessages, totalNumInputChannels, totalNumOutputChannels);

    delays[3].process(buff_4, totalNumInputChannels, totalNumOutputChannels);
    pitches[3].process(buff_4, midiMessages, totalNumInputChannels, totalNumOutputChannels);


    //Sum to wet buffer
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        
        buff_1.addFrom(channel, 0, buff_2.getWritePointer(channel), buffer.getNumSamples());
        buff_1.applyGain(0.9);

        buff_1.addFrom(channel, 0, buff_3.getWritePointer(channel), buffer.getNumSamples());
        buff_1.applyGain(0.9);
     
        buff_1.addFrom(channel, 0, buff_4.getWritePointer(channel), buffer.getNumSamples());
        buff_1.applyGain(0.9);
        
    }

    juce::dsp::AudioBlock<float> block(buff_1);

    //Fiter Processing
    filter.process(juce::dsp::ProcessContextReplacing<float>(block));

   
    float wet = 0.0 + mixValue;
    float dry = 1.0 - mixValue;

    //WET/DRY Control
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* dryData = buffer.getWritePointer(channel);
        auto* WetData = buff_1.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            dryData[sample] = dry * dryData[sample] + wet * WetData[sample];
        }
    }
}

//==============================================================================
bool Multitap_delayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Multitap_delayAudioProcessor::createEditor()
{
    return new Multitap_delayAudioProcessorEditor (*this);
}

//==============================================================================
void Multitap_delayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Multitap_delayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void Multitap_delayAudioProcessor::setMix(float newValue)
{
    mixValue = newValue;
    if (mixValue > 100)
        mixValue = 100;
    if (mixValue < 0)
        mixValue = 0;

    mixValue = mixValue / 100;
}

int Multitap_delayAudioProcessor::getMix()
{
    return int(mixValue*100);
}

void Multitap_delayAudioProcessor::setTone(float newValue)
{
    toneFreq = newValue;

    //Bounds Check
    if (toneFreq > 20000.0f)
        toneFreq = 20000.0f;
    if (toneFreq < 450.0f)
        toneFreq = 450.0f;
}

float Multitap_delayAudioProcessor::getTone()
{
    return toneFreq;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Multitap_delayAudioProcessor();
}
