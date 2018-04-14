/*
  ==============================================================================

    MySynth.h
    Created: 14 Apr 2018 9:38:56pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MyOscillator.h"

//==============================================================================
class MySynthSound : public SynthesiserSound
{
public:
	MySynthSound();
	~MySynthSound();

	// Inherited via SynthesiserSound
	virtual bool appliesToNote(int midiNoteNumber) override;

	virtual bool appliesToChannel(int midiChannel) override;
};

//==============================================================================
class MySynthVoice : public SynthesiserVoice
{
public:
	MySynthVoice();
	~MySynthVoice();

	// Inherited via SynthesiserVoice
	virtual bool canPlaySound(SynthesiserSound *) override;
	virtual void startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition) override;
	virtual void stopNote(float velocity, bool allowTailOff) override;
	virtual void pitchWheelMoved(int newPitchWheelValue) override;
	virtual void controllerMoved(int controllerNumber, int newControllerValue) override;
	virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

	//==============================================================================
	void getEnvelopeParameters(float attack, float decay, float sustain, float release);
	void getReverbParameters(float dryWet, float roomSize, float damping);

private:
	double level;
	MyOscillator oscillator;
};
