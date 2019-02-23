/*
  ==============================================================================

    TnpLookAndFeel.h
    Created: 23 Feb 2019 4:18:19pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TnpLookAndFeel : public LookAndFeel_V4
{
public:
	void drawRotarySlider(Graphics &g,
		int x, int y,
		int width, int height,
		float sliderPos,								// slider current value
		float rotaryStartAngle, float rotaryEndAngle,	// full motion angle
		Slider &slider) override;

	void drawLinearSlider(Graphics&, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle, Slider&) override;
};