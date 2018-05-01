/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#pragma once

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TnpMidiSynthAudioProcessorEditor::TnpMidiSynthAudioProcessorEditor (TnpMidiSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscillatorGUI(p), reverbGUI(p)
{
    // Main editor's size.
    setSize (250, 280);

	addAndMakeVisible(numVoicesLabel);
	numVoicesLabel.setText("number of voices:", dontSendNotification);
	numVoicesLabel.setJustificationType(Justification::centredRight);
	addAndMakeVisible(numVoicesInput);
	for(int i = 1; i < 11; i++)							//	Even though the numVoices parameter's range is defined we
		numVoicesInput.addItem((String)i, i);			// seem to need to populate the combo box anyway.
	numVoicesAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.treeState, "numVoices", numVoicesInput);

	addAndMakeVisible(oscillatorGUI);
	addAndMakeVisible(reverbGUI);
}
TnpMidiSynthAudioProcessorEditor::~TnpMidiSynthAudioProcessorEditor()
{
}

//=============================================================================
void TnpMidiSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::mediumseagreen);

	// Color scheme for child components.
	getLookAndFeel().setColour(Slider::ColourIds::trackColourId, Colours::lightpink);
	getLookAndFeel().setColour(Slider::ColourIds::backgroundColourId, Colours::lightyellow);
	getLookAndFeel().setColour(Slider::ColourIds::thumbColourId, Colours::coral);
	getLookAndFeel().setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::lightpink);
	getLookAndFeel().setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::lightyellow);
	getLookAndFeel().setColour(ComboBox::textColourId, Colours::black);
	getLookAndFeel().setColour(ComboBox::backgroundColourId, Colours::mediumseagreen);
	getLookAndFeel().setColour(PopupMenu::textColourId, Colours::black);
	getLookAndFeel().setColour(PopupMenu::ColourIds::backgroundColourId, Colours::rosybrown);
	getLookAndFeel().setColour(Label::textColourId, Colours::black);
	getLookAndFeel().setColour(Label::backgroundColourId, Colours::mediumseagreen);
}

void TnpMidiSynthAudioProcessorEditor::resized()
{
	// Total main editor's area.
	juce::Rectangle<int> area (getLocalBounds());

	// Number of voices selection area.
	juce::Rectangle<int> numVoicesArea (area.removeFromTop(20));
	numVoicesLabel.setBounds(numVoicesArea.removeFromLeft(getWidth() / 2));
	numVoicesInput.setBounds(numVoicesArea.removeFromLeft(getWidth() / 2));

	// Oscillator area.
	oscillatorGUI.setBounds(area.removeFromTop(180));

	// Reverb area.
	reverbGUI.setBounds(area.removeFromTop(80));
}