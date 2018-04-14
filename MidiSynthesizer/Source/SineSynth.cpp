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

SineSynthSound::~SineSynthSound()
{
}

//==============================================================================
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
	: currentAngle(0.0),
	  angleDelta(0.0)
{

}

SineSynthVoice::~SineSynthVoice()
{
}

//==============================================================================
bool SineSynthVoice::canPlaySound(SynthesiserSound* sound)
{
	return dynamic_cast<SineSynthSound*> (sound) != nullptr;
}

void SineSynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition)
{
	currentAngle = 0.0;
	level = velocity * 0.5;

	const auto frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	const auto cyclesPerSample = frequency / getSampleRate();

	angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void SineSynthVoice::stopNote(float velocity, bool allowTailOff)
{
	clearCurrentNote();
	angleDelta = 0.0;
	level = 0.0;
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
		while (--numSamples >= 0)
		{
			auto currentSample = (float)(std::sin(currentAngle) * level);

			for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
				outputBuffer.addSample(i, startSample, currentSample);

			currentAngle += angleDelta;
			++startSample;
		}
	}
}



