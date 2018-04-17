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
    setSize (400, 300);

	addAndMakeVisible(&oscillator);
	addAndMakeVisible(&reverb);
}
TnpMidiSynthAudioProcessorEditor::~TnpMidiSynthAudioProcessorEditor()
{
}

//==============================================================================
void TnpMidiSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);
}

void TnpMidiSynthAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area (getLocalBounds());
	oscillator.setBounds(area.removeFromTop(200));
	reverb.setBounds(area.removeFromTop(100));
}
