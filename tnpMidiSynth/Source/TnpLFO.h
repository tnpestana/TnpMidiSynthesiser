/*
  ==============================================================================

    TnpLFO.h
    Created: 30 Aug 2018 1:29:02pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TnpOscillator.h"

class TnpLFO
{
public:
	TnpLFO();
	~TnpLFO();

	void prepareToPLay(double sampleRate);
	void processAudioFrame(float* buffer);
	void updateParameters(float depth, float rate);

private:
	float calculateGainFactor(float LFO);

	TnpOscillator oscillator;
	float sampleRate;
	float depth;
	float rate;
};