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
                       ), apvts(*this, nullptr, "Params", createParameters())
#endif
{
    lowCut.reset();
    highCut.reset();
    lowCut.setCoefficients(lowCutCoeffs.makeHighPass(getSampleRate(), 20.0, 1.0f));
    highCut.setCoefficients(highCutCoeffs.makeLowPass(getSampleRate(), 20000.0, 1.0f));
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
    for (int delay = 0; delay < 4; ++delay)
    {
        delays[delay].prepare(sampleRate);
        delays[delay].setMix(1.0);

        delayBuffers[delay].setSize(1, samplesPerBlock, false, true, false);
        delayBuffers[delay].clear();

        pitches[delay].prepare(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    }

    DBG("Prepare Done!");

    /*
    delays[0].setParameter(Delay::Parameters::delayLengthParam, 0.5);
    delays[1].setParameter(Delay::Parameters::delayLengthParam, 0.25);
    delays[2].setParameter(Delay::Parameters::delayLengthParam, 0.37);
    delays[3].setParameter(Delay::Parameters::delayLengthParam, 0.75);

    pitches[0].setParameter(Pitch::Parameters::cents, 0.08); //min -0,5 max 0,5
    pitches[1].setParameter(Pitch::Parameters::cents, 0.04);
    pitches[2].setParameter(Pitch::Parameters::cents, -0.04);
    pitches[3].setParameter(Pitch::Parameters::cents, -0.08);   
    */        
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

    //Update Params
    updateParameters();
    
    auto* dryData = buffer.getWritePointer(0);
    auto* dryDataR = buffer.getWritePointer(1);

    //float** bufferPTRs[4];
    std::vector<float*> bufferPTRs;
    bufferPTRs.resize(4);

    for (int delay = 0; delay < 4; ++delay)
        bufferPTRs[delay] = delayBuffers[delay].getWritePointer(0);

    // Process
    for (int delay = 0; delay < 4; ++delay)  
    {
        // Fill delay buffers
        delayBuffers[delay].copyFrom(0, 0, dryData, buffer.getNumSamples());

        // Process delay and pitch
        delays[delay].process(bufferPTRs[delay], 0, buffer.getNumSamples());
        pitches[delay].process(delayBuffers[delay], 1);
    }

    /*
    //Process
    delays[0].process(buff_1, totalNumInputChannels, totalNumOutputChannels);
    pitches[0].process(buff_1, midiMessages, totalNumInputChannels, totalNumOutputChannels);

    delays[1].process(buff_2, totalNumInputChannels, totalNumOutputChannels);
    pitches[1].process(buff_2, midiMessages, totalNumInputChannels, totalNumOutputChannels);

    delays[2].process(buff_3, totalNumInputChannels, totalNumOutputChannels);
    pitches[2].process(buff_3, midiMessages, totalNumInputChannels, totalNumOutputChannels);

    delays[3].process(buff_4, totalNumInputChannels, totalNumOutputChannels);
    pitches[3].process(buff_4, midiMessages, totalNumInputChannels, totalNumOutputChannels);
    */

    // Sum Wet Buffer
    for(int sample = 0; sample < buffer.getNumSamples(); ++sample)
        for (int delay = 1; delay < 4; ++delay)
            bufferPTRs[0][sample] = (bufferPTRs[0][sample] + bufferPTRs[delay][sample]) / 2;

    /*
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        
        buff_1.addFrom(channel, 0, buff_2.getWritePointer(channel), buffer.getNumSamples());
        buff_1.applyGain(0.9);

        buff_1.addFrom(channel, 0, buff_3.getWritePointer(channel), buffer.getNumSamples());
        buff_1.applyGain(0.9);
     
        buff_1.addFrom(channel, 0, buff_4.getWritePointer(channel), buffer.getNumSamples());
        buff_1.applyGain(0.9);
        
    }
    */

    // Process Filters
    lowCut.processSamples(bufferPTRs[0], buffer.getNumSamples());
    highCut.processSamples(bufferPTRs[0], buffer.getNumSamples());

    // SampleType output = (1.0 - mix)*channelData[sample] + mix*processed;

    // Wet/Dry Mix
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        dryData[sample] = ((1.0 - mix) * dryData[sample]) + (mix * bufferPTRs[0][sample]);

    // Dual Mono
    AudioChannelUtilities<float>::doDualMono(dryData, dryDataR, 0, buffer.getNumSamples());
    
    /*
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
    */
}

void Multitap_delayAudioProcessor::updateParameters()
{
    // Update Delays and pitch shifters
    for (int delay = 0; delay < 4; ++delay)
    {
        delays[delay].setDelayTime(*apvts.getRawParameterValue("DELAY_TIME_" + std::to_string(delay + 1) + "_ID"));
        delays[delay].setFeedback(*apvts.getRawParameterValue("FEEDBACK_" + std::to_string(delay + 1) + "_ID"));

        pitches[delay].setParameter(Pitch::Parameters::cents, 
            *apvts.getRawParameterValue("DETUNE_" + std::to_string(delay + 1) + "_ID") / 100.0);
    }

    // Update Filter Coeffs
    lowCut.setCoefficients(lowCutCoeffs.makeHighPass(getSampleRate(), 
        *apvts.getRawParameterValue("LOWCUT_ID"), 1.0f));

    highCut.setCoefficients(highCutCoeffs.makeLowPass(getSampleRate(),
        *apvts.getRawParameterValue("HIGHCUT_ID"), 1.0f));

    mix = *apvts.getRawParameterValue("MIX_ID") / 100.0;
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

juce::AudioProcessorValueTreeState::ParameterLayout Multitap_delayAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    for(int delay = 1; delay <= 4; ++delay)
    {
        parameters.push_back(std::make_unique<juce::AudioParameterInt>("DELAY_TIME_" + std::to_string(delay) + 
            "_ID", "DELAY_TIME" + std::to_string(delay), 95, 1500, 500));

        parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FEEDBACK_" + std::to_string(delay) + "_ID", 
            "FEEDBACK" + std::to_string(delay), 0.0f, 0.95, 0.7));

        parameters.push_back(std::make_unique<juce::AudioParameterInt>("DETUNE_" + std::to_string(delay) + 
            "_ID", "DETUNE_" + std::to_string(delay), -50, 50, 0));
    }

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MIX_ID", "MIX", 0.0f, 100.0, 50.0));
    parameters.push_back(std::make_unique<juce::AudioParameterInt>("LOWCUT_ID", "LOWCUT", 20, 2000, 20));
    parameters.push_back(std::make_unique<juce::AudioParameterInt>("HIGHCUT_ID", "HIGHCUT", 200, 20000, 20000));


    return { parameters.begin(), parameters.end() };
}

void Multitap_delayAudioProcessor::setBPM(int newBPM)
{
    this->BPM = newBPM;
}

int Multitap_delayAudioProcessor::getBPM()
{
    return this->BPM;
}

//==============================================================================
void Multitap_delayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    xml->addTextElement("last_bpm");
    xml->setAttribute("last_bpm", BPM);
    copyXmlToBinary(*xml, destData);
}

void Multitap_delayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
        {
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
            BPM = xmlState->getIntAttribute("last_bpm");
        }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Multitap_delayAudioProcessor();
}
