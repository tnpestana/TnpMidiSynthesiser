/*
  ==============================================================================

    DistortionEditor.cpp
    Created: 1 May 2018 8:47:46pm
    Author:  tnpes

  ==============================================================================
*/

#include "DistortionEditor.h"

DistortionEditor::DistortionEditor()
{
	addAndMakeVisible(driveSlider);
	driveSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	driveSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(rangeSlider);
	rangeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	rangeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(mixSlider);
	mixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	mixSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(outputSlider);
	outputSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	outputSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
}

DistortionEditor::~DistortionEditor()
{
}

void DistortionEditor::paint(Graphics& g)
{
	g.fillAll(Colours::mediumseagreen);
}

void DistortionEditor::resized()
{
	const int sliderWidth = getWidth() / 4;
	juce::Rectangle<int> area(getLocalBounds());
	driveSlider.setBounds(area.removeFromLeft(sliderWidth));
	rangeSlider.setBounds(area.removeFromLeft(sliderWidth));
	mixSlider.setBounds(area.removeFromLeft(sliderWidth));
	outputSlider.setBounds(area.removeFromLeft(sliderWidth));
}
