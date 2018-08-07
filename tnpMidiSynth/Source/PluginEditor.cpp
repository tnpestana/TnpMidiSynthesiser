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
TnpMidiSynthAudioProcessorEditor::TnpMidiSynthAudioProcessorEditor (TnpMidiSynthAudioProcessor& p, AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p), processor (p), oscillatorGUI(p, apvts), reverbGUI(p, apvts), distortionGUI(p, apvts), delayGUI(p, apvts),
	filterGUI(p, apvts)
{
    // Main editor's size.
    //setSize (250, 360);
	setSize(300, 600);
	setResizable(true, true);

	addAndMakeVisible(oscillatorGUI);
	addAndMakeVisible(filterGUI);
	addAndMakeVisible(distortionGUI);
	addAndMakeVisible(reverbGUI);
	addAndMakeVisible(delayGUI);
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

	// Color scheme for properties that always remain the same.
	getLookAndFeel().setColour(Slider::ColourIds::backgroundColourId, Colours::floralwhite);
	getLookAndFeel().setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::floralwhite);
	getLookAndFeel().setColour(Slider::ColourIds::thumbColourId, Colours::cadetblue);
	getLookAndFeel().setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::black);

	getLookAndFeel().setColour(ComboBox::textColourId, Colours::black);
	getLookAndFeel().setColour(ComboBox::backgroundColourId, Colours::lightgrey);
	getLookAndFeel().setColour(ComboBox::outlineColourId, Colours::cadetblue);

	getLookAndFeel().setColour(PopupMenu::ColourIds::backgroundColourId ,Colours::lightgrey);
	getLookAndFeel().setColour(PopupMenu::textColourId, Colours::black);

	getLookAndFeel().setColour(Label::textColourId, Colours::black);
}

void TnpMidiSynthAudioProcessorEditor::resized()
{
	// Total main editor's area.
	juce::Rectangle<int> area (getLocalBounds());

	// Oscillator area.
	oscillatorGUI.setBounds(area.removeFromTop(200).reduced(5));

	// IRRFilter area.
	filterGUI.setBounds(area.removeFromTop(100).reduced(5));

	// Distortion area.
	distortionGUI.setBounds(area.removeFromTop(100).reduced(5));

	// Delay area.
	delayGUI.setBounds(area.removeFromTop(100).reduced(5));

	// Reverb area.
	reverbGUI.setBounds(area.reduced(5));
}