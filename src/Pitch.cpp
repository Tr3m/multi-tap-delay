#include "Pitch.h"

Pitch::Pitch()
{
	semitonesParam.reset(new juce::AudioParameterFloat("semitonesParam", "semitonesParam", -12.0f, 12.0f, 0.f));
    centsParam.reset(new juce::AudioParameterFloat("centsParam", "centsParam", -9.0f, 9.0f, 0.0f));
    //addParameter(semitonesParam.get());
    //addParameter(centsParam.get());

    m_soundTouch = std::make_unique<soundtouch::SoundTouch>();
}

Pitch::~Pitch()
{
	semitonesParam.release();
    centsParam.release();
}

void Pitch::prepare(double sampleRate, int samplesPerBlock, int totalNumInputChannels)
{
	m_soundTouch->setChannels(totalNumInputChannels);
    m_soundTouch->setSampleRate(sampleRate);
    m_soundTouch->setPitchSemiTones(0.0);
    m_soundTouch->flush();
    
    //Rezise temporary buffer
    m_buff.resize(totalNumInputChannels * samplesPerBlock);

    //Report latency to host
    int latency = m_soundTouch->getSetting(SETTING_INITIAL_LATENCY);

    //setLatencySamples(latency);
}

void Pitch::process(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels)
{
	int numSamples = buffer.getNumSamples();

	 float pitchValue = pow(2.0, (semitonesParam.get()->get() + centsParam.get()->get()) / 12);
    
    m_soundTouch->setPitch(pitchValue);

    for (int i = 0; i < totalNumOutputChannels; ++i)
        for (int j = 0; j < buffer.getNumSamples(); ++j)
            m_buff[j * totalNumOutputChannels + i] = buffer.getSample(i, j);

    m_soundTouch->putSamples(m_buff.data(), buffer.getNumSamples());

    //Here we check if SoundTouch has all the required samples available
    if (m_soundTouch->numSamples() >= buffer.getNumSamples())
    {
        m_soundTouch->receiveSamples(m_buff.data(), buffer.getNumSamples());

        // copy SoundTouch output samples to split format Juce buffer
        for (int i = 0; i < totalNumOutputChannels; ++i)
            for (int j = 0; j < buffer.getNumSamples(); ++j)
                buffer.setSample(i, j, m_buff[j * totalNumOutputChannels + i]);
    }
  
    else
    {
        // SoundTouch didn't have enough output samples, just output silence
        buffer.clear();
    }
}

/**
* Function for setting the pitch engine parameters.
*/
void Pitch::setParameter(int index, float newValue) 
{
    switch (index) 
    {
    case 0:
        *semitonesParam = newValue;
        break;
    
    case 1:
        *centsParam = newValue;
    }
}

float Pitch::getParameter(int index)
{
    switch (index)
    {
    case 0:
        return *semitonesParam;
        break;
    case 1:
        return *centsParam;
        break;
    }



}
