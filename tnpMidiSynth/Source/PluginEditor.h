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
#include "DistortionEditor.h"
#include "DelayEditor.h"

//==============================================================================
/**
*/
class TnpMidiSynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TnpMidiSynthAudioProcessorEditor (TnpMidiSynthAudioProcessor&, AudioProcessorValueTreeState&);
    ~TnpMidiSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	TnpMidiSynthAudioProcessor& processor;

	OscillatorEditor oscillatorGUI;
	DistortionEditor distortionGUI;
	DelayEditor delayGUI;
	ReverbEditor reverbGUI;

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpMidiSynthAudioProcessorEditor)
};
