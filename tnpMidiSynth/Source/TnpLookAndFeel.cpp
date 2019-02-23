/*
  ==============================================================================

    TnpLookAndFeel.cpp
    Created: 23 Feb 2019 4:18:19pm
    Author:  tnpes

  ==============================================================================
*/

#include "TnpLookAndFeel.h"

void TnpLookAndFeel::drawToggleButton(Graphics & g, ToggleButton & button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto fontSize = jmin(15.0f, button.getHeight() * 0.75f);
	auto tickWidth = fontSize * 1.1f;

	drawTickBox(g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
		tickWidth, tickWidth,
		button.getToggleState(),
		button.isEnabled(),
		shouldDrawButtonAsHighlighted,
		shouldDrawButtonAsDown);

	g.setColour(button.findColour(ToggleButton::textColourId));
	g.setFont(fontSize);

	if (!button.isEnabled())
		g.setOpacity(0.5f);

	g.drawFittedText(button.getButtonText(),
		button.getLocalBounds().withTrimmedLeft(roundToInt(tickWidth) + 10)
		.withTrimmedRight(2),
		Justification::centredLeft, 10);
}

void TnpLookAndFeel::drawTickBox(Graphics & g, Component & component, float x, float y, float w, float h, const bool ticked, const bool isEnabled, const bool shouldDrawButtonAsHighlighted, const bool shouldDrawButtonAsDown)
{
	ignoreUnused(isEnabled, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

	Rectangle<float> tickBounds(x, y, w, h);

	g.setColour(component.findColour(ToggleButton::tickDisabledColourId));
	//g.drawRoundedRectangle(tickBounds, 4.0f, 1.0f);
	g.fillEllipse(tickBounds.reduced(2.0f));

	g.setColour(component.findColour(ToggleButton::tickColourId));
	g.drawEllipse(tickBounds.reduced(2.0f), 1.0f);

	if (ticked)
	{
		g.setColour(component.findColour(ToggleButton::tickColourId));
		g.fillEllipse(tickBounds.reduced(4.0f));
		//auto tick = getTickShape(0.75f);
		//g.fillPath(tick, tick.getTransformToScaleToFit(tickBounds.reduced(4, 5).toFloat(), false));
	}
}

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

void TnpLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &slider)
{
	if (slider.isBar())
	{
		g.setColour(slider.findColour(Slider::trackColourId));
		g.fillRect(slider.isHorizontal() ? Rectangle<float>(static_cast<float> (x), y + 0.5f, sliderPos - x, height - 1.0f)
			: Rectangle<float>(x + 0.5f, sliderPos, width - 1.0f, y + (height - sliderPos)));
	}
	else
	{
		auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
		auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

		auto trackWidth = jmin(8.0f, slider.isHorizontal() ? height * 0.35f : width * 0.35f);

		Point<float> startPoint(slider.isHorizontal() ? x : x + width * 0.5f,
			slider.isHorizontal() ? y + height * 0.5f : height + y);

		Point<float> endPoint(slider.isHorizontal() ? width + x : startPoint.x,
			slider.isHorizontal() ? startPoint.y : y);

		Path backgroundTrack;
		backgroundTrack.startNewSubPath(startPoint);
		backgroundTrack.lineTo(endPoint);
		g.setColour(slider.findColour(Slider::backgroundColourId));
		g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

		Path valueTrack;
		Point<float> minPoint, maxPoint, thumbPoint;

		if (isTwoVal || isThreeVal)
		{
			minPoint = { slider.isHorizontal() ? minSliderPos : width * 0.5f,
				slider.isHorizontal() ? height * 0.5f : minSliderPos };

			if (isThreeVal)
				thumbPoint = { slider.isHorizontal() ? sliderPos : width * 0.5f,
				slider.isHorizontal() ? height * 0.5f : sliderPos };

			maxPoint = { slider.isHorizontal() ? maxSliderPos : width * 0.5f,
				slider.isHorizontal() ? height * 0.5f : maxSliderPos };
		}
		else
		{
			auto kx = slider.isHorizontal() ? sliderPos : (x + width * 0.5f);
			auto ky = slider.isHorizontal() ? (y + height * 0.5f) : sliderPos;

			minPoint = startPoint;
			maxPoint = { kx, ky };
		}

		auto thumbWidth = getSliderThumbRadius(slider);

		valueTrack.startNewSubPath(minPoint);
		valueTrack.lineTo(isThreeVal ? thumbPoint : maxPoint);
		g.setColour(slider.findColour(Slider::trackColourId));
		g.strokePath(valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

		if (!isTwoVal)
		{
			// replaces thumbWitdh with (trackWitdh - 2.0f) to draw a smaller thumb dial
			g.setColour(slider.findColour(Slider::thumbColourId));
			g.fillEllipse(Rectangle<float>(static_cast<float> (trackWidth - 2.0f), static_cast<float> (trackWidth - 2.0f)).withCentre(isThreeVal ? thumbPoint : maxPoint));
		}

		if (isTwoVal || isThreeVal)
		{
			auto sr = jmin(trackWidth, (slider.isHorizontal() ? height : width) * 0.4f);
			auto pointerColour = slider.findColour(Slider::thumbColourId);

			if (slider.isHorizontal())
			{
				drawPointer(g, minSliderPos - sr,
					jmax(0.0f, y + height * 0.5f - trackWidth * 2.0f),
					trackWidth * 2.0f, pointerColour, 2);
				drawPointer(g, maxSliderPos - trackWidth,
					jmin(y + height - trackWidth * 2.0f, y + height * 0.5f),
					trackWidth * 2.0f, pointerColour, 4);
			}
			else
			{
				drawPointer(g, jmax(0.0f, x + width * 0.5f - trackWidth * 2.0f),
					minSliderPos - trackWidth,
					trackWidth * 2.0f, pointerColour, 1);
				drawPointer(g, jmin(x + width - trackWidth * 2.0f, x + width * 0.5f), maxSliderPos - sr,
					trackWidth * 2.0f, pointerColour, 3);
			}
		}
	}
}
