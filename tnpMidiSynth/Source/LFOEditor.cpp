/*
  ==============================================================================

    LFOEditor.cpp
    Created: 30 Aug 2018 6:26:46pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "LFOEditor.h"

LFOEditor::LFOEditor(TnpMidiSynthAudioProcessor& p , AudioProcessorValueTreeState& apvts)
{
	addAndMakeVisible(toggleLfo);
	addAndMakeVisible(labelTitle);

	addAndMakeVisible(comboOscType);
	comboOscType.addItem("sine", 1);					//	Even though the oscType parameter's range is defined we
	comboOscType.addItem("square", 2);					// seem to need to populate the combo box anyway.
	comboOscType.addItem("triangle", 3);
	comboOscType.addItem("sawtooth", 4);

	addAndMakeVisible(sliderLfoDepth);
	addAndMakeVisible(sliderLfoRate);
	addAndMakeVisible(labelLfoOscType);
	addAndMakeVisible(labelLfoDepth);
	addAndMakeVisible(labelLfoRate);

	sliderLfoDepth.setTextBoxStyle(Slider::TextBoxLeft, true, 40, 15);
	sliderLfoRate.setTextBoxStyle(Slider::TextBoxLeft, true, 40, 15);

	labelLfoOscType.setText("wave: ", dontSendNotification);
	labelLfoOscType.setJustificationType(Justification::centredRight);
	labelLfoDepth.setText("depth: ", dontSendNotification);
	labelLfoDepth.setJustificationType(Justification::centredRight);
	labelLfoRate.setText("rate: ", dontSendNotification);
	labelLfoRate.setJustificationType(Justification::centredRight);

	labelTitle.setText("LFO", dontSendNotification);
	labelTitle.setJustificationType(Justification::centred);

	oscTypeAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "lfoOscType", comboOscType);
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
	comboOscType.setColour(ComboBox::textColourId, Colours::black);
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
	labelLfoOscType.setBounds(labels.removeFromTop(labels.getHeight() / 3));
	labelLfoDepth.setBounds(labels.removeFromTop(labels.getHeight() / 2));
	labelLfoRate.setBounds(labels);

	comboOscType.setBounds(area.removeFromTop(area.getHeight() / 3).reduced(5));
	sliderLfoDepth.setBounds(area.removeFromTop(area.getHeight() / 2));
	sliderLfoRate.setBounds(area);
}
