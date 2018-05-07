/*
  ==============================================================================

    TnpDistortion.cpp
    Created: 6 May 2018 8:10:43pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpDistortion.h"

TnpDistortion::TnpDistortion()
:	drive(0.f),
	range(0.f),
	mix(0.f),
	output(0.f)
{
}

TnpDistortion::~TnpDistortion()
{
}

void TnpDistortion::setParameters(float drive, float range, float mix)
{
	this->drive = drive;
	this->range = range;
	this->mix = mix;
	this->output = 1 - (0.9 * mix);	// We reduce the output as the mix level increases to balance the result.
}

float TnpDistortion::processSample(float sample)
{
	// Distortion processing:
	// Store clean signal.
	float cleanSignal = sample;

	// Add distortion.
	float distortedSignal = cleanSignal * drive * range;

	// Return mix of clean and distorted signal.
	return (((((2.f / MathConstants<float>::pi) * atan(distortedSignal)) * mix) + (cleanSignal * (1.f - mix))) / 2) * output;
}
