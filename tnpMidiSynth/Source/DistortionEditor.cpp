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
    attToggle (std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
        (treeState, "distortionToggle", toggleDistortion))
{
    sliderGain.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderGain.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    sliderGain.setTextValueSuffix(" dB");
    
    labelTitle.setText("DISTORTION", dontSendNotification);
    labelTitle.setJustificationType(Justification::centred);
    labelDistortionType.setText("type:", dontSendNotification);
    labelGain.setText("gain", dontSendNotification);
    labelGain.setJustificationType(Justification::centred);

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
    addAndMakeVisible(comboDistortionType);
}

DistortionEditor::~DistortionEditor()
{
}

void DistortionEditor::paint(Graphics &)
{
    labelTitle.setColour(Label::backgroundColourId, Colours::lightgrey);
    labelTitle.setColour(Label::outlineColourId, Colours::black);
    comboDistortionType.setColour(ComboBox::textColourId, Colours::black);
    sliderGain.setColour(Slider::textBoxTextColourId, Colours::black);
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
}
