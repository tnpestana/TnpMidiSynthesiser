/*
  ==============================================================================

    TnpDistortion.cpp
    Created: 6 May 2018 8:10:43pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpDistortion.h"

TnpDistortion::TnpDistortion()
{

}

TnpDistortion::~TnpDistortion()
{

}

void TnpDistortion::setParameters(float driveValue, float rangeValue, float mixValue)
{
	drive = driveValue;
	range = rangeValue;
	mix = mixValue;
	output = 1 - (0.9 * mix);	// We reduce the output as the mix level increases to balance the result.
}

float TnpDistortion::processSample(float sample)
{
	// Distortion processing:
	// Store clean signal.
	float cleanSignal = sample;

	// Add distortion.
	float distortedSignal = cleanSignal * drive * range;

	// Apply distortion parameters.
	return (((((2.f / MathConstants<float>::pi) * atan(distortedSignal)) * mix) + (cleanSignal * (1.f - mix))) / 2) * output;
}
