/*
  ==============================================================================

    MyOscillator.cpp
    Created: 14 Apr 2018 9:58:24pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "TnpOscillator.h"

TnpOscillator::TnpOscillator()
	: currentAngle(0.f),
	  angleDelta(0.f),
	  modulo(0.f),
	  increment(0.f)
{
}

TnpOscillator::~TnpOscillator()
{
}

void TnpOscillator::setFrequency(float frequency, float sampleRate)
{
	this->frequency = frequency;
	this->sampleRate = sampleRate;
	increment = frequency / sampleRate;
	angleDelta = increment * MathConstants<float>::twoPi;
}

void TnpOscillator::updateAngle()
{
	currentAngle += angleDelta;
	if (currentAngle >= MathConstants<float>::twoPi)
		currentAngle -= MathConstants<float>::twoPi;
}

void TnpOscillator::incrementModulo()
{
	// increment angle
	modulo += increment;

	// modulo wrap test
	if (modulo >= 1.f)
		modulo -= 1.f;
}

float TnpOscillator::cosineWave()
{
	float currentSample = std::cos(currentAngle);
	updateAngle();
	return currentSample;
}

float TnpOscillator::sineWave()
{
	float currentSample = std::sin(currentAngle);
	updateAngle();
	return currentSample;
}

float TnpOscillator::squareWave()
{
	float currentSample = modulo > 0.5 ? -1 : 1;
	incrementModulo();
	return currentSample;
}

float TnpOscillator::triangleWave()
{
	// (2.0 * modulo - 1.f) = sawtooth wave
	float currentSample = 2.f * fabs(2.f * modulo - 1.f) - 1.f;

	incrementModulo();

	// return sample
	return currentSample;
}

float TnpOscillator::sawtoothWave()
{	
	// unipolar to bipolar
	float currentSample = 2.0 * modulo - 1.f;

	incrementModulo();
	
	// return sample
	return currentSample;
}