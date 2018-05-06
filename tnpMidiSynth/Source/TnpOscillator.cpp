/*
  ==============================================================================

    MyOscillator.cpp
    Created: 14 Apr 2018 9:58:24pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpOscillator.h"

TnpOscillator::TnpOscillator()
	: currentAngle(0.0),
	angleDelta(0.0)
{
}

TnpOscillator::~TnpOscillator()
{
}

void TnpOscillator::setFrequency(float frequency, float sampleRate)
{
	frequencyHz = frequency;
	float cyclesPerSample = frequency / sampleRate;
	angleDelta = cyclesPerSample * MathConstants<float>::twoPi;
}

void TnpOscillator::updateAngle()
{
	currentAngle += angleDelta;
	if (currentAngle >= MathConstants<float>::twoPi)
		currentAngle -= MathConstants<float>::twoPi;
}

float TnpOscillator::sineWave()
{
	float currentSample = std::sin(currentAngle);
	updateAngle();
	return currentSample;
}

float TnpOscillator::squareWave()
{
	float sine = std::sin(currentAngle);
	float currentSample = ((sine < 0) ? -1 : 1 ) * 0.5;		//  Here I multiplied the output by 0.5 for
	updateAngle();											// output volume balance between waveforms.
	return currentSample;
}

float TnpOscillator::triangleWave()
{
	float currentSample = std::asin(std::sin(currentAngle)) * 2.0 / MathConstants<float>::pi;
	updateAngle();
	return currentSample;
}

float TnpOscillator::sawtoothWave()
{
	return 0.f;
}