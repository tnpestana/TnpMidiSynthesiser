/*
  ==============================================================================

    ReverbEditor.cpp
    Created: 17 Apr 2018 5:19:12pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "ReverbEditor.h"

ReverbEditor::ReverbEditor(TnpMidiSynthAudioProcessor& p, AudioProcessorValueTreeState& apvts)
	: processor(p)
{
	addAndMakeVisible(labelTitle);
	labelTitle.setText("REVERB", dontSendNotification);
	labelTitle.setJustificationType(Justification::centred);

	addAndMakeVisible(toggleReverb);
	toggleAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(apvts, "reverbToggle", toggleReverb);

	addAndMakeVisible(roomSizeSlider);
	roomSizeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	roomSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);

	addAndMakeVisible(roomSizeLabel);
	roomSizeLabel.setText("room size", dontSendNotification);
	roomSizeLabel.setJustificationType(Justification::centredBottom);
	roomSizeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "reverbRoomSize", roomSizeSlider);

	addAndMakeVisible(dampingSlider);
	dampingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dampingSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);

	addAndMakeVisible(dampingLabel);
	dampingLabel.setText("damping", dontSendNotification);
	dampingLabel.setJustificationType(Justification::centredBottom);
	dampingAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "reverbDamping", dampingSlider);

	addAndMakeVisible(widthSlider);
	widthSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	widthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);

	addAndMakeVisible(widthLabel);
	widthLabel.setText("width", dontSendNotification);
	widthLabel.setJustificationType(Justification::centredBottom);
	mixAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "reverbWidth", widthSlider);

	addAndMakeVisible(mixSlider);
	mixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	mixSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);

	addAndMakeVisible(labelMix);
	labelMix.setText("mix", dontSendNotification);
	labelMix.setJustificationType(Justification::centredBottom);
	mixAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "reverbMix", mixSlider);
}

ReverbEditor::~ReverbEditor()
{
}

void ReverbEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	//g.fillAll(Colours::lightgrey);

	labelTitle.setColour(Label::backgroundColourId, Colours::cadetblue);

	//=========================================================================================
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