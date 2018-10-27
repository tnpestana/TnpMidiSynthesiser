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
	static void createHarmonicSine();
	static void createSawTriSquare();

	static std::unique_ptr<AudioSampleBuffer> sineTable;
	static std::unique_ptr<AudioSampleBuffer> harmonicSineTable;
	static std::unique_ptr<AudioSampleBuffer> sawTable;
	static std::unique_ptr<AudioSampleBuffer> triTable;
	static std::unique_ptr<AudioSampleBuffer> squareTable;

	static int tableSize;

private:
	float currentIndex, frequency;
	float tableDelta;
};
