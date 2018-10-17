/*
  ==============================================================================

    TnpWavetable.cpp
    Created: 17 Oct 2018 12:54:01pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpWavetable.h"

//==============================================================================
WavetableOscillator::WavetableOscillator()
	: currentIndex(0.0f),
	tableDelta(0.0f)
{
}

WavetableOscillator::~WavetableOscillator()
{
}

//==============================================================================
void WavetableOscillator::setFrequency(float frequency, float sampleRate)
{
	float tableSizeOverSampleRate = wavetable->getNumSamples() / sampleRate;
	tableDelta = frequency * tableSizeOverSampleRate;
}

float WavetableOscillator::getNextSample()
{
	float tableSize = wavetable->getNumSamples();

	int index0 = (int)currentIndex;
	int index1 = index0 == (tableSize - 1) ? 0 : index0 + 1;

	float fraction = currentIndex - (float)index0;

	const float* table = wavetable->getReadPointer(0);
	float value0 = table[index0];
	float value1 = table[index1];

	float currentSample = value0 + fraction * (value1 - value0);

	if ((currentIndex += tableDelta) > tableSize)
		currentIndex -= tableSize;

	return currentSample;
}

//==============================================================================
// Static class members
int WavetableOscillator::tableSize = 128;

ScopedPointer<AudioSampleBuffer> WavetableOscillator::wavetable = new AudioSampleBuffer();

void WavetableOscillator::createWavetable()
{
	wavetable->setSize(1, tableSize);
	float* samples = wavetable->getWritePointer(0);

	float angleDelta = MathConstants<double>::twoPi / (float)tableSize;
	float currentAngle = 0.0;

	for (int i = 0; i < tableSize; i++)
	{
		float sample = std::sin(currentAngle);
		samples[i] = (float)sample;
		currentAngle += angleDelta;
	}
}
