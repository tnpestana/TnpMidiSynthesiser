/*
  ==============================================================================

    TnpDelayLine.h
    Created: 4 Aug 2018 6:09:20pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TnpDelayLine
{
public:
	TnpDelayLine();
	~TnpDelayLine();

	//==============================================================================
	void resetDelay();

	//==============================================================================
	void setSampleRate(double sampleRate);
	void initBuffer();

	void setFeedback(float feedback);
	void setWetMix(float wetMix);

	void setDelayTime(double delayTime_ms);
	void setupBuffer();

	void processAudio(float* inputBufferL);

private:

	float* buffer;
	int bufferSize;
	int delayReadPosition, delayWritePosition;
	int sampleRate;
	float delayLength, delayInSamples;
	double feedback, wetMix;
};
