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

float MyOscillator::getNextSample()
{
	float currentSample = (0.995f * sineWave() + 0.005f * squareWave()) * 0.2;
	updateAngle();
	return currentSample;
}

float MyOscillator::sineWave()
{
	return std::sin(currentAngle);
}

float MyOscillator::squareWave()
{
	float sine = sineWave();
	return (sine < 0) ? 0 : 1;
}