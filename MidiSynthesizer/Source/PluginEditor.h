/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MidiSynthesizerAudioProcessorEditor  : public AudioProcessorEditor,
											 public MidiKeyboardStateListener,
											 public MidiInputCallback,
											 public Button::Listener
{
public:
    MidiSynthesizerAudioProcessorEditor (MidiSynthesizerAudioProcessor&, 
		MidiKeyboardState&, AudioDeviceManager&);
    ~MidiSynthesizerAudioProcessorEditor();

	//==============================================================================
	void updateMidiInputList();
	void setMidiInput(int);

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiSynthesizerAudioProcessor& processor;

	AudioDeviceManager& deviceManager;

	MidiKeyboardComponent keyboardComponent;
	MidiKeyboardState& keyboardState;

	ComboBox midiInputList;
	TextButton refreshListButton;

	Label midiInputListLabel;
	Label midiNoteLabel;

	int lastInputIndex;
	bool isAddingFromMidiInput;

	// Inherited via MidiInputCallback
	virtual void handleIncomingMidiMessage(MidiInput * source, const MidiMessage & message) override;

	// Inherited via MidiKeyboardStateListener
	virtual void handleNoteOn(MidiKeyboardState * source, int midiChannel, int midiNoteNumber, float velocity) override;
	virtual void handleNoteOff(MidiKeyboardState * source, int midiChannel, int midiNoteNumber, float velocity) override;

	// Inherited via Listener
	virtual void buttonClicked(Button *) override;

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiSynthesizerAudioProcessorEditor)
};
