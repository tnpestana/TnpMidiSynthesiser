/*
  ==============================================================================

    TnpLFO.h
    Created: 30 Aug 2018 1:29:02pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TnpWavetable.h"

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
	int oscType;
    float depth;
    float rate;
    float mix;
	float sampleRate;
    WavetableOscillator wOscillator;
};
