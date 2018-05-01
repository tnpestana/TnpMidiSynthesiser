/*
  ==============================================================================

    MyOscillator.h
    Created: 14 Apr 2018 9:58:24pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MyOscillator
{
public:
	MyOscillator();
	~MyOscillator();

	void setFrequency(float, float);
	void updateAngle();
	float sineWave();
	float squareWave();
	float triangleWave();

private:
	float currentAngle, angleDelta, currentSample;
};
