/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Processors/PluginProcessor.h"
#include "../Editors/MasterEditor.h"
#include "../UI/TnpLookAndFeel.h"
#include "../Editors/OscillatorEditor.h"
#include "../Editors/ReverbEditor.h"
#include "../Editors/DelayEditor.h"
#include "../Editors/FilterEditor.h"
#include "../Editors/LFOEditor.h"
#include "../Editors/DistortionEditor.h"


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
    VisualiserEditor& visualiser;
    
    TnpLookAndFeel tnpLookAndFeel;
    
    juce::Image backgroundImage;
    
    MidiKeyboardComponent midiKeyboard;
    
    MasterEditor masterGUI;
    OscillatorEditor oscillator1GUI;
    OscillatorEditor oscillator2GUI;
    FilterEditor filterGUI;
    LFOEditor lfoGUI;
    DelayEditor delayGUI;
    ReverbEditor reverbGUI;
    DistortionEditor distortionGUI;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpMidiSynthAudioProcessorEditor)
};
