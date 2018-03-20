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
class NewSynthesiserAudioProcessorEditor  : public AudioProcessorEditor,
											public MidiKeyboardStateListener
{
public:
    NewSynthesiserAudioProcessorEditor (NewSynthesiserAudioProcessor&, 
		MidiKeyboardState&);
    ~NewSynthesiserAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewSynthesiserAudioProcessor& processor;

	Label label;

	MidiKeyboardComponent keyboardComponent;
	MidiKeyboardState& keyboardState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewSynthesiserAudioProcessorEditor)

	// Inherited via MidiKeyboardStateListener
	virtual void handleNoteOn(MidiKeyboardState * source, int midiChannel, int midiNoteNumber, float velocity) override;
	virtual void handleNoteOff(MidiKeyboardState * source, int midiChannel, int midiNoteNumber, float velocity) override;

	// Inherited via MidiInputCallback
	//virtual void handleIncomingMidiMessage(MidiInput * source, const MidiMessage & message) override;
};
