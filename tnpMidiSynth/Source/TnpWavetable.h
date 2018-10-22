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
	float getNextSample(AudioSampleBuffer* currentTable);

	static void createWavetable();
	static void createSine();
	static void createSawTriSquare();

	static ScopedPointer<AudioSampleBuffer> sinetable;
	static ScopedPointer<AudioSampleBuffer> sawtable;
	static ScopedPointer<AudioSampleBuffer> tritable;
	static ScopedPointer<AudioSampleBuffer> squaretable;

	static int tableSize;

private:
	float currentIndex, tableDelta;
};
