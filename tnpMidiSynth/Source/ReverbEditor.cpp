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
	addAndMakeVisible(titleLabel);
	titleLabel.setText("REVERB", dontSendNotification);
	titleLabel.setJustificationType(Justification::centred);

	addAndMakeVisible(dryWetSlider);
	dryWetSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dryWetSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	addAndMakeVisible(dryWetLabel);
	dryWetLabel.setText("dry/Wet", dontSendNotification);
	dryWetLabel.setJustificationType(Justification::centred);
	dryWetAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState,
		"dryWet", dryWetSlider);

	addAndMakeVisible(roomSizeSlider);
	roomSizeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	roomSizeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	addAndMakeVisible(roomSizeLabel);
	roomSizeLabel.setText("room size", dontSendNotification);
	roomSizeLabel.setJustificationType(Justification::centred);
	roomSizeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState,
		"roomSize", roomSizeSlider);

	addAndMakeVisible(dampingSlider);
	dampingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dampingSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

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
	g.fillAll(Colours::goldenrod);

	getLookAndFeel().setColour(Label::backgroundColourId, Colours::goldenrod);

	titleLabel.setColour(Label::backgroundColourId, Colours::darkgoldenrod);
}

void ReverbEditor::resized()
{
	const int labelWidth = getWidth() / 3;
	const int labelHeight = 15;
	const int sliderWidth = getWidth() / 3;
	const int sliderHeight = getHeight() - labelHeight;

	juce::Rectangle<int> area(getLocalBounds());

	titleLabel.setBounds(area.removeFromTop(20).reduced(2));

	juce::Rectangle<int> labels(area.removeFromTop(labelHeight));
	dryWetLabel.setBounds(labels.removeFromLeft(labelWidth));
	roomSizeLabel.setBounds(labels.removeFromLeft(labelWidth));
	dampingLabel.setBounds(labels.removeFromLeft(labelWidth));

	juce::Rectangle<int> sliders(area.removeFromTop(getHeight()));
	dryWetSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	roomSizeSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	dampingSlider.setBounds(sliders.removeFromLeft(sliderWidth));
}