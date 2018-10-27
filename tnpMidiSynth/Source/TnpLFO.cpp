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
	wOscillator()
{
}

TnpLFO::~TnpLFO()
{
}

void TnpLFO::prepareToPLay(double newSampleRate)
{
	sampleRate = newSampleRate;
	wOscillator.setFrequency(rate, sampleRate);
}

void TnpLFO::processAudioFrame(float* sample)
{
	float lfo = 0;
	wOscillator.setFrequency(rate, sampleRate);
	switch(oscType)
	{
		case 0:
			lfo = wOscillator.getNextSample(*WavetableOscillator::sineTable);
			break;
		case 1:
			lfo = wOscillator.getNextSample(*WavetableOscillator::squareTable);
			break;
		case 2:
			lfo = wOscillator.getNextSample(*WavetableOscillator::triTable);
			break;
		case 3:
			lfo = wOscillator.getNextSample(*WavetableOscillator::sawTable);
			break;
		default:
			lfo = 0.0;
			break;
	}

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

void TnpLFO::updateParameters(float depth, float rate, int oscType)
{
	this->depth = depth;
	this->rate = rate;
	this->oscType = oscType;
}

/*float TnpLFO::calculatePanFactor(float LFOSample, float * leftVolume, float * rightVolume)
{
	float pan = ((depth / 100.0f) * LFOSample + 1) * MathConstants<float>::pi / 4.0f;

	*rightVolume = cos(pan);
	*leftVolume = sin(pan);
	return 0.0f;
}*/
