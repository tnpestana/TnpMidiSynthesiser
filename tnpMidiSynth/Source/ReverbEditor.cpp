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
	dryWetSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	dryWetSlider.setRange(0, 1, 0.01);

	addAndMakeVisible(dryWetLabel);
	dryWetLabel.setText("dry/Wet", dontSendNotification);
	dryWetLabel.setJustificationType(Justification::centred);
	dryWetAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState,
		"dryWet", dryWetSlider);

	addAndMakeVisible(roomSizeSlider);
	roomSizeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	roomSizeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	roomSizeSlider.setRange(0, 1, 0.01);

	addAndMakeVisible(roomSizeLabel);
	roomSizeLabel.setText("room size", dontSendNotification);
	roomSizeLabel.setJustificationType(Justification::centred);
	roomSizeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState,
		"roomSize", roomSizeSlider);

	addAndMakeVisible(dampingSlider);
	dampingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dampingSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
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
	g.fillAll(Colours::mediumseagreen);

	getLookAndFeel().setColour(Label::backgroundColourId, Colours::mediumseagreen);
}

void ReverbEditor::resized()
{
	const int labelWidth = getWidth() / 3;
	const int labelHeight = 20;
	const int sliderWidth = getWidth() / 3;
	const int sliderHeight = getHeight() - labelHeight;

	juce::Rectangle<int> area(getLocalBounds());

	juce::Rectangle<int> labels(area.removeFromTop(labelHeight));
	dryWetLabel.setBounds(labels.removeFromLeft(labelWidth));
	roomSizeLabel.setBounds(labels.removeFromLeft(labelWidth));
	dampingLabel.setBounds(labels.removeFromLeft(labelWidth));

	juce::Rectangle<int> sliders(area.removeFromTop(getHeight()));
	dryWetSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	roomSizeSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	dampingSlider.setBounds(sliders.removeFromLeft(sliderWidth));
}