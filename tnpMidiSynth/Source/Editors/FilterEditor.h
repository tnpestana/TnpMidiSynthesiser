/*
 ==============================================================================
 
 FilterEditor.h
 Created: 7 Aug 2018 6:24:53pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Processors/PluginProcessor.h"
#include "../Colours/Palette.h"

class FilterEditor : public Component
{
public:
    FilterEditor(TnpMidiSynthAudioProcessor&);
    ~FilterEditor();
    
private:
    void paint(Graphics&) override;
    void resized() override;
    
    TnpMidiSynthAudioProcessor& processor;
    AudioProcessorValueTreeState& treeState;
    
    ToggleButton toggleFilter;
    
    Label labelFilterTitle;
    Label labelFilterType;
    Label labelFilterCutoff;
    Label labelFilterQ;
    Label labelFilterGainFactor;
    
    ComboBox comboFilterType;
    Slider sliderFilterCutoff;
    Slider sliderFilterQ;
    Slider sliderFilterGainFactor;
    
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> attToggle;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> attFilterType;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attCutoff;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attQ;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attGainFactor;
};
