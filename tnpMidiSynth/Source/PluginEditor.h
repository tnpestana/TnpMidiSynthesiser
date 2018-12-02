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
	Label gainLabel;

	juce::Image backgroundImage;

	Slider gainSlider;

	OscillatorEditor oscillatorGUI;
	FilterEditor filterGUI;
	LFOEditor lfoGUI;
	DelayEditor delayGUI;
	ReverbEditor reverbGUI;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpMidiSynthAudioProcessorEditor)
};
