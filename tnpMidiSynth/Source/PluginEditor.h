/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "OscillatorEditor.h"
#include "ReverbEditor.h"

//==============================================================================
/**
*/
class TnpMidiSynthAudioProcessorEditor  : public AudioProcessorEditor, ComboBox::Listener
{
public:
    TnpMidiSynthAudioProcessorEditor (TnpMidiSynthAudioProcessor&);
    ~TnpMidiSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	TnpMidiSynthAudioProcessor& processor;

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> numVoicesAttachment;

	ComboBox numVoicesInput;
	Label numVoicesLabel;

	OscillatorEditor oscillator;
	ReverbEditor reverb;

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpMidiSynthAudioProcessorEditor)

		// Inherited via Listener
		virtual void comboBoxChanged(ComboBox * comboBoxThatHasChanged) override;
};
