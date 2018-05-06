/*
  ==============================================================================

    MyWavetable.h
    Created: 23 Apr 2018 5:42:10pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TnpOscillator.h"

class TnpWavetable
{
public:
	TnpWavetable();
	~TnpWavetable();

	void setFrequency(float, float);
	float getNextSample();

	static void createWavetable();
	static ScopedPointer<AudioSampleBuffer> wavetable;
	static int tableSize;

private:
	TnpOscillator myOscillator;
	float currentIndex, tableDelta;
};