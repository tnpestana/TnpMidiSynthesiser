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

	sliderDelayTime.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	sliderDelayFeedback.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	sliderdelayMix.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);

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
	const int sliderWidth = getWidth() / 3;
	juce::Rectangle<int> area(getLocalBounds());

	juce::Rectangle<int> topSection(area.removeFromTop(20));
	toggleDelay.setBounds(topSection.removeFromLeft(22));
	labelTitle.setBounds(topSection.reduced(2));

	juce::Rectangle<int> controlsArea(area.reduced(5));

	juce::Rectangle<int> labelArea(controlsArea.removeFromTop(15));
	labelDelayTime.setBounds(labelArea.removeFromLeft(sliderWidth));
	labelDelayFeedback.setBounds(labelArea.removeFromLeft(sliderWidth));
	labelDelayMix.setBounds(labelArea.removeFromLeft(sliderWidth));

	juce::Rectangle<int> sliderArea(controlsArea.removeFromTop(getHeight()));
	sliderDelayTime.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5));
	sliderDelayFeedback.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5));
	sliderdelayMix.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(5));
}
