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
    : AudioProcessorEditor (&p), 
	//	Processor references
	processor (p),
	treeState(p.getTreeState()),
	midiState (p.getMidiState()),
	midiKeyboard(p.getMidiState() , MidiKeyboardComponent::horizontalKeyboard),
	//	Editor components
	oscillator1GUI(p, 1),
	oscillator2GUI(p, 2),
	reverbGUI(p), 
	lfoGUI(p), 
	delayGUI(p), 
	filterGUI(p),
	//	Attachments
	attNumVoices(std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
		(treeState, "numVoices", numVoicesInput)),
	gainAttachment(std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "gain", gainSlider))
{
    // Main editor's size.
	setSize(650, 660);
	setLookAndFeel(&tnpLookAndFeel);
	setResizable(false, false);

	backgroundImage = ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);

	addAndMakeVisible(numVoicesLabel);
	addAndMakeVisible(numVoicesInput);
	addAndMakeVisible(oscillator1GUI);
	addAndMakeVisible(oscillator2GUI);
	addAndMakeVisible(filterGUI);
	addAndMakeVisible(lfoGUI);
	addAndMakeVisible(reverbGUI);
	addAndMakeVisible(delayGUI);
	addAndMakeVisible(labelTitle);
	addAndMakeVisible(gainSlider);
	addAndMakeVisible(gainLabel);
	addAndMakeVisible(midiKeyboard);

	labelTitle.setText("TNP MIDI Synth", dontSendNotification);
	gainLabel.setText("GAIN", dontSendNotification);
	numVoicesLabel.setText("voices: ", dontSendNotification);

	labelTitle.setJustificationType(Justification::centred);
	gainLabel.setJustificationType(Justification::centredTop);
	numVoicesLabel.setJustificationType(Justification::bottomLeft);

	gainSlider.setSliderStyle(Slider::LinearVertical);
	gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 45, 20);
	
	//  Populate combo boxes with strings stored as parameter choices
	if (auto* choiceParameter = dynamic_cast<AudioParameterChoice*>(treeState.getParameter("numVoices")))
	{
		numVoicesInput.addItemList(choiceParameter->choices, 1);
		numVoicesInput.setSelectedId(choiceParameter->getIndex() + 1);
	}
	
	midiKeyboard.setLowestVisibleKey(36);
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

	numVoicesInput.setColour(ComboBox::textColourId, Colours::black);

	gainLabel.setColour(Label::backgroundColourId, Colours::lightgrey);
	gainLabel.setColour(Label::outlineColourId, Colours::black);
	gainSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	//gainSlider.setColour(Slider::textBoxOutlineColourId, Colours::lightgrey);

	// Color scheme for properties that always remain the same.
	getLookAndFeel().setColour(Slider::backgroundColourId, Colours::floralwhite);
	getLookAndFeel().setColour(Slider::ColourIds::trackColourId, Colours::lightgrey);
	getLookAndFeel().setColour(Slider::rotarySliderFillColourId, Colours::lightgrey);
	getLookAndFeel().setColour(Slider::rotarySliderOutlineColourId, Colours::black);
	getLookAndFeel().setColour(Slider::thumbColourId, Colours::black);
	getLookAndFeel().setColour(Slider::textBoxTextColourId, Colours::black);
	//getLookAndFeel().setColour(Slider::textBoxOutlineColourId, Colours::cadetblue);

	getLookAndFeel().setColour(ComboBox::textColourId, Colours::black);
	getLookAndFeel().setColour(ComboBox::backgroundColourId, Colours::floralwhite);
	getLookAndFeel().setColour(ComboBox::outlineColourId, Colours::lightgrey);
	getLookAndFeel().setColour(ComboBox::arrowColourId, Colours::cadetblue);

	getLookAndFeel().setColour(PopupMenu::backgroundColourId ,Colours::floralwhite);
	getLookAndFeel().setColour(PopupMenu::textColourId, Colours::black);

	getLookAndFeel().setColour(Label::textColourId, Colours::black);

	getLookAndFeel().setColour(ToggleButton::tickColourId, Colours::black);
	getLookAndFeel().setColour(ToggleButton::tickDisabledColourId, Colours::floralwhite);

	getLookAndFeel().setColour(TextButton::buttonColourId, Colours::lightgrey);
	getLookAndFeel().setColour(TextButton::textColourOffId, Colours::black);
}

void TnpMidiSynthAudioProcessorEditor::resized()
{
	// Total main editor's area.
	juce::Rectangle<int> area (getLocalBounds());
	juce::Rectangle<int> topSection (area.removeFromTop(50).reduced(5));

	//  Number of voices selection area.   
	juce::Rectangle<int> numVoicesArea(topSection.removeFromLeft(60));
	numVoicesLabel.setBounds(numVoicesArea.removeFromTop(15));
	numVoicesInput.setBounds(numVoicesArea.reduced(2));

	// MIDI keyboard area.
	midiKeyboard.setBounds(area.removeFromBottom(100).reduced(5));

	// Gain controls area. 
	juce::Rectangle<int> gainLocation(area.removeFromRight(50).reduced(5));
	gainLabel.setBounds(gainLocation.removeFromTop(20).reduced(2));
	gainSlider.setBounds(gainLocation);

	juce::Rectangle<int> left (area.removeFromLeft(area.getWidth() / 2));
	juce::Rectangle<int> right (area);

	// Oscillator area.
	oscillator1GUI.setBounds(left.removeFromTop(200).reduced(5));
	oscillator2GUI.setBounds(right.removeFromTop(200).reduced(5));

	// IRRFilter area.
	filterGUI.setBounds(left.removeFromTop(150).reduced(5));
	// Distortion area.
	lfoGUI.setBounds((right.removeFromTop(150).reduced(5)));
	// Delay area.
	delayGUI.setBounds(right.reduced(5));
	// Reverb area.
	reverbGUI.setBounds(left.reduced(5));
}