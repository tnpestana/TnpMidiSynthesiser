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
	soundwave1(0.f),
	soundwave2(0.f),
	osc1Type(0),
	osc2Type(0),
	osc1Transpose(0),
	osc2Transpose(0),
	wOscillator1(),
	wOscillator2(),
	volumeEnvelope1(),
	volumeEnvelope2(),
	frequency1(0.0f),
	frequency2(0.0f)
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
	frequency1 = MidiMessage::getMidiNoteInHertz(midiNoteNumber + osc1Transpose);
	frequency2 = MidiMessage::getMidiNoteInHertz(midiNoteNumber + osc2Transpose);
	wOscillator1.setFrequency(frequency1, getSampleRate());
	wOscillator2.setFrequency(frequency2, getSampleRate());
	velocityLevel = velocity;

	volumeEnvelope1.gate(1);
	volumeEnvelope2.gate(1);
}

void TnpSynthVoice::stopNote(float velocity, bool allowTailOff)
{
	volumeEnvelope1.gate(0);
	volumeEnvelope2.gate(0);
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
		switch (osc1Type)
		{
		case 0:
			soundwave1 = wOscillator1.getNextSample(WavetableOscillator::sineTable);
			break;
		case 1:
			soundwave1 = wOscillator1.getNextSample(WavetableOscillator::harmonicTable);
			break;
		case 2:
			// Check the frequency played to choose which wavetable to use
			if (frequency1 <= 987.78 /*B5*/)
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::squareTable);
			else if (frequency1 > 987.78 /*B5*/ && frequency1 <= 1975.55 /*B6*/)
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::squareTableB5);
			else if (frequency1 > 1975.55 /*B6*/ && frequency1 <= 3951.1 /*B7*/)
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::squareTableB6);
			else
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::squareTableB7);
			break;
		case 3:
			// Check the frequency played to choose which wavetable to use
			if (frequency1 <= 987.78 /*B5*/)
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::triangleTable);
			else if (frequency1 > 987.78 /*B5*/ && frequency1 <= 1975.55 /*B6*/)
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::triangleTableB5);
			else if (frequency1 > 1975.55 /*B6*/ && frequency1 <= 3951.1 /*B7*/)
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::triangleTableB6);
			else
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::triangleTableB7);
			break;
		case 4:
			// Check the frequency played to choose which wavetable to use
			if (frequency1 <= 1975.55 /*B6*/)
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::sawtoothTable);
			else if (frequency1 > 1975.55 /*B6*/ && frequency1 <= 3951.1 /*B7*/)
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::sawtoothTableB6);
			else if (frequency1 > 3951.1 /*B7*/ && frequency1 <= 7902.21 /*B8*/)
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::sawtoothTableB7);
			else
				soundwave1 = wOscillator1.getNextSample(WavetableOscillator::sawtoothTableB8);
			break;
		default:
			soundwave1 = 0.0;
			break;
		}

		switch (osc2Type)
		{
		case 0:
			soundwave2 = wOscillator2.getNextSample(WavetableOscillator::sineTable);
			break;
		case 1:
			soundwave2 = wOscillator2.getNextSample(WavetableOscillator::harmonicTable);
			break;
		case 2:
			// Check the frequency played to choose which wavetable to use
			if (frequency2 <= 987.78 /*B5*/)
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::squareTable);
			else if (frequency2 > 987.78 /*B5*/ && frequency2 <= 1975.55 /*B6*/)
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::squareTableB5);
			else if (frequency2 > 1975.55 /*B6*/ && frequency2 <= 3951.1 /*B7*/)
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::squareTableB6);
			else
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::squareTableB7);
			break;
		case 3:
			// Check the frequency played to choose which wavetable to use
			if (frequency2 <= 987.78 /*B5*/)
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::triangleTable);
			else if (frequency2 > 987.78 /*B5*/ && frequency2 <= 1975.55 /*B6*/)
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::triangleTableB5);
			else if (frequency2 > 1975.55 /*B6*/ && frequency2 <= 3951.1 /*B7*/)
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::triangleTableB6);
			else
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::triangleTableB7);
			break;
		case 4:
			// Check the frequency played to choose which wavetable to use
			if (frequency2 <= 1975.55 /*B6*/)
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::sawtoothTable);
			else if (frequency2 > 1975.55 /*B6*/ && frequency2 <= 3951.1 /*B7*/)
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::sawtoothTableB6);
			else if (frequency2 > 3951.1 /*B7*/ && frequency2 <= 7902.21 /*B8*/)
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::sawtoothTableB7);
			else
				soundwave2 = wOscillator2.getNextSample(WavetableOscillator::sawtoothTableB8);
			break;
		default:
			soundwave2 = 0.0;
			break;
		}

		float envelope = 0.0f;

		if (osc2Toggle == 1)
		{
			envelope = volumeEnvelope1.process() * (soundwave1 * 0.5 + soundwave2 * 0.5) * velocityLevel;
		}
		else
		{
			envelope = volumeEnvelope1.process() * soundwave1 * velocityLevel;
		}

		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
		{		
			outputBuffer.addSample(channel, startSample, envelope);
		}
		startSample++;
	}
}

// The main apps processor needs to access this method to pass the valueTreeState envelope paremeter values.
void TnpSynthVoice::getEnvelopeParameters(float attack1, float decay1, float sustain1, float release1,
										  float attack2, float decay2, float sustain2, float release2, float osc2Toggle)
{
	double sampleRate = getSampleRate();

	volumeEnvelope1.setAttackRate(attack1 * sampleRate);
	volumeEnvelope1.setDecayRate(decay1 * sampleRate);
	volumeEnvelope1.setSustainLevel(sustain1);
	volumeEnvelope1.setReleaseRate(release1 * sampleRate);

	volumeEnvelope2.setAttackRate(attack2 * sampleRate);
	volumeEnvelope2.setDecayRate(decay2 * sampleRate);
	volumeEnvelope2.setSustainLevel(sustain2);
	volumeEnvelope2.setReleaseRate(release2 * sampleRate);
	this->osc2Toggle = osc2Toggle;
}

void TnpSynthVoice::getOscillatorType(float osc1Type, float osc2Type)
{
	this->osc1Type = (int)osc1Type;
	this->osc2Type = (int)osc2Type;
}

void TnpSynthVoice::getTransposeValue(float transpose1, float transpose2)
{
	osc1Transpose = (int)transpose1;
	osc2Transpose = (int)transpose2;
}