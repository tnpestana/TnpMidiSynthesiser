/*
  ==============================================================================

    TnpSynth.cpp
    Created: 14 Apr 2018 9:38:56pm
    Author:  Tiago Pestana

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
	oscType(0),
	transposeValue(0),
	wOscillator(),
	volumeEnvelope(),
	frequency(0.0f)
{
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
	frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber + transposeValue);
	wOscillator.setFrequency(frequency, getSampleRate());
	velocityLevel = velocity;

	volumeEnvelope.gate(1);
}

void TnpSynthVoice::stopNote(float velocity, bool allowTailOff)
{
	volumeEnvelope.gate(0);
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
		switch (oscType)
		{
		case 0:
			soundwave = wOscillator.getNextSample(WavetableOscillator::sineTable);
			break;
		case 1:
			soundwave = wOscillator.getNextSample(WavetableOscillator::harmonicTable);
			break;
		case 2:
			// Check the frequency played to choose which wavetable to use
			if (frequency <= 987.78 /*B5*/)
				soundwave = wOscillator.getNextSample(WavetableOscillator::squareTable);
			else if (frequency > 987.78 /*B5*/ && frequency <= 1975.55 /*B6*/)
				soundwave = wOscillator.getNextSample(WavetableOscillator::squareTableB5);
			else if (frequency > 1975.55 /*B6*/ && frequency <= 3951.1 /*B7*/)
				soundwave = wOscillator.getNextSample(WavetableOscillator::squareTableB6);
			else
				soundwave = wOscillator.getNextSample(WavetableOscillator::squareTableB7);
			break;
		case 3:
			// Check the frequency played to choose which wavetable to use
			if (frequency <= 987.78 /*B5*/)
				soundwave = wOscillator.getNextSample(WavetableOscillator::triangleTable);
			else if (frequency > 987.78 /*B5*/ && frequency <= 1975.55 /*B6*/)
				soundwave = wOscillator.getNextSample(WavetableOscillator::triangleTableB5);
			else if (frequency > 1975.55 /*B6*/ && frequency <= 3951.1 /*B7*/)
				soundwave = wOscillator.getNextSample(WavetableOscillator::triangleTableB6);
			else
				soundwave = wOscillator.getNextSample(WavetableOscillator::triangleTableB7);
			break;
		case 4:
			// Check the frequency played to choose which wavetable to use
			if (frequency <= 1975.55 /*B6*/)
				soundwave = wOscillator.getNextSample(WavetableOscillator::sawtoothTable);
			else if (frequency > 1975.55 /*B6*/ && frequency <= 3951.1 /*B7*/)
				soundwave = wOscillator.getNextSample(WavetableOscillator::sawtoothTableB6);
			else if (frequency > 3951.1 /*B7*/ && frequency <= 7902.21 /*B8*/)
				soundwave = wOscillator.getNextSample(WavetableOscillator::sawtoothTableB7);
			else
				soundwave = wOscillator.getNextSample(WavetableOscillator::sawtoothTableB8);
			break;
		default:
			soundwave = 0.0;
			break;
		}

		float envelope = volumeEnvelope.process() * soundwave * velocityLevel;

		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
		{		
			outputBuffer.addSample(channel, startSample, envelope);
		}
		startSample++;
	}
}

// The main apps processor needs to access this method to pass the valueTreeState envelope paremeter values.
void TnpSynthVoice::getEnvelopeParameters(float attack, float decay, float sustain, float release)
{
	double sampleRate = getSampleRate();
	volumeEnvelope.setAttackRate(attack * sampleRate);
	volumeEnvelope.setDecayRate(decay * sampleRate);
	volumeEnvelope.setSustainLevel(sustain);
	volumeEnvelope.setReleaseRate(release * sampleRate);
}

void TnpSynthVoice::getOscillatorType(float input)
{
	oscType = (int)input;
}

void TnpSynthVoice::getTransposeValue(float transpose)
{
	transposeValue = (int)transpose;
}