/*
  ==============================================================================

    MyOscillator.cpp
    Created: 14 Apr 2018 9:58:24pm
    Author:  tnpes

  ==============================================================================
*/

#include "MyOscillator.h"

MyOscillator::MyOscillator()
	: currentAngle(0.0),
	angleDelta(0.0)
{
}

MyOscillator::~MyOscillator()
{
}

void MyOscillator::setFrequency(float frequency, float sampleRate)
{
	float cyclesPerSample = frequency / sampleRate;
	angleDelta = cyclesPerSample * MathConstants<float>::twoPi;
}

void MyOscillator::updateAngle()
{
	currentAngle += angleDelta;
	if (currentAngle >= MathConstants<float>::twoPi)
		currentAngle -= MathConstants<float>::twoPi;
}

float MyOscillator::sineWave()
{
	float currentSample = std::sin(currentAngle);
	updateAngle();
	return currentSample;
}

float MyOscillator::squareWave()
{
	float sine = std::sin(currentAngle);
	float currentSample = (sine < 0) ? -1 : 1;
	updateAngle();
	return currentSample;
}

float MyOscillator::triangleWave()
{
	float currentSample = std::asin(std::sin(currentAngle)) * 2.0 / MathConstants<float>::pi;
	updateAngle();
	return currentSample;
}


