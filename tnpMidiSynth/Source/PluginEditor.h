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
#include "FilterEditor.h"
#include "LFOEditor.h"

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

	Label labelTitle;

	juce::Image backgroundImage;

	OscillatorEditor oscillatorGUI;
	FilterEditor filterGUI;
	//DistortionEditor distortionGUI;
	LFOEditor lfoGUI;
	DelayEditor delayGUI;
	ReverbEditor reverbGUI;

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpMidiSynthAudioProcessorEditor)
};
