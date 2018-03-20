/*
  ==============================================================================

    SineSynth.cpp
    Created: 19 Mar 2018 5:09:21pm
    Author:  tnpes

  ==============================================================================
*/

#include "SineSynth.h"

//==============================================================================
SineSynthSound::SineSynthSound()
{
}

bool SineSynthSound::appliesToNote(int midiNoteNumber)
{
	return true;
}

bool SineSynthSound::appliesToChannel(int midiChannel)
{
	return true;
}

//==============================================================================
SineSynthVoice::SineSynthVoice()
	:	currentAngle(0.0),
		angleDelta(0.0),
		level(0.0)
{
}

bool SineSynthVoice::canPlaySound(SynthesiserSound* sound)
{
	return dynamic_cast<SineSynthSound*> (sound) != nullptr;
}

void SineSynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
	currentAngle = 0.0;
	level = velocity * 0.15;

	auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	auto cyclesPerSample = cyclesPerSecond / getSampleRate();

	angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void SineSynthVoice::stopNote(float velocity, bool allowTailOff)
{
	clearCurrentNote();
	angleDelta = 0.0;
}

void SineSynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SineSynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SineSynthVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	if (angleDelta != 0.0)
	{
		for (auto sample = 0; sample < numSamples; sample++)
		{
			float currentSample = (float)(std::sin(currentAngle) * level);
			 
			for (auto channel = 0; channel < outputBuffer.getNumChannels(); channel++)
				outputBuffer.addSample(channel, startSample, currentSample);

			currentAngle += angleDelta;
			++startSample;
		}
	}
}



