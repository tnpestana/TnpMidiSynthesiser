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
	static void createWavetable();
	static void createSine();
	static void createSawTriSquare();

	static std::unique_ptr<AudioSampleBuffer> sinetable;
	static std::unique_ptr<AudioSampleBuffer> sawtable;
	static std::unique_ptr<AudioSampleBuffer> tritable;
	static std::unique_ptr<AudioSampleBuffer> squaretable;

	static int tableSize;

private:
	float currentIndex, tableDelta;
};
