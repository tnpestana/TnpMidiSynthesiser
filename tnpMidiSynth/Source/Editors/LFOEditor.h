/*
 ==============================================================================
 
 LFOEditor.h
 Created: 30 Aug 2018 6:26:46pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Processors/PluginProcessor.h"

class LFOEditor : public Component
{
public:
    LFOEditor(TnpMidiSynthAudioProcessor&);
    ~LFOEditor();
    
private:
    void paint(Graphics&) override;
    void resized() override;
    
    TnpMidiSynthAudioProcessor& processor;
    AudioProcessorValueTreeState& treeState;
    
    ToggleButton toggleLfo;
    
    ComboBox comboOscType;
    
    Label labelTitle;
    Label labelLfoOscType;
    Label labelLfoDepth;
    Label labelLfoRate;
    
    Slider sliderLfoDepth;
    Slider sliderLfoRate;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> attOscType;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attDepth;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attRate;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> attToggle;
};
