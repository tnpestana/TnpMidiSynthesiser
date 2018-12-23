/*
  ==============================================================================

    DelayEditor.cpp
    Created: 4 Aug 2018 6:29:27pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "DelayEditor.h"

DelayEditor::DelayEditor(TnpMidiSynthAudioProcessor& p, AudioProcessorValueTreeState& apvts)
{
	addAndMakeVisible(labelTitle);
	labelTitle.setText("DELAY", dontSendNotification);
	labelTitle.setJustificationType(Justification::centred);

	addAndMakeVisible(toggleDelay);
	delayToggleAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(apvts, "delayToggle", toggleDelay);

	addAndMakeVisible(labelDelayTime);
	labelDelayTime.setText("time", dontSendNotification);
	labelDelayTime.setJustificationType(Justification::centredTop);
	addAndMakeVisible(sliderDelayTime);
	sliderDelayTime.setSliderStyle(Slider::RotaryVerticalDrag);
	sliderDelayTime.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	delayTimeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "delayTime", sliderDelayTime);

	addAndMakeVisible(labelDelayFeedback);
	labelDelayFeedback.setText("feedback", dontSendNotification);
	labelDelayFeedback.setJustificationType(Justification::centredTop);
	addAndMakeVisible(sliderDelayFeedback);
	sliderDelayFeedback.setSliderStyle(Slider::RotaryVerticalDrag);
	sliderDelayFeedback.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	delayFeedbackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "delayFeedback", sliderDelayFeedback);

	addAndMakeVisible(labelDelayMix);
	labelDelayMix.setText("mix", dontSendNotification);
	labelDelayMix.setJustificationType(Justification::centredTop);
	addAndMakeVisible(sliderdelayMix);
	sliderdelayMix.setSliderStyle(Slider::RotaryVerticalDrag);
	sliderdelayMix.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	delayMixAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "delayMix", sliderdelayMix);
}

DelayEditor::~DelayEditor()
{
}

void DelayEditor::paint(Graphics& g)
{
	//g.fillAll(Colours::lightgrey);

	labelTitle.setColour(Label::backgroundColourId, Colours::lightgrey);

	//=========================================================================================
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
	sliderDelayTime.setBounds(sliderArea.removeFromLeft(sliderWidth));
	sliderDelayFeedback.setBounds(sliderArea.removeFromLeft(sliderWidth));
	sliderdelayMix.setBounds(sliderArea.removeFromLeft(sliderWidth));
}
