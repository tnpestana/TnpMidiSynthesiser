/*
  ==============================================================================

    MyWavetable.h
    Created: 23 Apr 2018 5:42:10pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MyOscillator.h"

class MyWavetable
{
public:
	MyWavetable();
	~MyWavetable();

	void setFrequency(float, float);
	float getNextSample();

	static void createWavetable();
	static ScopedPointer<AudioSampleBuffer> wavetable;
	static int tableSize;

private:
	MyOscillator myOscillator;
	float currentIndex, tableDelta;
};