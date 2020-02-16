/*
  ==============================================================================

    TnpStereoDelay.cpp
    Created: 4 Aug 2018 6:10:56pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "TnpStereoDelay.h"

TnpStereoDelay::TnpStereoDelay()
	: delayLeft(),
	delayRight(),
    currentDelayTime(0.0f),
    currentFeedback(0.0f),
    currentMix(0.0f)
{
}

TnpStereoDelay::~TnpStereoDelay()
{
}

void TnpStereoDelay::prepareToPlay(double sampleRate)
{
	delayLeft.resetDelay(sampleRate);
	delayRight.resetDelay(sampleRate);
}

void TnpStereoDelay::processAudio(float* inputBufferL, float* inputBufferR)
{
	delayLeft.processAudio(inputBufferL);
	delayRight.processAudio(inputBufferR);
}

void TnpStereoDelay::updateParams(float delayTime, float feedback, float wet)
{
	if (currentDelayTime != delayTime)
	{
		delayLeft.setDelayTime(delayTime);
		delayRight.setDelayTime(delayTime);
	}

	if (currentFeedback != feedback)
	{
		delayLeft.setFeedback(feedback);
		delayRight.setFeedback(feedback);
	}

	if (currentMix != wet)
	{
		delayLeft.setWetMix(wet);
		delayRight.setWetMix(wet);
	}
}
