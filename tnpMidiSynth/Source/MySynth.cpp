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
	  targetGain(0.0f),
	  currentGain(targetGain)
{
	volumeEnvelope = new ADSR();
	filter = new IIRFilter();
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
	oscillator.setFrequency(MidiMessage::getMidiNoteInHertz(midiNoteNumber), getSampleRate());
	level = velocity;

	volumeEnvelope->gate(1);
	filter->setCoefficients(IIRCoefficients::makeLowPass(getSampleRate(), 5000, 1.0));
}

void MySynthVoice::stopNote(float velocity, bool allowTailOff)
{
	volumeEnvelope->gate(0);
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
	for (int sample = 0; sample < numSamples; sample++)
	{
		// Avoid glicthes via volume increment.
		if (currentGain != targetGain)
		{
			currentGain += (targetGain - currentGain) / numSamples;
		}

		double soundwave = oscillator.getNextSample();
		double envelope = volumeEnvelope->process() * soundwave;
		double output = filter->processSingleSampleRaw(envelope);

		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
		{		
			outputBuffer.addSample(channel, startSample, output * level * currentGain);
		}
		startSample++;
	}

}

void MySynthVoice::getGainValue(float gain)
{
	targetGain = gain;
}

void MySynthVoice::getEnvelopeParameters(float attack, float decay, float sustain, float release)
{
	double sampleRate = getSampleRate();
	volumeEnvelope->setAttackRate(attack * sampleRate);
	volumeEnvelope->setDecayRate(decay * sampleRate);
	volumeEnvelope->setSustainLevel(sustain);
	volumeEnvelope->setReleaseRate(release * sampleRate);
}