/*
  ==============================================================================

    ReverbEditor.cpp
    Created: 17 Apr 2018 5:19:12pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "ReverbEditor.h"

ReverbEditor::ReverbEditor(TnpMidiSynthAudioProcessor& p)
	: processor(p),
	treeState(p.getTreeState())
{
	addAndMakeVisible(labelTitle);
	labelTitle.setText("REVERB", dontSendNotification);
	labelTitle.setJustificationType(Justification::centred);

	addAndMakeVisible(toggleReverb);
	toggleAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(treeState, "reverbToggle", toggleReverb);

	addAndMakeVisible(roomSizeSlider);
	roomSizeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	roomSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	roomSizeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "reverbRoomSize", roomSizeSlider);

	addAndMakeVisible(roomSizeLabel);
	roomSizeLabel.setText("room size", dontSendNotification);
	roomSizeLabel.setJustificationType(Justification::centredBottom);

	addAndMakeVisible(dampingSlider);
	dampingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dampingSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	dampingAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "reverbDamping", dampingSlider);

	addAndMakeVisible(dampingLabel);
	dampingLabel.setText("damping", dontSendNotification);
	dampingLabel.setJustificationType(Justification::centredBottom);

	addAndMakeVisible(widthSlider);
	widthSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	widthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);

	addAndMakeVisible(widthLabel);
	widthLabel.setText("width", dontSendNotification);
	widthLabel.setJustificationType(Justification::centredBottom);
	widthAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "reverbWidth", widthSlider);

	addAndMakeVisible(mixSlider);
	mixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	mixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);

	addAndMakeVisible(labelMix);
	labelMix.setText("mix", dontSendNotification);
	labelMix.setJustificationType(Justification::centredBottom);
	mixAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "reverbMix", mixSlider);
}

ReverbEditor::~ReverbEditor()
{
}

void ReverbEditor::paint(Graphics& g)
{
	labelTitle.setColour(Label::backgroundColourId, Colours::lightgrey);
	roomSizeSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	dampingSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	mixSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	widthSlider.setColour(Slider::textBoxTextColourId, Colours::black);
}

void ReverbEditor::resized()
{
	const int labelWidth = getWidth() * 0.25;
	const int labelHeight = 15;
	const int sliderWidth = getWidth() * 0.25;
	const int sliderHeight = getHeight() - labelHeight;

	juce::Rectangle<int> area(getLocalBounds());

	juce::Rectangle<int> topSection(area.removeFromTop(20));
	toggleReverb.setBounds(topSection.removeFromLeft(22));
	labelTitle.setBounds(topSection.reduced(2));

	juce::Rectangle<int> controlsArea(area.reduced(5));

	juce::Rectangle<int> labels(controlsArea.removeFromTop(labelHeight));
	roomSizeLabel.setBounds(labels.removeFromLeft(labelWidth));
	dampingLabel.setBounds(labels.removeFromLeft(labelWidth));
	widthLabel.setBounds(labels.removeFromLeft(labelWidth));
	labelMix.setBounds(labels.removeFromLeft(labelWidth));

	juce::Rectangle<int> sliders(controlsArea.removeFromTop(getHeight()));
	roomSizeSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	dampingSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	widthSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	mixSlider.setBounds(sliders.removeFromLeft(sliderWidth));
}