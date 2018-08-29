/*
  ==============================================================================

    DistortionEditor.cpp
    Created: 1 May 2018 8:47:46pm
    Author:  tnpes

  ==============================================================================
*/

#include "DistortionEditor.h"

DistortionEditor::DistortionEditor(TnpMidiSynthAudioProcessor& p, AudioProcessorValueTreeState& apvts)
{
	addAndMakeVisible(labelTitle);
	labelTitle.setText("DISTORTION", dontSendNotification);
	labelTitle.setJustificationType(Justification::centred);

	addAndMakeVisible(toggleDistortion);
	toggleAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(apvts, "distortionToggle", toggleDistortion);

	addAndMakeVisible(labelDrive);
	labelDrive.setText("drive", dontSendNotification);
	labelDrive.setJustificationType(Justification::centredTop);
	addAndMakeVisible(sliderDrive);
	sliderDrive.setSliderStyle(Slider::RotaryVerticalDrag);
	sliderDrive.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);
	driveAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "distortionDrive", sliderDrive);

	addAndMakeVisible(labelRange);
	labelRange.setText("range", dontSendNotification);
	labelRange.setJustificationType(Justification::centredTop);
	addAndMakeVisible(sliderRange);
	sliderRange.setSliderStyle(Slider::RotaryVerticalDrag);
	sliderRange.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 15);
	rangeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "distortionRange", sliderRange);

	addAndMakeVisible(labelMix);
	labelMix.setText("mix", dontSendNotification);
	labelMix.setJustificationType(Justification::centredTop);
	addAndMakeVisible(sliderMix);
	sliderMix.setSliderStyle(Slider::RotaryVerticalDrag);
	sliderMix.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);
	mixAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "distortionMix", sliderMix);
}

DistortionEditor::~DistortionEditor()
{
}

void DistortionEditor::paint(Graphics& g)
{
	g.fillAll(Colours::lightgrey);

	labelTitle.setColour(Label::backgroundColourId, Colours::cadetblue);

	//=========================================================================================
	sliderDrive.setColour(Slider::textBoxTextColourId, Colours::black);
	sliderRange.setColour(Slider::textBoxTextColourId, Colours::black);
	sliderMix.setColour(Slider::textBoxTextColourId, Colours::black);
}

void DistortionEditor::resized()
{
	const int sliderWidth = getWidth() / 3;
	juce::Rectangle<int> area(getLocalBounds());

	juce::Rectangle<int> topSection(area.removeFromTop(20).reduced(2));
	toggleDistortion.setBounds(topSection.removeFromLeft(20));
	labelTitle.setBounds(topSection.reduced(2));
	juce::Rectangle<int> controlsArea(area.reduced(5));

	juce::Rectangle<int> labelArea(controlsArea.removeFromTop(15));
	labelDrive.setBounds(labelArea.removeFromLeft(sliderWidth));
	labelRange.setBounds(labelArea.removeFromLeft(sliderWidth));
	labelMix.setBounds(labelArea.removeFromLeft(sliderWidth));

	juce::Rectangle<int> sliderArea(controlsArea.removeFromTop(getHeight()));
	sliderDrive.setBounds(sliderArea.removeFromLeft(sliderWidth));
	sliderRange.setBounds(sliderArea.removeFromLeft(sliderWidth));
	sliderMix.setBounds(sliderArea.removeFromLeft(sliderWidth));
}
