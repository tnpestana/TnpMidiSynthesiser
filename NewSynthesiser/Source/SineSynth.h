/*
  ==============================================================================

    SineSynth.h
    Created: 20 Mar 2018 7:28:14pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class SineSynthSound :	public SynthesiserSound
{
public:
	SineSynthSound();
	~SineSynthSound();
	// Inherited via SynthesiserSound
	virtual bool appliesToNote(int midiNoteNumber) override;
	virtual bool appliesToChannel(int midiChannel) override;
};

//==============================================================================
class SineSynthVoice :	public SynthesiserVoice
{
public:
	SineSynthVoice();
	~SineSynthVoice();
	// Inherited via SynthesiserVoice
	virtual bool canPlaySound(SynthesiserSound *) override;
	virtual void startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition) override;
	virtual void stopNote(float velocity, bool allowTailOff) override;
	virtual void pitchWheelMoved(int newPitchWheelValue) override;
	virtual void controllerMoved(int controllerNumber, int newControllerValue) override;
	virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
private:
	double currentAngle, angleDelta, level;
};