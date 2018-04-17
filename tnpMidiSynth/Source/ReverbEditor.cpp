/*
  ==============================================================================

    ReverbEditor.cpp
    Created: 17 Apr 2018 5:19:12pm
    Author:  tnpes

  ==============================================================================
*/

#include "ReverbEditor.h"

ReverbEditor::ReverbEditor(TnpMidiSynthAudioProcessor& p)
	: processor(p)
{
	addAndMakeVisible(dryWetSlider);
	dryWetSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dryWetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	dryWetSlider.setRange(0, 1, 0.01);

	addAndMakeVisible(dryWetLabel);
	dryWetLabel.setText("dry/Wet", dontSendNotification);
	dryWetLabel.setJustificationType(Justification::centred);
	dryWetAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState,
		"dryWet", dryWetSlider);

	addAndMakeVisible(roomSizeSlider);
	roomSizeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	roomSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	roomSizeSlider.setRange(0, 1, 0.01);

	addAndMakeVisible(roomSizeLabel);
	roomSizeLabel.setText("room size", dontSendNotification);
	roomSizeLabel.setJustificationType(Justification::centred);
	roomSizeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState,
		"roomSize", roomSizeSlider);

	addAndMakeVisible(dampingSlider);
	dampingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dampingSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
	dampingSlider.setRange(0, 1, 0.01);

	addAndMakeVisible(dampingLabel);
	dampingLabel.setText("damping", dontSendNotification);
	dampingLabel.setJustificationType(Justification::centred);
	dampingAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState,
		"damping", dampingSlider);
}

ReverbEditor::~ReverbEditor()
{
}

void ReverbEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::black);
}

void ReverbEditor::resized()
{
	const int labelWidth = getWidth() / 3;
	const int labelHeight = 20;
	const int sliderWidth = getWidth() / 3;
	const int sliderHeight = getHeight() - labelHeight;

	juce::Rectangle<int> area(getLocalBounds());

	dryWetSlider.setBounds(0, 0, sliderWidth, sliderHeight);
	dryWetLabel.setBounds(0, sliderHeight, labelWidth, labelHeight);

	roomSizeLabel.setBounds(sliderWidth, sliderHeight, labelWidth, labelHeight);
	roomSizeSlider.setBounds(sliderWidth, 0, sliderWidth, sliderHeight);

	dampingLabel.setBounds(sliderWidth * 2, sliderHeight, labelWidth, labelHeight);
	dampingSlider.setBounds(sliderWidth * 2, 0, sliderWidth, sliderHeight);
}