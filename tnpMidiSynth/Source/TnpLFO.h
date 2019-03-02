/*
  ==============================================================================

    TnpLFO.h
    Created: 30 Aug 2018 1:29:02pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "tnpWavetable.h"

class TnpLFO
{
public:
	TnpLFO();
	~TnpLFO();

	void prepareToPLay(double sampleRate);
	void processAudioFrame(float* sample);
	void updateParameters(float depth, float rate, int oscType);

private:
	float calculateGainFactor(float LFO);

	WavetableOscillator wOscillator;
	
	int oscType;
	float sampleRate;
	float depth;
	float rate;
};