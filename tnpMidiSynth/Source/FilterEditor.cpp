/*
  ==============================================================================

    FilterEditor.cpp
    Created: 7 Aug 2018 6:24:53pm
    Author:  tnpes

  ==============================================================================
*/

#include "FilterEditor.h"

FilterEditor::FilterEditor(TnpMidiSynthAudioProcessor& p, AudioProcessorValueTreeState& apvts)
	: processor(p)
{
	addAndMakeVisible(titleLabel);
	titleLabel.setText("FILTER", dontSendNotification);
	titleLabel.setJustificationType(Justification::centred);

	addAndMakeVisible(filterTypeInput);
	filterTypeInput.addItem("lo-pass", 1);
	filterTypeInput.addItem("hi-pass", 2);
	filterTypeInput.addItem("band-pass", 3);
	filterTypeInput.addItem("notch", 4);
	filterTypeInput.addItem("lo-shelf", 5);
	filterTypeInput.addItem("hi-shelf", 6);
	filterTypeInput.addItem("peak", 7);

	addAndMakeVisible(filterCutoffSlider);
	filterCutoffSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	filterCutoffSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	addAndMakeVisible(filterQSlider);
	filterQSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	filterQSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	addAndMakeVisible(filterGainFactorSlider);
	filterGainFactorSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	filterGainFactorSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	addAndMakeVisible(filterTypeLabel);
	filterTypeLabel.setText("type", dontSendNotification);
	filterTypeLabel.setJustificationType(Justification::centredBottom);

	addAndMakeVisible(filterCutoffLabel);
	filterCutoffLabel.setText("cutoff", dontSendNotification);
	filterCutoffLabel.setJustificationType(Justification::centredBottom);

	addAndMakeVisible(filterQLabel);
	filterQLabel.setText("Q", dontSendNotification);
	filterQLabel.setJustificationType(Justification::centredBottom);

	addAndMakeVisible(filterGainFactorLabel);
	filterGainFactorLabel.setText("gain", dontSendNotification);
	filterGainFactorLabel.setJustificationType(Justification::centredBottom);

	filterTypeAttachment = 
		std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> (apvts, "filterType", filterTypeInput);
	filterCutoffAttachment = 
		std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "filterCutoff", filterCutoffSlider);
	filterQAttachment = 
		std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "filterQ", filterQSlider);
	filterGainFactorAttachment = 
		std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (apvts, "filterGainFactor", filterGainFactorSlider);
}

FilterEditor::~FilterEditor()
{
}

void FilterEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::lightgrey);

	titleLabel.setColour(Label::backgroundColourId, Colours::cadetblue);
}

void FilterEditor::resized()
{
	const int labelWidth = getWidth() / 4;
	const int labelHeight = 15;
	const int sliderWidth = getWidth() / 4;
	const int sliderHeight = getHeight() - labelHeight;

	juce::Rectangle<int> area(getLocalBounds());

	titleLabel.setBounds(area.removeFromTop(20).reduced(2));

	juce::Rectangle<int> labels(area.removeFromTop(labelHeight));
	filterTypeLabel.setBounds(labels.removeFromLeft(labelWidth));
	filterCutoffLabel.setBounds(labels.removeFromLeft(labelWidth));
	filterQLabel.setBounds(labels.removeFromLeft(labelWidth));
	filterGainFactorLabel.setBounds(labels);

	juce::Rectangle<int> sliders(area.removeFromTop(getHeight()));
	filterTypeInput.setBounds(sliders.removeFromLeft(sliderWidth).reduced(10));
	filterCutoffSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	filterQSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	filterGainFactorSlider.setBounds(sliders);
}
