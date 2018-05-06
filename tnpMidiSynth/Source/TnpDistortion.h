/*
  ==============================================================================

    TnpDistortion.h
    Created: 6 May 2018 8:10:43pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TnpDistortion
{
public:
	TnpDistortion();
	~TnpDistortion();

	void setParameters(float driveValue, float rangeValue, float mixValue);
	float processSample(float sample);

private:
	float drive, range, mix, output;
};