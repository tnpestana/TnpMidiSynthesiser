/*
  ==============================================================================

    TnpWavetable.h
    Created: 17 Oct 2018 12:54:01pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class WavetableOscillator
{
public:
	WavetableOscillator();
	~WavetableOscillator();

	void setFrequency(float, float);
	float getNextSample(AudioSampleBuffer& currentTable);

	// Static public class members
	static void createWavetable(float sampleRate);
	static void createSine();
	static void createSawtooth();
	static void createSquare();
	static void createTriangle();
	static void createHarmonicSine();

	// Waveforms
	static AudioSampleBuffer sineTable;
	static AudioSampleBuffer harmonicTable;
	static AudioSampleBuffer sawtoothTable;
	static AudioSampleBuffer triangleTable;
	static AudioSampleBuffer squareTable;

	static int tableSize;

private:
	float currentIndex, frequency;
	float tableDelta;
};
