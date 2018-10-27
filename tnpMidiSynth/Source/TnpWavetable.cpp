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

float WavetableOscillator::getNextSample(AudioSampleBuffer& currentTable)
{
	int index0 = (int)currentIndex;
	int index1 = index0 + 1;

	float fraction = currentIndex - (float)index0;

	const float* table = currentTable.getReadPointer(0);
	float value0 = table[index0];
	float value1 = table[index1];

	float currentSample = value0 + fraction * (value1 - value0);

	if ((currentIndex += tableDelta) > tableSize)
		currentIndex -= tableSize;

	return currentSample;
}

//==============================================================================
// Static class members
int WavetableOscillator::tableSize = 127;

std::unique_ptr<AudioSampleBuffer> WavetableOscillator::sinetable = std::make_unique<AudioSampleBuffer>();
std::unique_ptr<AudioSampleBuffer> WavetableOscillator::sawtable = std::make_unique<AudioSampleBuffer>();
std::unique_ptr<AudioSampleBuffer> WavetableOscillator::tritable = std::make_unique<AudioSampleBuffer>();
std::unique_ptr<AudioSampleBuffer> WavetableOscillator::squaretable = std::make_unique<AudioSampleBuffer>();

void WavetableOscillator::createWavetable()
{
	createSine();
	createSawTriSquare();
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

	samples[tableSize] = samples[0];
}

void WavetableOscillator::createSawTriSquare()
{
	sawtable->setSize(1, tableSize + 1);
	float* sawSamples = sawtable->getWritePointer(0);
	tritable->setSize(1, tableSize + 1);
	float* triSamples = tritable->getWritePointer(0);
	squaretable->setSize(1, tableSize + 1);
	float* squareSamples = squaretable->getWritePointer(0);

	float modulo = 0.5f;
	float increment = 1.0f / (float)tableSize;

	for (int i = 0; i < tableSize; i++)
	{
		// unipolar to bipolar
		sawSamples[i] = 2.0f * modulo - 1.0f;
		// triangle from saw
		triSamples[i] = 2.0f * fabs(sawSamples[i]) - 1.0f;
		// square wave
		squareSamples[i] = modulo > 0.5 ? 1 : -1;

		// increment angle
		modulo += increment;
		if (modulo >= 1.0f)
			modulo -= 1.0f;
	}
	sawSamples[tableSize] = sawSamples[0];
	triSamples[tableSize] = triSamples[0];
	squareSamples[tableSize] = squareSamples[0];
}


