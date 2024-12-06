/*
 ==============================================================================
 
 MasterEditor.h
 Created: 25 Aug 2019 5:18:55pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Processors/PluginProcessor.h"

class MasterEditor : public Component
{
    public:
    MasterEditor(TnpMidiSynthAudioProcessor&);
    ~MasterEditor();
    
    private:
    void paint(Graphics& g) override;
    void resized() override;
    
    TnpMidiSynthAudioProcessor& processor;
    AudioProcessorValueTreeState& treeState;
    
    Label labelTitle;
    Label numVoicesLabel;
    Label gainLabel;
    
    ComboBox numVoicesInput;
    Slider gainSlider;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> attNumVoices;
};
