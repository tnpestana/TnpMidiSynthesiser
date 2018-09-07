/*
  ==============================================================================

    TnpStereoDelay.cpp
    Created: 4 Aug 2018 6:10:56pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "TnpStereoDelay.h"

TnpStereoDelay::TnpStereoDelay()
{
}

TnpStereoDelay::~TnpStereoDelay()
{
}

void TnpStereoDelay::updateParams(float delayTime, float feedback, float wet)
{
	delayLeft.setDelayTime(delayTime);
	delayRight.setDelayTime(delayTime);

	delayLeft.setFeedback(feedback);
	delayRight.setFeedback(feedback);

	delayLeft.setWetMix(wet);
	delayRight.setWetMix(wet);
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