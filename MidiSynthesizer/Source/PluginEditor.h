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
											 public MidiInputCallback
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

	void handleNoteOn(MidiKeyboardState*, int, int, float) override;
	void handleNoteOff(MidiKeyboardState*, int, int, float) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiSynthesizerAudioProcessor& processor;
	MidiKeyboardState& keyboardState;
	AudioDeviceManager& deviceManager;

	MidiKeyboardComponent keyboardComponent;
	ComboBox midiInputList;
	Label midiInputListLabel;

	Label midiNoteLabel;

	int lastInputIndex;
	bool isAddingFromMidiInput;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiSynthesizerAudioProcessorEditor)

	// Inherited via MidiInputCallback
	virtual void handleIncomingMidiMessage(MidiInput * source, const MidiMessage & message) override;
};
