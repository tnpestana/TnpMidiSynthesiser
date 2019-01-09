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
// Static class members
int WavetableOscillator::tableSize = 2047;

// Waveform tables
AudioSampleBuffer WavetableOscillator::sineTable(1, tableSize + 1);
AudioSampleBuffer WavetableOscillator::harmonicTable(1, tableSize + 1);

AudioSampleBuffer WavetableOscillator::sawtoothTable(1, tableSize + 1);
AudioSampleBuffer WavetableOscillator::sawtoothTableB6(1, tableSize + 1);
AudioSampleBuffer WavetableOscillator::sawtoothTableB7(1, tableSize + 1);
AudioSampleBuffer WavetableOscillator::sawtoothTableB8(1, tableSize + 1);

AudioSampleBuffer WavetableOscillator::triangleTable(1, tableSize + 1);
AudioSampleBuffer WavetableOscillator::triangleTableB5(1, tableSize + 1);
AudioSampleBuffer WavetableOscillator::triangleTableB6(1, tableSize + 1);
AudioSampleBuffer WavetableOscillator::triangleTableB7(1, tableSize + 1);

AudioSampleBuffer WavetableOscillator::squareTable(1, tableSize + 1);
AudioSampleBuffer WavetableOscillator::squareTableB5(1, tableSize + 1);
AudioSampleBuffer WavetableOscillator::squareTableB6(1, tableSize + 1);
AudioSampleBuffer WavetableOscillator::squareTableB7(1, tableSize + 1);


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
void WavetableOscillator::createWavetable(float sampleRate)
{
	createSine();
	createSawtooth();
	createSquare();
	createTriangle();
	createHarmonicSine();
}

void WavetableOscillator::createSine()
{
	sineTable.clear();

	float* samples = sineTable.getWritePointer(0);

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
	harmonicTable.clear();

	float* samples = harmonicTable.getWritePointer(0);

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
	sawtoothTable.clear();
	sawtoothTableB6.clear();
	sawtoothTableB7.clear();
	sawtoothTableB8.clear();

	float* samples = sawtoothTable.getWritePointer(0);
	float* samplesB6 = sawtoothTableB6.getWritePointer(0);
	float* samplesB7 = sawtoothTableB7.getWritePointer(0);
	float* samplesB8 = sawtoothTableB8.getWritePointer(0);

	int harmonics[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	float harmonicWeights[] = { 0.5f, 0.5f / 2.0f, 0.5f / 3.0f, 0.5f / 4.0f,
		0.5f / 5.0f, 0.5f / 6.0f, 0.5f / 7.0f, 0.5f / 8.0f, 0.5f / 9.0f, 0.5f / 10.0f };

	for (int harmonic = 0; harmonic < numElementsInArray(harmonics); ++harmonic)
	{
		float angleDelta = MathConstants<double>::twoPi / (float)(tableSize) * harmonics[harmonic];
		float currentAngle = 0.0;

		for (int i = 0; i < tableSize; i++)
		{
			float sample = std::sin(currentAngle);
			if (harmonic < 5)
				samplesB6[i] += (float)sample * harmonicWeights[harmonic];
			if (harmonic < 2)
				samplesB7[i] += (float)sample * harmonicWeights[harmonic];
			if (harmonic < 1)
				samplesB8[i] += (float)sample * harmonicWeights[harmonic];
			samples[i] += (float)sample * harmonicWeights[harmonic];
			currentAngle += angleDelta;
		}
	}
	samples[tableSize] = samples[0];
	samplesB6[tableSize] = samplesB6[0];
	samplesB7[tableSize] = samplesB7[0];
	samplesB8[tableSize] = samplesB8[0];
}

void WavetableOscillator::createSquare()
{
	squareTable.clear();
	squareTableB5.clear();
	squareTableB6.clear();
	squareTableB7.clear();

	float* samples = squareTable.getWritePointer(0);
	float* samplesB5 = squareTableB5.getWritePointer(0);
	float* samplesB6 = squareTableB6.getWritePointer(0);
	float* samplesB7 = squareTableB7.getWritePointer(0);

	int harmonics[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	float harmonicWeights[] = { 0.5f, 0.5f / 3.0f, 0.5f / 5.0f, 0.5f / 7.0f,
		0.5f / 9.0f, 0.5f / 11.0f, 0.5f / 13.0f, 0.5f / 15.0f, 0.5f / 17.0f, 0.5f / 19.0f };

	for (int harmonic = 0; harmonic < numElementsInArray(harmonics); ++harmonic)
	{
		float angleDelta = MathConstants<double>::twoPi / (float)(tableSize) * harmonics[harmonic];
		float currentAngle = 0.0;

		for (int i = 0; i < tableSize; i++)
		{
			float sample = std::sin(currentAngle);
			if (harmonic < 5)
				samplesB5[i] += (float)sample * harmonicWeights[harmonic];
			if (harmonic < 3)
				samplesB6[i] += (float)sample * harmonicWeights[harmonic];
			if (harmonic < 1)
				samplesB7[i] += (float)sample * harmonicWeights[harmonic];
			samples[i] += (float)sample * harmonicWeights[harmonic];
			currentAngle += angleDelta;
		}
	}
	samples[tableSize] = samples[0];
	samplesB5[tableSize] = samplesB5[0];
	samplesB6[tableSize] = samplesB6[0];
	samplesB7[tableSize] = samplesB7[0];
}

void WavetableOscillator::createTriangle()
{
	triangleTable.clear();
	triangleTableB5.clear();
	triangleTableB6.clear();
	triangleTableB7.clear();

	float* samples = triangleTable.getWritePointer(0);
	float* samplesB5 = triangleTableB5.getWritePointer(0);
	float* samplesB6 = triangleTableB6.getWritePointer(0);
	float* samplesB7 = triangleTableB7.getWritePointer(0);
	

	int harmonics[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	float harmonicWeights[] = { 0.5f, -0.5f / pow(3.0f, 2), 0.5f / pow(5.0f, 2),
		-0.5f / pow(7.0f, 2), 0.5f / pow(9.0f, 2), -0.5f / pow(11.0f, 2), 
		0.5f / pow(13.0f, 2), -0.5f / pow(15.0f, 2), 0.5f / pow(17.0f, 2), 
		-0.5f / pow(19.0f, 2) };

	for (int harmonic = 0; harmonic < numElementsInArray(harmonics); ++harmonic)
	{
		float angleDelta = MathConstants<double>::twoPi / (float)(tableSize) * harmonics[harmonic];
		float currentAngle = 0.0;

		for (int i = 0; i < tableSize; i++)
		{
			float sample = std::sin(currentAngle);
			if (harmonic < 5)
				samplesB5[i] += (float)sample * harmonicWeights[harmonic];
			if (harmonic < 3)
				samplesB6[i] += (float)sample * harmonicWeights[harmonic];
			if (harmonic < 1)
				samplesB7[i] += (float)sample * harmonicWeights[harmonic];
			samples[i] += (float)sample * harmonicWeights[harmonic];
			currentAngle += angleDelta;
		}
	}
	samples[tableSize] = samples[0];
	samplesB5[tableSize] = samplesB5[0];
	samplesB6[tableSize] = samplesB6[0];
	samplesB7[tableSize] = samplesB7[0];
}

