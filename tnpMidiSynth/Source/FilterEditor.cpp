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

	addAndMakeVisible(filterCutoffSlider);
	filterCutoffSlider.setSliderStyle(Slider::LinearHorizontal);
	filterCutoffSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	addAndMakeVisible(filterTypeLabel);
	filterTypeLabel.setText("filter type:", dontSendNotification);
	filterTypeLabel.setJustificationType(Justification::bottomLeft);

	addAndMakeVisible(filterCutoffLabel);
	filterCutoffLabel.setText("filter cutoff:", dontSendNotification);
	filterCutoffLabel.setJustificationType(Justification::bottomLeft);
	filterCutoffAttachment = std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>
		(new AudioProcessorValueTreeState::SliderAttachment(apvts, "filterCutoff", filterCutoffSlider));
	filterTypeAttachment = std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment>
		(new AudioProcessorValueTreeState::ComboBoxAttachment(apvts, "filterType", filterTypeInput));
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
	const int labelWidth = getWidth() / 3;
	const int labelHeight = 15;
	const int sliderWidth = getWidth() / 3;
	const int sliderHeight = getHeight() - labelHeight;

	juce::Rectangle<int> area(getLocalBounds());

	titleLabel.setBounds(area.removeFromTop(20).reduced(2));

	juce::Rectangle<int> labels(area.removeFromTop(labelHeight));
	filterTypeLabel.setBounds(labels.removeFromLeft(labelWidth));
	filterCutoffLabel.setBounds(labels.removeFromLeft(labelWidth));
	//filterQLabel.setBounds(labels.removeFromLeft(labelWidth));

	juce::Rectangle<int> sliders(area.removeFromTop(getHeight()));
	filterTypeInput.setBounds(sliders.removeFromLeft(sliderWidth));
	filterCutoffSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	//filterQSlider.setBounds(sliders.removeFromLeft(sliderWidth));
}