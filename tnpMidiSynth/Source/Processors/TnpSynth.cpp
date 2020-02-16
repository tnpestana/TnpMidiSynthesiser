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
    :
    frequency1(0.0f),
    frequency2(0.0f),
    velocityLevel(0.0),
	soundwave1(0.f),
	soundwave2(0.f),
	osc1Type(0),
	osc2Type(0),
	osc1Transpose(0),
	osc2Transpose(0),
	wOscillator1(),
	wOscillator2(),
	volumeEnvelope1(),
	volumeEnvelope2()
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
		float envelope = 0.0f;
		soundwave1 = processOscillator(wOscillator1, osc1Type, frequency1);
		
		if (osc2Toggle == 1)
		{
			soundwave2 = processOscillator(wOscillator2, osc2Type, frequency2);
			envelope = ((volumeEnvelope1.process() * soundwave1) * 0.5 + (volumeEnvelope2.process() * soundwave2) * 0.5) * velocityLevel;
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

float TnpSynthVoice::processOscillator(WavetableOscillator& oscillator, int oscType, float frequency)
{
    // Check the frequency played to choose which wavetable to use
	switch (oscType)
	{
	case 0:
		return oscillator.getNextSample(WavetableOscillator::sineTable);
		break;
	case 1:
		return oscillator.getNextSample(WavetableOscillator::harmonicTable);
		break;
	case 2:
		if (frequency <= 987.78 /*B5*/)
			return oscillator.getNextSample(WavetableOscillator::squareTable);
		else if (frequency > 987.78 /*B5*/ && frequency <= 1975.55 /*B6*/)
			return oscillator.getNextSample(WavetableOscillator::squareTableB5);
		else if (frequency > 1975.55 /*B6*/ && frequency <= 3951.1 /*B7*/)
			return oscillator.getNextSample(WavetableOscillator::squareTableB6);
		else
			return oscillator.getNextSample(WavetableOscillator::squareTableB7);
		break;
	case 3:
		if (frequency <= 987.78 /*B5*/)
			return oscillator.getNextSample(WavetableOscillator::triangleTable);
		else if (frequency > 987.78 /*B5*/ && frequency <= 1975.55 /*B6*/)
			return oscillator.getNextSample(WavetableOscillator::triangleTableB5);
		else if (frequency > 1975.55 /*B6*/ && frequency <= 3951.1 /*B7*/)
			return oscillator.getNextSample(WavetableOscillator::triangleTableB6);
		else
			return oscillator.getNextSample(WavetableOscillator::triangleTableB7);
		break;
	case 4:
		if (frequency <= 1975.55 /*B6*/)
			return oscillator.getNextSample(WavetableOscillator::sawtoothTable);
		else if (frequency > 1975.55 /*B6*/ && frequency <= 3951.1 /*B7*/)
			return oscillator.getNextSample(WavetableOscillator::sawtoothTableB6);
		else if (frequency > 3951.1 /*B7*/ && frequency <= 7902.21 /*B8*/)
			return oscillator.getNextSample(WavetableOscillator::sawtoothTableB7);
		else
			return oscillator.getNextSample(WavetableOscillator::sawtoothTableB8);
		break;
	default:
		return 0.0;
		break;
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
