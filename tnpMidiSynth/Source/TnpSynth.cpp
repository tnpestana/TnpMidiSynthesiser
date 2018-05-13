/*
  ==============================================================================

    MySynth.cpp
    Created: 14 Apr 2018 9:38:56pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpSynth.h"

//==============================================================================
TnpSynthSound::TnpSynthSound()
{
}

TnpSynthSound::~TnpSynthSound()
{
}

bool TnpSynthSound::appliesToNote(int midiNoteNumber)
{
	return true;
}

bool TnpSynthSound::appliesToChannel(int midiChannel)
{
	return true;
}

//==============================================================================
TnpSynthVoice::TnpSynthVoice()
	: velocityLevel(0.0),
	soundwave(0.f),
	transposeValue(0)
{
	volumeEnvelope = new ADSR();
}

TnpSynthVoice::~TnpSynthVoice()
{
}

bool TnpSynthVoice::canPlaySound(SynthesiserSound * sound)
{
	return dynamic_cast<TnpSynthSound*> (sound) != nullptr;
}

void TnpSynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition)
{
	oscillator.setFrequency(MidiMessage::getMidiNoteInHertz(midiNoteNumber + transposeValue), getSampleRate());
	velocityLevel = velocity;

	volumeEnvelope->gate(1);
}

void TnpSynthVoice::stopNote(float velocity, bool allowTailOff)
{
	volumeEnvelope->gate(0);
	allowTailOff = true;

	if (velocity == 0)
		clearCurrentNote();
}

void TnpSynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void TnpSynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void TnpSynthVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	for (int sample = 0; sample < numSamples; sample++)
	{

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

		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
		{		
			// Multiply the output by the velocity level and the "gain" parameter.
			outputBuffer.addSample(channel, startSample, envelope * velocityLevel);
		}
		startSample++;
	}

}

// The main apps processor needs to access this method to pass the valueTreeState envelope paremeter values.
void TnpSynthVoice::getEnvelopeParameters(float attack, float decay, float sustain, float release)
{
	double sampleRate = getSampleRate();
	volumeEnvelope->setAttackRate(attack * sampleRate);
	volumeEnvelope->setDecayRate(decay * sampleRate);
	volumeEnvelope->setSustainLevel(sustain);
	volumeEnvelope->setReleaseRate(release * sampleRate);
}

void TnpSynthVoice::getOscillatorType(float input)
{
	oscType = (int)input;
}

void TnpSynthVoice::getTransposeValue(float transpose)
{
	transposeValue = (int)transpose;
}