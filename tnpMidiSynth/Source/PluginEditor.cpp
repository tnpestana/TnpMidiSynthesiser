/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
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
    masterGUI(p),
	oscillator1GUI(p, 1),
	oscillator2GUI(p, 2),
	filterGUI(p),
    lfoGUI(p),
    delayGUI(p),
    reverbGUI(p),
    distortionGUI(p)

{
    // Main editor's size.
	setSize(790, 610);
	setLookAndFeel(&tnpLookAndFeel);
	setResizable(false, false);

	backgroundImage = ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);

    addAndMakeVisible(masterGUI);
	addAndMakeVisible(oscillator1GUI);
	addAndMakeVisible(oscillator2GUI);
	addAndMakeVisible(filterGUI);
	addAndMakeVisible(lfoGUI);
	addAndMakeVisible(reverbGUI);
	addAndMakeVisible(delayGUI);
    addAndMakeVisible(distortionGUI);
	addAndMakeVisible(midiKeyboard);
	
	midiKeyboard.setLowestVisibleKey(36);
}

TnpMidiSynthAudioProcessorEditor::~TnpMidiSynthAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//=============================================================================
void TnpMidiSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::lightslategrey);
	//g.drawImageAt(backgroundImage, 0, 0);

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

	// MIDI keyboard area.
	midiKeyboard.setBounds(area.removeFromBottom(100).reduced(5));

	juce::Rectangle<int> left (area.removeFromLeft(area.getWidth() / 3));
    juce::Rectangle<int> center (area.removeFromLeft(area.getWidth() / 2));
	juce::Rectangle<int> right (area);

	// Oscillator area.
	oscillator1GUI.setBounds(left.removeFromTop(200).reduced(5));
	oscillator2GUI.setBounds(center.removeFromTop(200).reduced(5));

	// IRRFilter area.
	filterGUI.setBounds(left.removeFromTop(170).reduced(5));
	
    // Distortion area.
	lfoGUI.setBounds((center.removeFromTop(170).reduced(5)));
	
    // Delay area.
	delayGUI.setBounds(center.reduced(5));
	
    // Reverb area.
	reverbGUI.setBounds(left.reduced(5));
    
    // Master area.
    masterGUI.setBounds(right.removeFromTop(200).reduced(5));
    
    // Distortion area.
    distortionGUI.setBounds(right.removeFromTop(170).reduced(5));
}
