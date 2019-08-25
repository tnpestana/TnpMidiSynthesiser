/*
  ==============================================================================

    FilterEditor.cpp
    Created: 7 Aug 2018 6:24:53pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "FilterEditor.h"

FilterEditor::FilterEditor(TnpMidiSynthAudioProcessor& p)
	//  Processor references
	: processor (p),
	treeState (p.getTreeState()),
	//  Parameter attachments
	attToggle (std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
		(treeState, "filterToggle", toggleFilter)),
	attFilterType (std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
		(treeState, "filterType", comboFilterType)),
	attCutoff (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "filterCutoff", sliderFilterCutoff)),
	attQ (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "filterQ", sliderFilterQ)),
	attGainFactor (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "filterGainFactor", sliderFilterGainFactor))
{
	labelFilterTitle.setText	  ("FILTER", dontSendNotification);
	labelFilterType.setText		  ("type: ", dontSendNotification);
	labelFilterCutoff.setText	  ("cutoff", dontSendNotification);
	labelFilterQ.setText		  ("Q", dontSendNotification);
	labelFilterGainFactor.setText ("gain factor", dontSendNotification);

	labelFilterTitle.setJustificationType	   (Justification::centred);
	labelFilterType.setJustificationType       (Justification::centredRight);
	labelFilterCutoff.setJustificationType     (Justification::centredBottom);
	labelFilterQ.setJustificationType		   (Justification::centredBottom);
	labelFilterGainFactor.setJustificationType (Justification::centredBottom);

	sliderFilterCutoff.setSliderStyle	  (Slider::RotaryVerticalDrag);
	sliderFilterQ.setSliderStyle		  (Slider::RotaryVerticalDrag);
	sliderFilterGainFactor.setSliderStyle (Slider::RotaryVerticalDrag);

	sliderFilterQ.setTextBoxStyle		   (Slider::TextBoxBelow, false, 50, 15);
	sliderFilterCutoff.setTextBoxStyle	   (Slider::TextBoxBelow, false, 80, 15);
	sliderFilterGainFactor.setTextBoxStyle (Slider::TextBoxBelow, false, 50, 15);

	sliderFilterQ.setTextValueSuffix(" oct");
	sliderFilterCutoff.setTextValueSuffix(" Hz");
	sliderFilterGainFactor.setTextValueSuffix(" %");

	//  Populate combo boxes with strings stored as paramneter choices
	if (auto* choiceParameter = dynamic_cast<AudioParameterChoice*>(treeState.getParameter("filterType")))
	{
		comboFilterType.addItemList(choiceParameter->choices, 1);
		comboFilterType.setSelectedId(choiceParameter->getIndex() + 1);
	}

	addAndMakeVisible (toggleFilter);
	addAndMakeVisible (labelFilterTitle);
	addAndMakeVisible (labelFilterType);
	addAndMakeVisible (labelFilterCutoff);
        addAndMakeVisible (labelFilterQ);
	addAndMakeVisible (labelFilterGainFactor);
	addAndMakeVisible (comboFilterType);
	addAndMakeVisible (sliderFilterCutoff);
	addAndMakeVisible (sliderFilterQ);
	addAndMakeVisible (sliderFilterGainFactor);
}

FilterEditor::~FilterEditor()
{
}

void FilterEditor::paint(Graphics& g)
{
	labelFilterTitle.setColour(Label::backgroundColourId, Colours::lightgrey);
	labelFilterTitle.setColour(Label::outlineColourId, Colours::black);
	sliderFilterCutoff.setColour(Slider::textBoxTextColourId, Colours::black);
	sliderFilterGainFactor.setColour(Slider::textBoxTextColourId, Colours::black);
	sliderFilterQ.setColour(Slider::textBoxTextColourId, Colours::black);
	comboFilterType.setColour(ComboBox::textColourId, Colours::black);
}

void FilterEditor::resized()
{
	const int labelWidth = getWidth() / 4;
	const int labelHeight = 15;

	juce::Rectangle<int> area (getLocalBounds());
	juce::Rectangle<int> titleSection	(area.removeFromTop(20));
	toggleFilter.setBounds (titleSection.removeFromLeft(22));
	labelFilterTitle.setBounds (titleSection.reduced(2));

    juce::Rectangle<int> topSection (area.removeFromTop(area.getHeight() / 4).reduced(5));
	juce::Rectangle<int> slidersSection (area.reduced(5));

	labelFilterType.setBounds (topSection.removeFromLeft(topSection.getWidth() / 5));
	comboFilterType.setBounds (topSection);
	
	juce::Rectangle<int> filterGainFactorSection (slidersSection.removeFromLeft(slidersSection.getWidth() / 4));
	labelFilterGainFactor.setBounds (filterGainFactorSection.removeFromTop(labelHeight));
	sliderFilterGainFactor.setBounds (filterGainFactorSection);
	
	juce::Rectangle<int> filterCutoffSection (slidersSection.removeFromLeft(slidersSection.getWidth() / 3));
	labelFilterCutoff.setBounds (filterCutoffSection.removeFromTop(labelHeight));
	sliderFilterCutoff.setBounds (filterCutoffSection);

	juce::Rectangle<int> filterQSection (slidersSection.removeFromLeft(slidersSection.getWidth() / 2));
	labelFilterQ.setBounds (filterQSection.removeFromTop(labelHeight));
	sliderFilterQ.setBounds	(filterQSection);
}
