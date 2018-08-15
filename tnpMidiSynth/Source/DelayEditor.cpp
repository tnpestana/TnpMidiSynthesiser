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
	delayTimeLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(delayTimeSlider);
	delayTimeSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	delayTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);
	delayTimeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "delayTime", delayTimeSlider);

	addAndMakeVisible(delayFeedbackLabel);
	delayFeedbackLabel.setText("feedback", dontSendNotification);
	delayFeedbackLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(delayFeedbackSlider);
	delayFeedbackSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	delayFeedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);
	delayFeedbackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "delayFeedback", delayFeedbackSlider);

	addAndMakeVisible(delayMixLabel);
	delayMixLabel.setText("mix", dontSendNotification);
	delayMixLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(delayMixSlider);
	delayMixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	delayMixSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 15);
	delayMixAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "delayMix", delayMixSlider);
}

DelayEditor::~DelayEditor()
{
}

void DelayEditor::paint(Graphics& g)
{
	g.fillAll(Colours::lightgrey);

	titleLabel.setColour(Label::backgroundColourId, Colours::cadetblue);

	//=========================================================================================
	delayTimeSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	delayFeedbackSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	delayMixSlider.setColour(Slider::textBoxTextColourId, Colours::black);
}

void DelayEditor::resized()
{
	const int sliderWidth = getWidth() / 3;
	juce::Rectangle<int> area(getLocalBounds());

	titleLabel.setBounds(area.removeFromTop(20).reduced(2));

	juce::Rectangle<int> controlsArea(area.reduced(5));

	juce::Rectangle<int> labelArea(controlsArea.removeFromTop(15));
	delayTimeLabel.setBounds(labelArea.removeFromLeft(sliderWidth));
	delayFeedbackLabel.setBounds(labelArea.removeFromLeft(sliderWidth));
	delayMixLabel.setBounds(labelArea.removeFromLeft(sliderWidth));

	juce::Rectangle<int> sliderArea(controlsArea.removeFromTop(getHeight()));
	delayTimeSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
	delayFeedbackSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
	delayMixSlider.setBounds(sliderArea.removeFromLeft(sliderWidth));
}
