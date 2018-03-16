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
											 public MidiInputCallback,
											 public MidiKeyboardStateListener
{
public:
    MidiSynthesizerAudioProcessorEditor (MidiSynthesizerAudioProcessor&, 
		MidiKeyboardState&, AudioDeviceManager&);
    ~MidiSynthesizerAudioProcessorEditor();

	//==============================================================================
	void setMidiInput(int);

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiSynthesizerAudioProcessor& processor;
	MidiKeyboardState& keyboardState;
	AudioDeviceManager& deviceManager;

	MidiKeyboardComponent keyboardComponent;
	ComboBox midiInputList;
	Label midiInputListLabel;

	int lastInputIndex;
	bool isAddingFromMidiInput;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiSynthesizerAudioProcessorEditor)

	// Herdado por meio de MidiInputCallback
	virtual void handleIncomingMidiMessage(MidiInput * source, const MidiMessage & message) override;

	// Herdado por meio de MidiKeyboardStateListener
	virtual void handleNoteOn(MidiKeyboardState * source, int midiChannel, int midiNoteNumber, float velocity) override;
	virtual void handleNoteOff(MidiKeyboardState * source, int midiChannel, int midiNoteNumber, float velocity) override;
};
