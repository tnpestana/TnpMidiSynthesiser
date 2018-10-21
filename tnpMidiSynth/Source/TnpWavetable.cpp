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
	float tableSizeOverSampleRate = tableSize / sampleRate;
	tableDelta = frequency * tableSizeOverSampleRate;
}

float WavetableOscillator::getNextSample(AudioSampleBuffer* currentTable)
{
	int index0 = (int)currentIndex;
	int index1 = index0 == (tableSize - 1) ? 0 : index0 + 1;

	float fraction = currentIndex - (float)index0;

	const float* table = currentTable->getReadPointer(0);
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

ScopedPointer<AudioSampleBuffer> WavetableOscillator::sinetable = new AudioSampleBuffer();
ScopedPointer<AudioSampleBuffer> WavetableOscillator::sawtable = new AudioSampleBuffer();

void WavetableOscillator::createWavetable()
{
	createSine();
	createSaw();
}

void WavetableOscillator::createSine()
{
	sinetable->setSize(1, tableSize);
	float* samples = sinetable->getWritePointer(0);

	float angleDelta = MathConstants<double>::twoPi / (float)tableSize;
	float currentAngle = 0.0;

	for (int i = 0; i < tableSize; i++)
	{
		float sample = std::sin(currentAngle);
		samples[i] = (float)sample;
		currentAngle += angleDelta;
	}
}

void WavetableOscillator::createSaw()
{
	sawtable->setSize(1, tableSize);
	float* samples = sawtable->getWritePointer(0);

	float modulo = 0.5f;
	float increment = 1.0f / (float)tableSize;

	for (int i = 0; i < tableSize; i++)
	{
		// unipolar to bipolar
		samples[i] = 2.0 * modulo - 1;
		// increment angle
		modulo += increment;
		if (modulo >= 1.0f)
			modulo -= 1.0f;
	}
}


