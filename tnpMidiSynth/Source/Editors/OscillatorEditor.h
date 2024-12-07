/*
 ==============================================================================
 
 OscillatorEditor.h
 Created: 17 Apr 2018 1:57:27pm
 Author:  Tiago Pestana
 
 Main application is suposed to run more than one oscillator, so here is a
 template for its GUI added to the main editor as many times as needed.
 
 ==============================================================================
 */

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "../Processors/PluginProcessor.h"
#include "../Colours/Palette.h"

class OscillatorEditor : public Component
{
public:
    OscillatorEditor(TnpMidiSynthAudioProcessor&, int);
    ~OscillatorEditor();
    
    void paint(Graphics&) override;
    void resized() override;
    
private:
    TnpMidiSynthAudioProcessor& processor;
    AudioProcessorValueTreeState& treeState;
    
    int osc;
    
    Slider attackSlider;
    Slider decaySlider; 
    Slider sustainSlider;
    Slider releaseSlider; 
    Slider transposeSlider;
    
    ToggleButton toggle;
    
    Label attackLabel;
    Label decayLabel;
    Label sustainLabel;
    Label releaseLabel;  
    Label oscTypeLabel;
    Label titleLabel;
    Label transposeLabel;
    
    ComboBox oscTypeInput;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attAttack;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attDecay;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attSustain;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attRelease;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attTranspose;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> attOscType;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> attOsc2Toggle;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorEditor)
};
