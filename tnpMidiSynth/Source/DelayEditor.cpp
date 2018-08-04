/*
  ==============================================================================

    DelayEditor.cpp
    Created: 4 Aug 2018 6:29:27pm
    Author:  tnpes

  ==============================================================================
*/

#include "DelayEditor.h"

DelayEditor::DelayEditor(TnpMidiSynthAudioProcessor& p, AudioProcessorValueTreeState& apvts)
{
	addAndMakeVisible(titleLabel);
	titleLabel.setText("DELAY", dontSendNotification);
	titleLabel.setJustificationType(Justification::centred);

	addAndMakeVisible(delayTimeLabel);
	delayTimeLabel.setText("time", dontSendNotification);
	delayTimeLabel.setJustificationType(Justification::centredBottom);
	addAndMakeVisible(delayTimeSlider);
	delayTimeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	delayTimeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	delayTimeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "delayTime", delayTimeSlider);

	addAndMakeVisible(delayFeedbackLabel);
	delayFeedbackLabel.setText("feedback", dontSendNotification);
	delayFeedbackLabel.setJustificationType(Justification::centredBottom);
	addAndMakeVisible(delayFeedbackSlider);
	delayFeedbackSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	delayFeedbackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	delayFeedbackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "delayFeedback", delayFeedbackSlider);

	addAndMakeVisible(delayMixLabel);
	delayMixLabel.setText("wet", dontSendNotification);
	delayMixLabel.setJustificationType(Justification::centredBottom);
	addAndMakeVisible(delayMixSlider);
	delayMixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	delayMixSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	delayMixAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "delayMix", delayMixSlider);
}

DelayEditor::~DelayEditor()
{
}

void DelayEditor::paint(Graphics& g)
{
	g.fillAll(Colours::lightgrey);

	titleLabel.setColour(Label::backgroundColourId, Colours::cadetblue);
}

void DelayEditor::resized()
{
	const int sliderWidth = getWidth() / 3;
	juce::Rectangle<int> area(getLocalBounds());

	titleLabel.setBounds(area.removeFromTop(20).reduced(2));

	juce::Rectangle<int> labelArea(area.removeFromTop(15));
	delayTimeLabel.setBounds(labelArea.removeFromLeft(sliderWidth));
	delayFeedbackLabel.setBounds(labelArea.removeFromLeft(sliderWidth));
	delayMixLabel.setBounds(labelArea.removeFromLeft(sliderWidth));

	juce::Rectangle<int> sliderArea(area.removeFromTop(getHeight()));
	delayTimeSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
	delayFeedbackSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
	delayMixSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
}
