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
	setSize(600, 370);
	setResizable(true, true);

	addAndMakeVisible(labelTitle);
	addAndMakeVisible(oscillatorGUI);
	addAndMakeVisible(filterGUI);
	addAndMakeVisible(distortionGUI);
	addAndMakeVisible(reverbGUI);
	addAndMakeVisible(delayGUI);

	labelTitle.setJustificationType(Justification::centred);
	labelTitle.setText("TNP MIDI Synth", dontSendNotification);
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
	labelTitle.setColour(Label::backgroundColourId, Colours::black);
	labelTitle.setColour(Label::textColourId, Colours::white);

	// Color scheme for properties that always remain the same.
	getLookAndFeel().setColour(Slider::backgroundColourId, Colours::floralwhite);
	getLookAndFeel().setColour(Slider::rotarySliderOutlineColourId, Colours::floralwhite);
	getLookAndFeel().setColour(Slider::thumbColourId, Colours::cadetblue);
	getLookAndFeel().setColour(Slider::rotarySliderFillColourId, Colours::black);

	getLookAndFeel().setColour(ComboBox::textColourId, Colours::black);
	getLookAndFeel().setColour(ComboBox::backgroundColourId, Colours::lightgrey);
	getLookAndFeel().setColour(ComboBox::outlineColourId, Colours::cadetblue);

	getLookAndFeel().setColour(PopupMenu::backgroundColourId ,Colours::lightgrey);
	getLookAndFeel().setColour(PopupMenu::textColourId, Colours::black);

	getLookAndFeel().setColour(Label::textColourId, Colours::black);
}

void TnpMidiSynthAudioProcessorEditor::resized()
{
	// Total main editor's area.
	juce::Rectangle<int> area (getLocalBounds());

	labelTitle.setBounds(area.removeFromTop(40).reduced(5));

	juce::Rectangle<int> left (area.removeFromLeft(area.getWidth() / 2));
	juce::Rectangle<int> right (area);
	

	// Oscillator area.
	oscillatorGUI.setBounds(left.removeFromTop(200).reduced(5));

	// IRRFilter area.
	filterGUI.setBounds(left.reduced(5));

	// Distortion area.
	distortionGUI.setBounds(right.removeFromTop(area.getHeight() / 3).reduced(5));

	// Delay area.
	delayGUI.setBounds(right.removeFromTop(area.getHeight() / 3).reduced(5));

	// Reverb area.
	reverbGUI.setBounds(right.reduced(5));
}