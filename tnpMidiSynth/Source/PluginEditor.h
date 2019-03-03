/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "TnpLookAndFeel.h"
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
    TnpMidiSynthAudioProcessorEditor (TnpMidiSynthAudioProcessor&);
    ~TnpMidiSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	TnpMidiSynthAudioProcessor& processor;
	AudioProcessorValueTreeState& treeState;
	MidiKeyboardState& midiState;

	TnpLookAndFeel tnpLookAndFeel;

	Label labelTitle;
	Label numVoicesLabel;
	Label gainLabel;

	juce::Image backgroundImage;

	ComboBox numVoicesInput;
	Slider gainSlider;

	MidiKeyboardComponent midiKeyboard;

	OscillatorEditor oscillator1GUI;
	OscillatorEditor oscillator2GUI;
	FilterEditor filterGUI;
	LFOEditor lfoGUI;
	DelayEditor delayGUI;
	ReverbEditor reverbGUI;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> attNumVoices;

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpMidiSynthAudioProcessorEditor)
};
