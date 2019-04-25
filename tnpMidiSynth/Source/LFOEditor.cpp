/*
  ==============================================================================

    LFOEditor.cpp
    Created: 30 Aug 2018 6:26:46pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "LFOEditor.h"

LFOEditor::LFOEditor(TnpMidiSynthAudioProcessor& p)
	//  Processor references
	: processor (p),
	treeState(p.getTreeState()),
	//  Parameter attachments
	attOscType (std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
		(treeState, "lfoOscType", comboOscType)),
	attDepth (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "lfoDepth", sliderLfoDepth)),
	attRate (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "lfoRate", sliderLfoRate)),
	attToggle (std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
		(treeState, "lfoToggle", toggleLfo))
{
	labelTitle.setText("LFO", dontSendNotification);
	labelLfoOscType.setText("wave: ", dontSendNotification);
	labelLfoDepth.setText("depth: ", dontSendNotification);
	labelLfoRate.setText("rate: ", dontSendNotification);

	labelLfoOscType.setJustificationType(Justification::centredRight);
	labelLfoDepth.setJustificationType(Justification::centredRight);
	labelLfoRate.setJustificationType(Justification::centredRight);
	labelTitle.setJustificationType(Justification::centred);

	sliderLfoDepth.setTextBoxStyle(Slider::TextBoxLeft, false, 50, 15);
	sliderLfoRate.setTextBoxStyle(Slider::TextBoxLeft, false, 50, 15);

	sliderLfoDepth.setTextValueSuffix(" %");
	sliderLfoRate.setTextValueSuffix(" Hz");

	//  Populate combo boxes with strings stored as paramneter choices
	if (auto* choiceParameter = dynamic_cast<AudioParameterChoice*>(treeState.getParameter("lfoOscType")))
	{
		comboOscType.addItemList(choiceParameter->choices, 1);
		comboOscType.setSelectedId(choiceParameter->getIndex() + 1);
	}

	addAndMakeVisible(labelTitle);
	addAndMakeVisible(toggleLfo);
	addAndMakeVisible(comboOscType);
	addAndMakeVisible(sliderLfoDepth);
	addAndMakeVisible(sliderLfoRate);
	addAndMakeVisible(labelLfoOscType);
	addAndMakeVisible(labelLfoDepth);
	addAndMakeVisible(labelLfoRate);
}

LFOEditor::~LFOEditor()
{
}

void LFOEditor::paint(Graphics &)
{
	labelTitle.setColour(Label::backgroundColourId, Colours::lightgrey);
	labelTitle.setColour(Label::outlineColourId, Colours::black);
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
