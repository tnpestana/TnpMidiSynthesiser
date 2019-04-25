/*
  ==============================================================================

    DelayEditor.cpp
    Created: 4 Aug 2018 6:29:27pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "DelayEditor.h"

DelayEditor::DelayEditor(TnpMidiSynthAudioProcessor& p)
	//  Processor references
	: processor (p),
	treeState (p.getTreeState()),
	//  Parameter attachments
	attToggle (std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
		(treeState, "delayToggle", toggleDelay)),
	attDelayTime (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "delayTime", sliderDelayTime)),
	attFeedback (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "delayFeedback", sliderDelayFeedback)),
	attMix (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "delayMix", sliderdelayMix))
{
	labelTitle.setText("DELAY", dontSendNotification);
	labelDelayTime.setText("time", dontSendNotification);
	labelDelayFeedback.setText("feedback", dontSendNotification);
	labelDelayMix.setText("mix", dontSendNotification);

	labelTitle.setJustificationType(Justification::centred);
	labelDelayTime.setJustificationType(Justification::centredTop);
	labelDelayFeedback.setJustificationType(Justification::centredTop);
	labelDelayMix.setJustificationType(Justification::centredTop);

	sliderDelayTime.setSliderStyle(Slider::RotaryVerticalDrag);
	sliderDelayFeedback.setSliderStyle(Slider::RotaryVerticalDrag);
	sliderdelayMix.setSliderStyle(Slider::RotaryVerticalDrag);

	sliderDelayTime.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
	sliderDelayFeedback.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
	sliderdelayMix.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);

	sliderDelayTime.setTextValueSuffix(" ms");
	sliderDelayFeedback.setTextValueSuffix(" %");
	sliderdelayMix.setTextValueSuffix(" %");

	addAndMakeVisible(labelTitle);
	addAndMakeVisible(toggleDelay);
	addAndMakeVisible(labelDelayTime);
	addAndMakeVisible(sliderDelayTime);
	addAndMakeVisible(labelDelayFeedback);
	addAndMakeVisible(sliderDelayFeedback);
	addAndMakeVisible(labelDelayMix);
	addAndMakeVisible(sliderdelayMix);
}

DelayEditor::~DelayEditor()
{
}

void DelayEditor::paint(Graphics& g)
{
	labelTitle.setColour(Label::outlineColourId, Colours::black);
	labelTitle.setColour(Label::backgroundColourId, Colours::lightgrey);
	sliderDelayTime.setColour(Slider::textBoxTextColourId, Colours::black);
	sliderDelayFeedback.setColour(Slider::textBoxTextColourId, Colours::black);
	sliderdelayMix.setColour(Slider::textBoxTextColourId, Colours::black);
}

void DelayEditor::resized()
{
	juce::Rectangle<int> area(getLocalBounds());

	juce::Rectangle<int> topSection(area.removeFromTop(20));
	toggleDelay.setBounds(topSection.removeFromLeft(22));
	labelTitle.setBounds(topSection.reduced(2));

	juce::Rectangle<int> controlsArea(area.reduced(5));

	int controlWidth = controlsArea.getWidth() / 16;

	juce::Rectangle<int> firstRemovedAreaLeft(controlsArea.removeFromLeft(controlWidth * 2));

	juce::Rectangle<int> delayTimeArea(controlsArea.removeFromLeft(controlWidth * 4));
	labelDelayTime.setBounds(delayTimeArea.removeFromTop(15));
	sliderDelayTime.setBounds(delayTimeArea);

	juce::Rectangle<int> secondRemovedAreaLeft(controlsArea.removeFromLeft(controlWidth));

	juce::Rectangle<int> feedbackArea(controlsArea.removeFromLeft(controlWidth * 4));
	labelDelayFeedback.setBounds(feedbackArea.removeFromTop(15));
	sliderDelayFeedback.setBounds(feedbackArea);

	juce::Rectangle<int> thirdRemovedAreaLeft(controlsArea.removeFromLeft(controlWidth));

	juce::Rectangle<int> mixArea(controlsArea.removeFromLeft(controlWidth * 4));
	labelDelayMix.setBounds(mixArea.removeFromTop(15));
	sliderdelayMix.setBounds(mixArea);
}
