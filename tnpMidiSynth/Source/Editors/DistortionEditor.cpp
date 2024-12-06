/*
 ==============================================================================
 
 TnpDistortionEditor.cpp
 Created: 11 Aug 2019 8:17:19pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#include "DistortionEditor.h"

DistortionEditor::DistortionEditor(TnpMidiSynthAudioProcessor& p)
//  Processor references
: processor (p),
treeState(p.getTreeState()),
//  Parameter attachments
attDistortionType (std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
                   (treeState, "distortionType", comboDistortionType)),
attGain (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "distortionGain", sliderGain)),
attMix (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "distortionMix", sliderMix)),
attToggle (std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
           (treeState, "distortionToggle", toggleDistortion))
{
    sliderGain.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderGain.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    sliderGain.setTextValueSuffix(" dB");
    sliderMix.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderMix.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    sliderMix.setTextValueSuffix(" %");
    
    labelTitle.setText("DISTORTION", dontSendNotification);
    labelTitle.setJustificationType(Justification::centred);
    labelDistortionType.setText("type: ", dontSendNotification);
    labelDistortionType.setJustificationType(Justification::centredRight);
    labelGain.setText("input gain", dontSendNotification);
    labelGain.setJustificationType(Justification::centred);
    labelMix.setText("drive", dontSendNotification);
    labelMix.setJustificationType(Justification::centred);
    
    //  Populate combo boxes with strings stored as parameter choices
    if (auto* choiceParameter = dynamic_cast<AudioParameterChoice*>(treeState.getParameter("distortionType")))
    {
        comboDistortionType.addItemList(choiceParameter->choices, 1);
        comboDistortionType.setSelectedId(choiceParameter->getIndex() + 1);
    }
    
    addAndMakeVisible(toggleDistortion);
    addAndMakeVisible(labelTitle);
    addAndMakeVisible(labelDistortionType);
    addAndMakeVisible(labelGain);
    addAndMakeVisible(sliderGain);
    addAndMakeVisible(labelMix);
    addAndMakeVisible(sliderMix);
    addAndMakeVisible(comboDistortionType);
}

DistortionEditor::~DistortionEditor()
{
}

void DistortionEditor::paint(Graphics& g)
{
    g.fillAll (Colours::pink);
}

void DistortionEditor::resized()
{
    const int labelHeight = 15;
    
    juce::Rectangle<int> area (getLocalBounds());
    juce::Rectangle<int> titleSection    (area.removeFromTop(20));
    toggleDistortion.setBounds (titleSection.removeFromLeft(22));
    labelTitle.setBounds (titleSection.reduced(2));
    
    juce::Rectangle<int> topSection (area.removeFromTop(area.getHeight() / 4).reduced(5));
    juce::Rectangle<int> slidersSection (area.reduced(5));
    
    labelDistortionType.setBounds (topSection.removeFromLeft(topSection.getWidth() / 5));
    comboDistortionType.setBounds (topSection);
    
    juce::Rectangle<int> sliderGainSection (slidersSection.removeFromLeft(slidersSection.getWidth() / 4));
    labelGain.setBounds (sliderGainSection.removeFromTop(labelHeight));
    sliderGain.setBounds (sliderGainSection);
    
    juce::Rectangle<int> sliderMixSection (slidersSection.removeFromLeft(slidersSection.getWidth() / 3));
    labelMix.setBounds (sliderMixSection.removeFromTop(labelHeight));
    sliderMix.setBounds (sliderMixSection);
}
