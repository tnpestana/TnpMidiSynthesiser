/*
 ==============================================================================
 
 TnpDistortionEditor.h
 Created: 11 Aug 2019 8:17:19pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Processors/PluginProcessor.h"
#include "../Colours/Palette.h"

class DistortionEditor : public Component
{
    public:
    DistortionEditor(TnpMidiSynthAudioProcessor&);
    ~DistortionEditor();
    
    private:
    void paint(Graphics& g) override;
    void resized() override;
    
    TnpMidiSynthAudioProcessor& processor;
    AudioProcessorValueTreeState& treeState;
    
    ToggleButton toggleDistortion;
    Slider sliderGain;
    Slider sliderMix;
    ComboBox comboDistortionType;
    
    Label labelTitle;
    Label labelGain;
    Label labelMix;
    Label labelDistortionType;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> attDistortionType;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attGain;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attMix;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> attToggle;
};
