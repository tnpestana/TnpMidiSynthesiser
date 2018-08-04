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

	addAndMakeVisible(dryWetSlider);
	dryWetSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dryWetSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	addAndMakeVisible(dryWetLabel);
	dryWetLabel.setText("dry/wet", dontSendNotification);
	dryWetLabel.setJustificationType(Justification::centredBottom);
	dryWetAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "dryWet", dryWetSlider);

	addAndMakeVisible(roomSizeSlider);
	roomSizeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	roomSizeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	addAndMakeVisible(roomSizeLabel);
	roomSizeLabel.setText("room size", dontSendNotification);
	roomSizeLabel.setJustificationType(Justification::centredBottom);
	roomSizeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "roomSize", roomSizeSlider);

	addAndMakeVisible(dampingSlider);
	dampingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dampingSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	addAndMakeVisible(dampingLabel);
	dampingLabel.setText("damping", dontSendNotification);
	dampingLabel.setJustificationType(Justification::centredBottom);
	dampingAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "damping", dampingSlider);
}

ReverbEditor::~ReverbEditor()
{
}

void ReverbEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::lightgrey);
	getLookAndFeel().setColour(Label::backgroundColourId, Colours::lightgrey);

	titleLabel.setColour(Label::backgroundColourId, Colours::cadetblue);

	// Color scheme for child components.
	getLookAndFeel().setColour(Slider::ColourIds::thumbColourId, Colours::cadetblue);
	getLookAndFeel().setColour(Slider::ColourIds::trackColourId, Colours::cadetblue);
	getLookAndFeel().setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::cadetblue);
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