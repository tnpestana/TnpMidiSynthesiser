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
	static AudioSampleBuffer sawtoothTableB6;
	static AudioSampleBuffer sawtoothTableB7;
	static AudioSampleBuffer sawtoothTableB8;

	static AudioSampleBuffer triangleTable;
	static AudioSampleBuffer triangleTableB5;
	static AudioSampleBuffer triangleTableB6;
	static AudioSampleBuffer triangleTableB7;

	static AudioSampleBuffer squareTable;
	static AudioSampleBuffer squareTableB5;
	static AudioSampleBuffer squareTableB6;
	static AudioSampleBuffer squareTableB7;


	static int tableSize;

private:
	float currentIndex, frequency;
	float tableDelta;
};
