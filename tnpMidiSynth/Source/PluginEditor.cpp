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
    : AudioProcessorEditor (&p), processor (p), oscillatorGUI(p), reverbGUI(p), distortionGUI(p)
{
    // Main editor's size.
    //setSize (250, 360);
	setSize(300, 500);
	setResizable(true, true);

	addAndMakeVisible(oscillatorGUI);
	addAndMakeVisible(distortionGUI);
	addAndMakeVisible(reverbGUI);
}
TnpMidiSynthAudioProcessorEditor::~TnpMidiSynthAudioProcessorEditor()
{
}

//=============================================================================
void TnpMidiSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::lightslategrey);

	//Image oscBackground = ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);
	//g.drawImageAt(oscBackground, 0, 0);

	// Color scheme for child components.
	getLookAndFeel().setColour(Slider::ColourIds::trackColourId, Colours::lightpink);
	getLookAndFeel().setColour(Slider::ColourIds::backgroundColourId, Colours::lightyellow);
	getLookAndFeel().setColour(Slider::ColourIds::thumbColourId, Colours::coral);
	getLookAndFeel().setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::lightpink);
	getLookAndFeel().setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::lightyellow);
	getLookAndFeel().setColour(ComboBox::textColourId, Colours::black);
	getLookAndFeel().setColour(ComboBox::backgroundColourId, Colours::mediumseagreen);
	getLookAndFeel().setColour(PopupMenu::textColourId, Colours::black);
	getLookAndFeel().setColour(Label::textColourId, Colours::black);
	getLookAndFeel().setColour(Label::backgroundColourId, Colours::mediumseagreen);
}

void TnpMidiSynthAudioProcessorEditor::resized()
{
	// Total main editor's area.
	juce::Rectangle<int> area (getLocalBounds());

	// Oscillator area.
	oscillatorGUI.setBounds(area.removeFromTop(300).reduced(5));

	// Distortion area.
	distortionGUI.setBounds(area.removeFromTop(100).reduced(5));

	// Reverb area.
	reverbGUI.setBounds(area.reduced(5));
}