/*
  ==============================================================================

    ReverbEditor.cpp
    Created: 17 Apr 2018 5:19:12pm
    Author:  tnpes

  ==============================================================================
*/

#include "ReverbEditor.h"

ReverbEditor::ReverbEditor(TnpMidiSynthAudioProcessor& p, AudioProcessorValueTreeState& apvts)
	: processor(p)
{
	addAndMakeVisible(titleLabel);
	titleLabel.setText("REVERB", dontSendNotification);
	titleLabel.setJustificationType(Justification::centred);

	addAndMakeVisible(roomSizeSlider);
	roomSizeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	roomSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);

	addAndMakeVisible(roomSizeLabel);
	roomSizeLabel.setText("room size", dontSendNotification);
	roomSizeLabel.setJustificationType(Justification::centredTop);
	roomSizeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "reverbRoomSize", roomSizeSlider);

	addAndMakeVisible(dampingSlider);
	dampingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dampingSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);

	addAndMakeVisible(dampingLabel);
	dampingLabel.setText("damping", dontSendNotification);
	dampingLabel.setJustificationType(Justification::centredTop);
	dampingAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "reverbDamping", dampingSlider);

	addAndMakeVisible(mixSlider);
	mixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	mixSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);

	addAndMakeVisible(mixLabel);
	mixLabel.setText("mix", dontSendNotification);
	mixLabel.setJustificationType(Justification::centredTop);
	mixAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "reverbMix", mixSlider);
}

ReverbEditor::~ReverbEditor()
{
}

void ReverbEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::lightgrey);

	titleLabel.setColour(Label::backgroundColourId, Colours::cadetblue);

	//=========================================================================================
	roomSizeSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	dampingSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	mixSlider.setColour(Slider::textBoxTextColourId, Colours::black);
}

void ReverbEditor::resized()
{
	const int labelWidth = getWidth() / 3;
	const int labelHeight = 15;
	const int sliderWidth = getWidth() / 3;
	const int sliderHeight = getHeight() - labelHeight;

	juce::Rectangle<int> area(getLocalBounds());

	titleLabel.setBounds(area.removeFromTop(20).reduced(2));

	juce::Rectangle<int> controlsArea(area.reduced(5));

	juce::Rectangle<int> labels(controlsArea.removeFromTop(labelHeight));
	roomSizeLabel.setBounds(labels.removeFromLeft(labelWidth));
	dampingLabel.setBounds(labels.removeFromLeft(labelWidth));
	mixLabel.setBounds(labels.removeFromLeft(labelWidth));

	juce::Rectangle<int> sliders(controlsArea.removeFromTop(getHeight()));
	roomSizeSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	dampingSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	mixSlider.setBounds(sliders.removeFromLeft(sliderWidth));
}