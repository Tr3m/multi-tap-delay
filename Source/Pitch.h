#pragma once
#include <JuceHeader.h>
#include "SoundTouch.h"

class Pitch
{

public:

	Pitch();
	~Pitch();

	
	void prepare(double sampleRate, int samplesPerBlock, int totalNumInputChannels);
	void process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages, int numInputChannels, int numOutputChannels);

	void setParameter(int index, float newValue);
	float getParameter(int index);

	enum Parameters {
		semitones = 0,
		cents

	};
	

private:

	std::unique_ptr<soundtouch::SoundTouch> m_soundTouch;
	std::vector<float> m_buff;

	std::unique_ptr<juce::AudioParameterFloat> semitonesParam;
    std::unique_ptr<juce::AudioParameterFloat> centsParam;
};