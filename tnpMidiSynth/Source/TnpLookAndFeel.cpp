/*
  ==============================================================================

    TnpLookAndFeel.cpp
    Created: 23 Feb 2019 4:18:19pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpLookAndFeel.h"

void TnpLookAndFeel::drawRotarySlider(Graphics & g, int x, int y, int width,
	int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
	Slider & slider)
{
	float dialWidth = width - 20;
	float dialHeight = height - 20;
	float diameter = jmin(dialWidth, dialHeight);
	float radius = diameter / 2;
	float centreX = x + width / 2;
	float centreY = y + height / 2;
	float rx = centreX - radius;
	float ry = centreY - radius;
	float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));
	auto fillColor = slider.findColour(Slider::ColourIds::rotarySliderFillColourId);
	auto outlineColor = slider.findColour(Slider::ColourIds::rotarySliderOutlineColourId);
	auto thumbColor = slider.findColour(Slider::ColourIds::thumbColourId);

	Rectangle<float> dialArea(centreX, centreY, dialWidth, dialHeight);

	g.setColour(fillColor);
	g.fillEllipse(rx, ry, diameter, diameter);

	g.setColour(thumbColor);
	Path dialTick;
	dialTick.addRectangle(0, -radius, 2.0f, radius * 0.33);
	g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centreX, centreY));

	g.setColour(outlineColor);
	g.drawEllipse(rx, ry, diameter, diameter, 1.0f);
}