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
	frequency(0.0f),
	tableDelta(0.0f)
{
}

WavetableOscillator::~WavetableOscillator()
{
}

//==============================================================================
void WavetableOscillator::setFrequency(float frequency, float sampleRate)
{
	this->frequency = frequency;
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
int WavetableOscillator::tableSize = 2047;

std::unique_ptr<AudioSampleBuffer> WavetableOscillator::sineTable = std::make_unique<AudioSampleBuffer>();
std::unique_ptr<AudioSampleBuffer> WavetableOscillator::harmonicSineTable = std::make_unique<AudioSampleBuffer>();

std::unique_ptr<AudioSampleBuffer> WavetableOscillator::sawTable = std::make_unique<AudioSampleBuffer>();
std::unique_ptr<AudioSampleBuffer> WavetableOscillator::adSawTable = std::make_unique<AudioSampleBuffer>();

std::unique_ptr<AudioSampleBuffer> WavetableOscillator::triTable = std::make_unique<AudioSampleBuffer>();
std::unique_ptr<AudioSampleBuffer> WavetableOscillator::adTriTable = std::make_unique<AudioSampleBuffer>();

std::unique_ptr<AudioSampleBuffer> WavetableOscillator::squareTable = std::make_unique<AudioSampleBuffer>();
std::unique_ptr<AudioSampleBuffer> WavetableOscillator::adSquareTable = std::make_unique<AudioSampleBuffer>();

void WavetableOscillator::createWavetable(float sampleRate)
{
	createSine();
	createSawtooth();
	createSquare();
	createTriangle();
	createHarmonicSine();
	createSawTriSquare();
}

void WavetableOscillator::createSine()
{
	sineTable->setSize(1, tableSize + 1);
	sineTable->clear();

	float* samples = sineTable->getWritePointer(0);

		float angleDelta = MathConstants<double>::twoPi / (float)(tableSize);

		float currentAngle = 0.0;

		for (int i = 0; i < tableSize; i++)
		{
			float sample = std::sin(currentAngle);
			samples[i] += (float)sample;
			currentAngle += angleDelta;
		}

	samples[tableSize] = samples[0];
}

void WavetableOscillator::createHarmonicSine()
{
	harmonicSineTable->setSize(1, tableSize + 1);
	harmonicSineTable->clear();

	float* samples = harmonicSineTable->getWritePointer(0);

	/*
	int harmonics[] = { 1, 3, 5, 6, 7, 9, 13, 15 };
	float harmonicWeights[] = { 0.5f, 0.1f, 0.05f, 0.125f, 0.09f, 0.005,
	0.002f, 0.001f };
	*/

	int harmonics[] = { 1, 2, 4, 6 };
	float harmonicWeights[] = { 0.5f, 0.1f, 0.05f, 0.025f };

	for (int harmonic = 0; harmonic < numElementsInArray(harmonics); ++harmonic)
	{
		float angleDelta = MathConstants<double>::twoPi / (float)(tableSize) *
			harmonics[harmonic];

		float currentAngle = 0.0;

		for (int i = 0; i < tableSize; i++)
		{
			float sample = std::sin(currentAngle);
			samples[i] += (float)sample * harmonicWeights[harmonic];
			currentAngle += angleDelta;
		}
	}
	samples[tableSize] = samples[0];
}

void WavetableOscillator::createSawtooth()
{
	adSawTable->setSize(1, tableSize + 1);
	adSawTable->clear();

	float* samples = adSawTable->getWritePointer(0);

	int harmonics[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	float harmonicWeights[] = { 0.5f, 0.5f / 2.0f, 0.5f / 3.0f, 0.5f / 4.0f,
		0.5f / 5.0f, 0.5f / 6.0f, 0.5f / 7.0f, 0.5f / 8.0f, 0.5f / 9.0f, 0.5f / 10.0f };

	for (int harmonic = 0; harmonic < numElementsInArray(harmonics); ++harmonic)
	{
		float angleDelta = MathConstants<double>::twoPi / (float)(tableSize)*
			harmonics[harmonic];

		float currentAngle = 0.0;

		for (int i = 0; i < tableSize; i++)
		{
			float sample = std::sin(currentAngle);
			samples[i] += (float)sample * harmonicWeights[harmonic];
			currentAngle += angleDelta;
		}
	}
	samples[tableSize] = samples[0];
}

void WavetableOscillator::createSquare()
{
	adSquareTable->setSize(1, tableSize + 1);
	adSquareTable->clear();

	float* samples = adSquareTable->getWritePointer(0);

	int harmonics[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	float harmonicWeights[] = { 0.5f, 0.5f / 3.0f, 0.5f / 5.0f, 0.5f / 7.0f,
		0.5f / 9.0f, 0.5f / 11.0f, 0.5f / 13.0f, 0.5f / 15.0f, 0.5f / 17.0f, 0.5f / 19.0f };

	for (int harmonic = 0; harmonic < numElementsInArray(harmonics); ++harmonic)
	{
		float angleDelta = MathConstants<double>::twoPi / (float)(tableSize)*
			harmonics[harmonic];

		float currentAngle = 0.0;

		for (int i = 0; i < tableSize; i++)
		{
			float sample = std::sin(currentAngle);
			samples[i] += (float)sample * harmonicWeights[harmonic];
			currentAngle += angleDelta;
		}
	}
	samples[tableSize] = samples[0];
}

void WavetableOscillator::createTriangle()
{
	adTriTable->setSize(1, tableSize + 1);
	adTriTable->clear();

	float* samples = adTriTable->getWritePointer(0);

	int harmonics[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	float harmonicWeights[] = { 0.5f, 0.5f / pow(3.0f, 2), 0.5f / pow(5.0f, 2),
		0.5f / pow(7.0f, 2), 0.5f / pow(9.0f, 2), 0.5f / pow(11.0f, 2), 
		0.5f / pow(13.0f, 2), 0.5f / pow(15.0f, 2), 0.5f / pow(17.0f, 2), 
		0.5f / pow(19.0f, 2) };

	for (int harmonic = 0; harmonic < numElementsInArray(harmonics); ++harmonic)
	{
		float angleDelta = MathConstants<double>::twoPi / (float)(tableSize)*
			harmonics[harmonic];

		float currentAngle = 0.0;

		for (int i = 0; i < tableSize; i++)
		{
			float sample = std::sin(currentAngle);
			samples[i] += (float)sample * harmonicWeights[harmonic];
			currentAngle += angleDelta;
		}
	}
	samples[tableSize] = samples[0];
}

void WavetableOscillator::createSawTriSquare()
{
	sawTable->setSize(1, tableSize + 1);
	sawTable->clear();
	float* sawSamples = sawTable->getWritePointer(0);
	triTable->setSize(1, tableSize + 1);
	triTable->clear();
	float* triSamples = triTable->getWritePointer(0);
	squareTable->setSize(1, tableSize + 1);
	squareTable->clear();
	float* squareSamples = squareTable->getWritePointer(0);

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


