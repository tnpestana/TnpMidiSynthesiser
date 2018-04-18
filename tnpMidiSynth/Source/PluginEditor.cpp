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
	for(int i = 1; i < 11; i++)
		numVoicesInput.addItem((String)i, i);
	numVoicesInput.addListener(this);
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
    g.fillAll (Colours::black);
}

void TnpMidiSynthAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area (getLocalBounds());
	juce::Rectangle<int> numVoicesArea (area.removeFromTop(20));
	numVoicesLabel.setBounds(numVoicesArea.removeFromLeft(getWidth() / 2));
	numVoicesInput.setBounds(numVoicesArea.removeFromLeft(getWidth() / 2));

	oscillatorGUI.setBounds(area.removeFromTop(180));
	reverbGUI.setBounds(area.removeFromTop(80));
}

void TnpMidiSynthAudioProcessorEditor::comboBoxChanged(ComboBox * comboBoxThatHasChanged)
{
	float currentNumVoices = *processor.treeState.getRawParameterValue("numVoices") + 1;
	processor.setNumVoices((int)currentNumVoices);
}
