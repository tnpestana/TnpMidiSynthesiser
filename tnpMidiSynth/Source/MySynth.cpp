/*
  ==============================================================================

    MySynth.cpp
    Created: 14 Apr 2018 9:38:56pm
    Author:  tnpes

  ==============================================================================
*/

#include "MySynth.h"

//==============================================================================
MySynthSound::MySynthSound()
{
}

MySynthSound::~MySynthSound()
{
}

bool MySynthSound::appliesToNote(int midiNoteNumber)
{
	return true;
}

bool MySynthSound::appliesToChannel(int midiChannel)
{
	return true;
}

//==============================================================================
MySynthVoice::MySynthVoice()
	: level(0.0),
	frequency(0.0)
{
}

MySynthVoice::~MySynthVoice()
{
}

bool MySynthVoice::canPlaySound(SynthesiserSound * sound)
{
	return dynamic_cast<MySynthSound*> (sound) != nullptr;
}

void MySynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition)
{
	frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);

	level = velocity;
}

void MySynthVoice::stopNote(float velocity, bool allowTailOff)
{
	allowTailOff = true;

	if (velocity == 0)
		clearCurrentNote();
}

void MySynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void MySynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void MySynthVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	oscillator.setFrequency(440.0f, getSampleRate());

	for (int sample = 0; sample < numSamples; sample++)
	{
		double output = oscillator.getNextSample();

		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
		{
			outputBuffer.addSample(channel, startSample, output);
		}
		startSample++;
	}
}

void MySynthVoice::getEnvelopeParameters(float attack, float decay, float sustain, float release)
{
	double sampleRate = getSampleRate();
}

void MySynthVoice::getReverbParameters(float dryWet, float roomSize, float damping)
{
}
