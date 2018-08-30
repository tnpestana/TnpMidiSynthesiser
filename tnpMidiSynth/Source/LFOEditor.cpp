/*
  ==============================================================================

    LFOEditor.cpp
    Created: 30 Aug 2018 6:26:46pm
    Author:  tnpes

  ==============================================================================
*/

#include "LFOEditor.h"

LFOEditor::LFOEditor(TnpMidiSynthAudioProcessor&p , AudioProcessorValueTreeState& apvts)
{
	addAndMakeVisible(toggleLfo);
	addAndMakeVisible(labelTitle);

	addAndMakeVisible(sliderLfoDepth);
	addAndMakeVisible(sliderLfoRate);
	addAndMakeVisible(labelLfoDepth);
	addAndMakeVisible(labelLfoRate);

	sliderLfoDepth.setTextBoxStyle(Slider::TextBoxLeft, true, 40, 15);
	sliderLfoRate.setTextBoxStyle(Slider::TextBoxLeft, true, 40, 15);


	labelLfoDepth.setText("depth: ", dontSendNotification);
	labelLfoDepth.setJustificationType(Justification::centredRight);
	labelLfoRate.setText("rate :", dontSendNotification);
	labelLfoRate.setJustificationType(Justification::centredRight);

	labelTitle.setText("LFO", dontSendNotification);
	labelTitle.setJustificationType(Justification::centred);

	depthAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "lfoDepth", sliderLfoDepth);
	rateAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "lfoRate", sliderLfoRate);
	toggleAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(apvts, "lfoToggle", toggleLfo);
}

LFOEditor::~LFOEditor()
{
}

void LFOEditor::paint(Graphics &)
{
	labelTitle.setColour(Label::backgroundColourId, Colours::cadetblue);

	sliderLfoDepth.setColour(Slider::textBoxTextColourId, Colours::black);
	sliderLfoRate.setColour(Slider::textBoxTextColourId, Colours::black);
}

void LFOEditor::resized()
{
	juce::Rectangle<int> area(getLocalBounds());

	juce::Rectangle<int> topSection(area.removeFromTop(20));
	toggleLfo.setBounds(topSection.removeFromLeft(22));
	labelTitle.setBounds(topSection.reduced(2));

	juce::Rectangle<int> labels(area.removeFromLeft(50));
	labelLfoDepth.setBounds(labels.removeFromTop(labels.getHeight() / 2));
	labelLfoRate.setBounds(labels);

	sliderLfoDepth.setBounds(area.removeFromTop(area.getHeight() / 2));
	sliderLfoRate.setBounds(area);
}
