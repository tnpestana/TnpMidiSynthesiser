/*
  ==============================================================================

    MyWavetable.cpp
    Created: 23 Apr 2018 5:42:10pm
    Author:  tnpes

  ==============================================================================
*/

#include "MyWavetable.h"

//==============================================================================
MyWavetable::MyWavetable()
	: currentIndex(0.0f),
	tableDelta(0.0f)
{
}

MyWavetable::~MyWavetable()
{
}

//==============================================================================
void MyWavetable::setFrequency(float frequency, float sampleRate)
{
	float tableSizeOverSampleRate = wavetable->getNumSamples() / sampleRate;
	tableDelta = frequency * tableSizeOverSampleRate;
}

float MyWavetable::getNextSample()
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
int MyWavetable::tableSize = 128;

ScopedPointer<AudioSampleBuffer> MyWavetable::wavetable = new AudioSampleBuffer();

void MyWavetable::createWavetable()
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
