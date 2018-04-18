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
    : AudioProcessorEditor (&p), processor (p), oscillator(p), reverb(p)
{
    // Main editor's size.
    setSize (250, 300);

	addAndMakeVisible(numVoicesLabel);
	numVoicesLabel.setText("number of voices:", dontSendNotification);
	numVoicesLabel.setJustificationType(Justification::centredRight);
	addAndMakeVisible(numVoicesInput);
	for(int i = 1; i < 11; i++)
		numVoicesInput.addItem((String)i, i);
	numVoicesInput.addListener(this);
	numVoicesAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.treeState, "numVoices", numVoicesInput);

	addAndMakeVisible(oscillator);
	addAndMakeVisible(reverb);
}
TnpMidiSynthAudioProcessorEditor::~TnpMidiSynthAudioProcessorEditor()
{
}

//=============================================================================
void TnpMidiSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);
}

void TnpMidiSynthAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area (getLocalBounds());
	juce::Rectangle<int> numVoicesArea (area.removeFromTop(20));
	numVoicesLabel.setBounds(numVoicesArea.removeFromLeft(getWidth() / 2));
	numVoicesInput.setBounds(numVoicesArea.removeFromLeft(getWidth() / 2));

	oscillator.setBounds(area.removeFromTop(180));
	reverb.setBounds(area.removeFromTop(100));
}

void TnpMidiSynthAudioProcessorEditor::comboBoxChanged(ComboBox * comboBoxThatHasChanged)
{
	float currentNumVoices = *processor.treeState.getRawParameterValue("numVoices") + 1;
	processor.setNumVoices((int)currentNumVoices);
}
