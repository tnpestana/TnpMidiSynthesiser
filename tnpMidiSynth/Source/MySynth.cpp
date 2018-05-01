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
	targetGain(0.0),
	currentGain(targetGain),
	soundwave(0.f),
	filterFrequency(0.0)
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

	if(filterType == 0)
		filter->setCoefficients(IIRCoefficients::makeLowPass(getSampleRate(), filterFrequency, 1.0));
	else if(filterType == 1)
		filter->setCoefficients(IIRCoefficients::makeHighPass(getSampleRate(), filterFrequency, 1.0));

	volumeEnvelope->gate(1);
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

		//	Get initial wave via the oscillator object, process its volume with the envelope class
		// from ADSR files and filter it with JUCEs IIRFilter.
		switch (oscType)
		{
		case 0:
			soundwave = oscillator.sineWave();
			break;
		case 1:
			soundwave = oscillator.squareWave();
			break;
		case 2:
			soundwave = oscillator.triangleWave();
			break;
		default:
			soundwave = 0.0;
			break;
		}
				

		double envelope = volumeEnvelope->process() * soundwave;
		double filtered = filter->processSingleSampleRaw(envelope);

		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
		{		
			// Multiply the output by the velocity level and the "gain" parameter.
			outputBuffer.addSample(channel, startSample, filtered * level * currentGain);
		}
		startSample++;
	}

}

// The main apps processor needs to access this method to pass the valueTreeState gain paremeter value.
void MySynthVoice::getGainValue(float gain)
{
	targetGain = gain;
}

// The main apps processor needs to access this method to pass the valueTreeState envelope paremeter values.
void MySynthVoice::getEnvelopeParameters(float attack, float decay, float sustain, float release)
{
	double sampleRate = getSampleRate();
	volumeEnvelope->setAttackRate(attack * sampleRate);
	volumeEnvelope->setDecayRate(decay * sampleRate);
	volumeEnvelope->setSustainLevel(sustain);
	volumeEnvelope->setReleaseRate(release * sampleRate);
}

void MySynthVoice::getOscillatorType(float input)
{
	oscType = (int)input;
}

void MySynthVoice::getFilterParameters(float type, float frequency)
{
	filterType = type;
	filterFrequency = frequency;
}