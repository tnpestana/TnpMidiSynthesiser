/*
  ==============================================================================

    TnpDelayLine.cpp
    Created: 4 Aug 2018 6:09:20pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpDelayLine.h"

TnpDelayLine::TnpDelayLine()
	: buffer(nullptr),
	delayLength(0.0),
	bufferSize(0),
	delayReadPosition(0),
	delayWritePosition(0),
	sampleRate(0),
	feedback(0.0),
	wetMix(0.0)
{
}

TnpDelayLine::~TnpDelayLine()
{
	delete[] buffer;
}

void TnpDelayLine::resetDelay()
{
	if (buffer)
		memset(buffer, 0, bufferSize);

	delayReadPosition = 0.0;
	delayWritePosition = 0.0;

	setupBuffer();
}

void TnpDelayLine::setSampleRate(double sampleRate)
{
	this->sampleRate = sampleRate;

	initBuffer();
}

void TnpDelayLine::initBuffer()
{
	// Set 2 second max delay in samples.
	bufferSize = (int)(2.0 * sampleRate);
	if (bufferSize < 1)
		bufferSize = 1;

	// delete old buffer
	if (buffer)
		delete[] buffer;

	// create new buffer
	buffer = new float[bufferSize];
	// flush new buffer
	memset(buffer, 0, bufferSize);
}

void TnpDelayLine::setFeedback(float feedback)
{
	this->feedback = feedback;
}

void TnpDelayLine::setWetMix(float wetMix)
{
	this->wetMix = wetMix;
}

void TnpDelayLine::setDelayTime(double delayTime_ms)
{
	delayLength = delayTime_ms;
	setupBuffer();
}

void TnpDelayLine::setupBuffer()
{
	delayInSamples = delayLength * sampleRate;

	delayReadPosition = (int)(delayWritePosition - delayInSamples);

	// Wrap delay read position to the buffers range.
	if (delayReadPosition < 0)
		delayReadPosition += bufferSize;
}

float TnpDelayLine::processAudio(float* inputBuffer)
{
	float output = 0.0;

	float yn = buffer[delayReadPosition];

	float xn = *inputBuffer;

	if (delayLength == 0)
		yn = xn;

	buffer[delayWritePosition] = xn + feedback * yn;

	output = (xn * (1 - wetMix)) + (yn * wetMix);

	*inputBuffer = output;

	delayReadPosition++;
	if (delayReadPosition >= bufferSize)
		delayReadPosition = 0;
	delayWritePosition++;
	if (delayWritePosition >= bufferSize)
		delayWritePosition = 0;


	return output;
}