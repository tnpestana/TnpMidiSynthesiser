/*
  ==============================================================================

    TnpLFO.cpp
    Created: 30 Aug 2018 1:29:02pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpLFO.h"

TnpLFO::TnpLFO()
	: depth(100.0f),
	rate(0.5f),
	mode(0.0f)
{
}

TnpLFO::~TnpLFO()
{
}

void TnpLFO::prepareToPLay(double sampleRate)
{
	oscillator.setFrequency(rate, sampleRate);
	this->sampleRate = sampleRate;
}

void TnpLFO::processAudioFrame(float* sample)
{
	float yn = 0;
	oscillator.setFrequency(rate, sampleRate);
	yn = oscillator.sineWave();
	yn = yn / 2 + 0.5;

	float GnL = 1.0;
	float GnR = 1.0;
	float monoIn = 0.0;

	GnL = calculateGainFactor(yn);

	*sample = *sample * GnL;
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

float TnpLFO::calculatePanFactor(float LFOSample, float * leftVolume, float * rightVolume)
{
	float pan = ((depth / 100.0f) * LFOSample + 1) * MathConstants<float>::pi / 4.0f;

	*rightVolume = cos(pan);
	*leftVolume = sin(pan);
	return 0.0f;
}
