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
TnpMidiSynthAudioProcessorEditor::TnpMidiSynthAudioProcessorEditor (TnpMidiSynthAudioProcessor& p, 
																	AudioProcessorValueTreeState& apvts,
																	MidiKeyboardState& mks)
    : AudioProcessorEditor (&p), 
	processor (p), 
	midiKeyboard(mks, MidiKeyboardComponent::horizontalKeyboard), 
	oscillatorGUI(p, apvts), 
	reverbGUI(p, apvts), 
	lfoGUI(p, apvts), 
	delayGUI(p, apvts), 
	filterGUI(p, apvts)
{
    // Main editor's size.
	setSize(650, 500);
	setResizable(true, true);

	backgroundImage = ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);

	addAndMakeVisible(labelTitle);
	addAndMakeVisible(oscillatorGUI);
	addAndMakeVisible(filterGUI);
	addAndMakeVisible(lfoGUI);
	addAndMakeVisible(reverbGUI);
	addAndMakeVisible(delayGUI);
	addAndMakeVisible(midiKeyboard);

	// Gain.
	addAndMakeVisible(gainSlider);
	gainSlider.setSliderStyle(Slider::LinearVertical);
	gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 45, 20);
	addAndMakeVisible(gainLabel);
	gainLabel.setText("GAIN", dontSendNotification);
	gainLabel.setJustificationType(Justification::centredTop);
	gainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, "gain", gainSlider);

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
	g.drawImageAt(backgroundImage, 0, 0);

	//Image oscBackground = ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);
	//g.drawImageAt(oscBackground, 0, 0);
	labelTitle.setColour(Label::backgroundColourId, Colours::black);
	labelTitle.setColour(Label::textColourId, Colours::white);

	gainLabel.setColour(Label::backgroundColourId, Colours::cadetblue);
	gainSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	gainSlider.setColour(Slider::textBoxOutlineColourId, Colours::cadetblue);

	// Color scheme for properties that always remain the same.
	getLookAndFeel().setColour(Slider::backgroundColourId, Colours::floralwhite);
	getLookAndFeel().setColour(Slider::rotarySliderOutlineColourId, Colours::floralwhite);
	getLookAndFeel().setColour(Slider::thumbColourId, Colours::cadetblue);
	getLookAndFeel().setColour(Slider::textBoxTextColourId, Colours::black);
	getLookAndFeel().setColour(Slider::textBoxOutlineColourId, Colours::cadetblue);

	getLookAndFeel().setColour(ComboBox::textColourId, Colours::black);
	getLookAndFeel().setColour(ComboBox::backgroundColourId, Colours::floralwhite);
	getLookAndFeel().setColour(ComboBox::outlineColourId, Colours::cadetblue);
	getLookAndFeel().setColour(ComboBox::arrowColourId, Colours::cadetblue);

	getLookAndFeel().setColour(PopupMenu::backgroundColourId ,Colours::floralwhite);
	getLookAndFeel().setColour(PopupMenu::textColourId, Colours::black);

	getLookAndFeel().setColour(Label::textColourId, Colours::black);

	getLookAndFeel().setColour(ToggleButton::tickColourId, Colours::floralwhite);
	getLookAndFeel().setColour(ToggleButton::tickDisabledColourId, Colours::floralwhite);
	getLookAndFeel().setColour(ToggleButton::textColourId, Colours::floralwhite);

	getLookAndFeel().setColour(TextButton::buttonColourId, Colours::cadetblue);
}

void TnpMidiSynthAudioProcessorEditor::resized()
{
	// Total main editor's area.
	juce::Rectangle<int> area (getLocalBounds());
	juce::Rectangle<int> topSection (area.removeFromTop(40).reduced(5));

	midiKeyboard.setBounds(area.removeFromBottom(100).reduced(5));

	// Gain controls area. 
	juce::Rectangle<int> gainLocation(area.removeFromRight(50).reduced(5));
	gainLabel.setBounds(gainLocation.removeFromTop(20).reduced(2));
	gainSlider.setBounds(gainLocation);

	juce::Rectangle<int> left (area.removeFromLeft(area.getWidth() / 2));
	juce::Rectangle<int> right (area);

	// Oscillator area.
	oscillatorGUI.setBounds(left.removeFromTop(200).reduced(5));
	// IRRFilter area.
	filterGUI.setBounds(left.reduced(5));
	// Distortion area.
	lfoGUI.setBounds((right.removeFromTop(right.getHeight() * 0.33).reduced(5)));
	// Delay area.
	delayGUI.setBounds(right.removeFromTop(right.getHeight() * 0.5).reduced(5));
	// Reverb area.
	reverbGUI.setBounds(right.reduced(5));
}