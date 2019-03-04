/*
  ==============================================================================

    TnpSynth.h
    Created: 14 Apr 2018 9:38:56pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TnpWavetable.h"
#include "ADSR/ADSR.h"


//==============================================================================
class TnpSynthSound : public SynthesiserSound
{
public:
	TnpSynthSound();
	~TnpSynthSound();

	// Inherited via SynthesiserSound
	virtual bool appliesToNote(int midiNoteNumber) override;

	virtual bool appliesToChannel(int midiChannel) override;
};

//==============================================================================
class TnpSynthVoice : public SynthesiserVoice
{
public:
	TnpSynthVoice();
	~TnpSynthVoice();

	// Inherited via SynthesiserVoice
	virtual bool canPlaySound(SynthesiserSound *) override;
	virtual void startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition) override;
	virtual void stopNote(float velocity, bool allowTailOff) override;
	virtual void pitchWheelMoved(int newPitchWheelValue) override;
	virtual void controllerMoved(int controllerNumber, int newControllerValue) override;
	virtual void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

	//==============================================================================
	float processOscillator(WavetableOscillator& oscillator, int oscType, float frequency);

	//==============================================================================
	void getEnvelopeParameters(float attack1, float decay1, float sustain1, float release1,
							   float attack2, float decay2, float sustain2, float release2, float osc2Toggle);
	void getOscillatorType(float osc1Type, float osc2Type);
	void getTransposeValue(float transpose1, float transpose2);

private:
	float frequency1, frequency2;
	double velocityLevel;
	float soundwave1, soundwave2;
	int osc1Type, osc1Transpose;
	int osc2Type, osc2Transpose;
	float osc2Toggle;
	WavetableOscillator wOscillator1;
	WavetableOscillator wOscillator2;
	ADSR volumeEnvelope1;
	ADSR volumeEnvelope2;
};
