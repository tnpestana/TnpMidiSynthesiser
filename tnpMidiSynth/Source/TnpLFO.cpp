/*
  ==============================================================================

    TnpLFO.cpp
    Created: 30 Aug 2018 1:29:02pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "TnpLFO.h"

TnpLFO::TnpLFO()
	: depth(100.0f),
	rate(0.5f),
	sampleRate(0),
	oscillator()
{
}

TnpLFO::~TnpLFO()
{
}

void TnpLFO::prepareToPLay(double newSampleRate)
{
	sampleRate = newSampleRate;
	oscillator.setFrequency(rate, sampleRate);
}

void TnpLFO::processAudioFrame(float* sample)
{
	float lfo = 0;
	oscillator.setFrequency(rate, sampleRate);
	lfo = oscillator.sineWave();
	lfo = lfo / 2 + 0.5;

	float gainFactor = 1.0;

	gainFactor = calculateGainFactor(lfo);

	*sample = *sample * gainFactor;
}

float TnpLFO::calculateGainFactor(float LFOSample)
{
	float output = LFOSample * (depth / 100.0f);
	output += 1 - depth / 100.0f;
	return output;
}

void TnpLFO::updateParameters(float depth, float rate)
{
	this->depth = depth;
	this->rate = rate;
}

/*float TnpLFO::calculatePanFactor(float LFOSample, float * leftVolume, float * rightVolume)
{
	float pan = ((depth / 100.0f) * LFOSample + 1) * MathConstants<float>::pi / 4.0f;

	*rightVolume = cos(pan);
	*leftVolume = sin(pan);
	return 0.0f;
}*/
