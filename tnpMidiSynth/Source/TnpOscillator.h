/*
  ==============================================================================

    MyOscillator.h
    Created: 14 Apr 2018 9:58:24pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TnpOscillator
{
public:
	TnpOscillator();
	~TnpOscillator();

	void setFrequency(float, float);
	void updateAngle();
	void incrementModulo();
	float cosineWave();
	float sineWave();
	float squareWave();
	float triangleWave();
	float sawtoothWave();

private:
	float currentAngle, angleDelta, currentSample,
		frequency, cyclesPerSample;
	float modulo, increment, sampleRate;
};