/*
  ==============================================================================

    DistortionEditor.cpp
    Created: 1 May 2018 8:47:46pm
    Author:  tnpes

  ==============================================================================
*/

#include "DistortionEditor.h"

DistortionEditor::DistortionEditor(TnpMidiSynthAudioProcessor& p)
{
	addAndMakeVisible(driveLabel);
	driveLabel.setText("drive", dontSendNotification);
	driveLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(driveSlider);
	driveSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	driveSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "distortionDrive", driveSlider);

	addAndMakeVisible(rangeLabel);
	rangeLabel.setText("range", dontSendNotification);
	rangeLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(rangeSlider);
	rangeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	rangeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	rangeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "distortionRange", rangeSlider);

	addAndMakeVisible(mixLabel);
	mixLabel.setText("mix", dontSendNotification);
	mixLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mixSlider);
	mixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	mixSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	mixAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "distortionMix", mixSlider);
}

DistortionEditor::~DistortionEditor()
{
}

void DistortionEditor::paint(Graphics& g)
{
	g.fillAll(Colours::yellowgreen);

	getLookAndFeel().setColour(Label::backgroundColourId, Colours::yellowgreen);
}

void DistortionEditor::resized()
{
	const int sliderWidth = getWidth() / 3;
	juce::Rectangle<int> area(getLocalBounds());
	juce::Rectangle<int> labelArea(area.removeFromTop(20));
	driveLabel.setBounds(labelArea.removeFromLeft(sliderWidth));
	rangeLabel.setBounds(labelArea.removeFromLeft(sliderWidth));
	mixLabel.setBounds(labelArea.removeFromLeft(sliderWidth));

	juce::Rectangle<int> sliderArea(area.removeFromTop(getHeight()));
	driveSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
	rangeSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
	mixSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
}
