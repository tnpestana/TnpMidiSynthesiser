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
	toggleLFO(0.0f),
	oscillator(),
	wOscillator(),
	volumeEnvelope()
{
	lfo.prepareToPLay(getSampleRate());
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
	wOscillator.setFrequency(MidiMessage::getMidiNoteInHertz(midiNoteNumber + transposeValue), getSampleRate());
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
			//soundwave = oscillator.sineWave();
			soundwave = wOscillator.getNextSample(WavetableOscillator::sinetable);
			break;
		case 1:
			//soundwave = oscillator.squareWave();
			soundwave = wOscillator.getNextSample(WavetableOscillator::squaretable);
			break;
		case 2:
			//soundwave = oscillator.triangleWave();
			soundwave = wOscillator.getNextSample(WavetableOscillator::tritable);
			break;
		case 3:
			//soundwave = oscillator.sawtoothWave();
			soundwave = wOscillator.getNextSample(WavetableOscillator::sawtable);
			break;
		default:
			soundwave = 0.0;
			break;
		}
				

		float envelope = volumeEnvelope.process() * soundwave * velocityLevel;

		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
		{		
			if (toggleLFO != 0.0f)
			{
				lfo.processAudioFrame(&envelope);
			}
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

void TnpSynthVoice::getLfoParameters(float depth, float rate, float toggle)
{
	lfo.updateParameters(depth, rate);
	toggleLFO = toggle;
}

void TnpSynthVoice::getOscillatorType(float input)
{
	oscType = (int)input;
}

void TnpSynthVoice::getTransposeValue(float transpose)
{
	transposeValue = (int)transpose;
}