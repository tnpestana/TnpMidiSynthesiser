/*
  ==============================================================================

    SineSynth.h
    Created: 19 Mar 2018 5:09:21pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "PluginEditor.h"

class SineSynthSound : public SynthesiserSound
{
public:
	SineSynthSound();

	// Herdado por meio de SynthesiserSound
	virtual bool appliesToNote(int midiNoteNumber) override;
	virtual bool appliesToChannel(int midiChannel) override;
};

class SineSynthVoice : public SynthesiserVoice
{
public:
	SineSynthVoice();

	// Herdado por meio de SynthesiserVoice
	virtual bool canPlaySound(SynthesiserSound *) override;
	virtual void startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition) override;
	virtual void stopNote(float velocity, bool allowTailOff) override;
	virtual void pitchWheelMoved(int newPitchWheelValue) override;
	virtual void controllerMoved(int controllerNumber, int newControllerValue) override;
	virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
	double currentAngle, angleDelta, level;
};