/*
  ==============================================================================

    TnpLFO.cpp
    Created: 30 Aug 2018 1:29:02pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpLFO.h"

TnpLFO::TnpLFO()
	: depth(50.0f),
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
}

void TnpLFO::processAudioFrame(float* sample)
{
	float yn = 0;
	yn = oscillator.sineWave();
	yn = yn / 2 + 0.5;

	float GnL = 1.0;
	float GnR = 1.0;
	float monoIn = 0.0;

	GnL = calculateGainFactor(yn);

	/*else
	{
		if (numChannels == 1)
			monoIn = *sample;
		//else
			//monoIn = 0.5 * (*sample + inputBuffer[1]);

		calculatePanFactor(yn, &GnL, &GnR);
	}*/

	*sample = *sample * GnL;

	/*if (inputChannels == 1 && outputChannels == 2)
		outputBuffer[1] = outputBuffer[0];

	if (inputChannels == 2 && outputChannels == 2)
	{
		if (mode == 0)
		{
			outputBuffer[1] = inputBuffer[1] * GnL;
		}
		else
		{
			outputBuffer[1] = inputBuffer[1] * GnR;
		}
	}*/
}

float TnpLFO::calculateGainFactor(float LFOSample)
{
	float output = LFOSample * (depth / 100.0f);
	output += 1 - depth / 100.0f;
	return output;
}

float TnpLFO::calculatePanFactor(float LFOSample, float * leftVolume, float * rightVolume)
{
	float pan = ((depth / 100.0f) * LFOSample + 1) * MathConstants<float>::pi / 4.0f;

	*rightVolume = cos(pan);
	*leftVolume = sin(pan);
	return 0.0f;
}
