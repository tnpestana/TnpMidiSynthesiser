/*
  ==============================================================================

    FilterEditor.cpp
    Created: 7 Aug 2018 6:24:53pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "FilterEditor.h"

FilterEditor::FilterEditor(TnpMidiSynthAudioProcessor& p)
	//	Processor references
	: processor (p),
	treeState (p.getTreeState()),
	//	Parameter attachments
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
	labelFilterType.setText		  ("type:", dontSendNotification);
	labelFilterCutoff.setText	  ("cutoff", dontSendNotification);
	labelFilterQ.setText		  ("Q", dontSendNotification);
	labelFilterGainFactor.setText ("gain factor:", dontSendNotification);

	labelFilterTitle.setJustificationType	   (Justification::centred);
	labelFilterType.setJustificationType       (Justification::bottomLeft);
	labelFilterCutoff.setJustificationType     (Justification::centredTop);
	labelFilterQ.setJustificationType		   (Justification::centredTop);
	labelFilterGainFactor.setJustificationType (Justification::bottomLeft);

	sliderFilterCutoff.setSliderStyle	  (Slider::RotaryVerticalDrag);
	sliderFilterQ.setSliderStyle		  (Slider::RotaryVerticalDrag);
	sliderFilterGainFactor.setSliderStyle (Slider::LinearHorizontal);

	sliderFilterCutoff.setSkewFactorFromMidPoint(1000.0f);
	sliderFilterGainFactor.setSkewFactorFromMidPoint(1.0f);

	sliderFilterQ.setTextBoxStyle		   (Slider::TextBoxBelow, false, 40, 15);
	sliderFilterCutoff.setTextBoxStyle	   (Slider::TextBoxBelow, false, 50, 15);
	sliderFilterGainFactor.setTextBoxStyle (Slider::TextBoxLeft, false, 30, 15);

	comboFilterType.addItem("lo-pass", 1);
	comboFilterType.addItem("hi-pass", 2);
	comboFilterType.addItem("band-pass", 3);
	comboFilterType.addItem("notch", 4);
	comboFilterType.addItem("lo-shelf", 5);
	comboFilterType.addItem("hi-shelf", 6);
	comboFilterType.addItem("peak", 7);

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
	juce::Rectangle<int> topSection	(area.removeFromTop(20));
	toggleFilter.setBounds (topSection.removeFromLeft(22));
	labelFilterTitle.setBounds (topSection.reduced(2));

	juce::Rectangle<int> totalSection (area.reduced(5));
	juce::Rectangle<int> leftSection (totalSection.removeFromLeft(labelWidth * 2).reduced(5));

	juce::Rectangle<int> filterTypeSection (leftSection.removeFromTop(leftSection.getHeight() * 0.5).reduced(5));
	labelFilterType.setBounds (filterTypeSection.removeFromTop(labelHeight));
	comboFilterType.setBounds (filterTypeSection);
	
	juce::Rectangle<int> filterGainFactorSection (leftSection.reduced(5));
	labelFilterGainFactor.setBounds (filterGainFactorSection.removeFromTop(labelHeight));
	sliderFilterGainFactor.setBounds (filterGainFactorSection);
	
	juce::Rectangle<int> filterCutoffSection (totalSection.removeFromLeft(totalSection.getWidth() * 0.5).reduced(5));
	labelFilterCutoff.setBounds (filterCutoffSection.removeFromTop(labelHeight));
	sliderFilterCutoff.setBounds (filterCutoffSection);

	juce::Rectangle<int> filterQSection (totalSection.reduced(5));
	labelFilterQ.setBounds (filterQSection.removeFromTop(labelHeight));
	sliderFilterQ.setBounds	(filterQSection);
}
