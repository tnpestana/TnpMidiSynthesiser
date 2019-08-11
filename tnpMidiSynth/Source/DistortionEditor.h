/*
  ==============================================================================

    TnpDistortionEditor.h
    Created: 11 Aug 2019 8:17:19pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class DistortionEditor : public Component
{
public:
    DistortionEditor(TnpMidiSynthAudioProcessor&);
    ~DistortionEditor();

private:
    void paint(Graphics&) override;
    void resized() override;

    TnpMidiSynthAudioProcessor& processor;
    AudioProcessorValueTreeState& treeState;

    ToggleButton toggleDistortion;

    ComboBox comboDistortionType;

    Label labelTitle;
    Label labelDistortionType;

    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> attDistortionType;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> attToggle;
};
