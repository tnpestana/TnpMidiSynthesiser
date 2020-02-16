/*
  ==============================================================================

    TnpStereoDelay.h
    Created: 4 Aug 2018 6:10:56pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TnpDelayLine.h"

class TnpStereoDelay
{
public:
	TnpStereoDelay();
	~TnpStereoDelay();

	void updateParams(float delayTime, float feedback, float wet);

	void prepareToPlay(double sampleRate);
	void processAudio(float* inputBufferL, float* inputBufferR);

private:
	TnpDelayLine delayLeft, delayRight;
	float currentDelayTime, currentFeedback, currentMix;
};