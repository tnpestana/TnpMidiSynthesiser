/*
  ==============================================================================

    ReverbEditor.cpp
    Created: 17 Apr 2018 5:19:12pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "ReverbEditor.h"

ReverbEditor::ReverbEditor(TnpMidiSynthAudioProcessor& p)
	//	Processor references
	: processor(p),
	treeState(p.getTreeState()),
	//	Parameter attachments
	attToggle (std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
		(treeState, "reverbToggle", toggleReverb)),
	attRoomSize (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "reverbRoomSize", roomSizeSlider)),
	attDamping (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "reverbDamping", dampingSlider)),
	attWidth (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "reverbWidth", widthSlider)),
	attMix (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "reverbMix", mixSlider))

{
	labelTitle.setText("REVERB", dontSendNotification);
	roomSizeLabel.setText("room size", dontSendNotification);
	dampingLabel.setText("damping", dontSendNotification);
	widthLabel.setText("width", dontSendNotification);
	labelMix.setText("mix", dontSendNotification);

	labelTitle.setJustificationType(Justification::centred);
	roomSizeLabel.setJustificationType(Justification::centredBottom);
	dampingLabel.setJustificationType(Justification::centredBottom);
	widthLabel.setJustificationType(Justification::centredBottom);
	labelMix.setJustificationType(Justification::centredBottom);

	roomSizeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	dampingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	widthSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	mixSlider.setSliderStyle(Slider::RotaryVerticalDrag);

	roomSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	dampingSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	widthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	mixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);

	addAndMakeVisible(labelTitle);
	addAndMakeVisible(toggleReverb);
	addAndMakeVisible(roomSizeLabel);
	addAndMakeVisible(roomSizeSlider);
	addAndMakeVisible(dampingLabel);
	addAndMakeVisible(dampingSlider);
	addAndMakeVisible(widthLabel);
	addAndMakeVisible(widthSlider);
	addAndMakeVisible(labelMix);
	addAndMakeVisible(mixSlider);
}

ReverbEditor::~ReverbEditor()
{
}

void ReverbEditor::paint(Graphics& g)
{
	labelTitle.setColour(Label::backgroundColourId, Colours::lightgrey);
	labelTitle.setColour(Label::outlineColourId, Colours::black);
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