/*
 ==============================================================================
 
 MasterEditor.cpp
 Created: 25 Aug 2019 5:18:55pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#include "MasterEditor.h"

MasterEditor::MasterEditor(TnpMidiSynthAudioProcessor& p)
//  Processor references
: processor (p),
treeState(p.getTreeState()),
//  Parameter attachments
gainAttachment(std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "gain", gainSlider)),
attNumVoices(std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(treeState, "numVoices", numVoicesInput))
{
    addAndMakeVisible(numVoicesLabel);
    addAndMakeVisible(numVoicesInput);
    addAndMakeVisible(labelTitle);
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(gainLabel);
    
    labelTitle.setText("MASTER", dontSendNotification);
    gainLabel.setText("gain", dontSendNotification);
    numVoicesLabel.setText("voices: ", dontSendNotification);
    
    labelTitle.setJustificationType(Justification::centred);
    gainLabel.setJustificationType(Justification::centredBottom);
    numVoicesLabel.setJustificationType(Justification::bottomLeft);
    
    gainSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    gainSlider.setTextValueSuffix(" dB");
    
    //  Populate combo boxes with strings stored as parameter choices
    if (auto* choiceParameter = dynamic_cast<AudioParameterChoice*>(treeState.getParameter("numVoices")))
    {
        numVoicesInput.addItemList(choiceParameter->choices, 1);
        numVoicesInput.setSelectedId(choiceParameter->getIndex() + 1);
    }
}

MasterEditor::~MasterEditor()
{
}

void MasterEditor::paint(Graphics& g)
{
    g.fillAll (Palette::primaryColor);
}

void MasterEditor::resized()
{
    const int labelHeight = 20;
    
    juce::Rectangle<int> area (getLocalBounds());
    juce::Rectangle<int> titleSection (area.removeFromTop(20));
    labelTitle.setBounds (titleSection.reduced(2));
    
    juce::Rectangle<int> topSection (area.removeFromTop(area.getHeight() / 3));
    juce::Rectangle<int> slidersSection (area);
    
    numVoicesLabel.setBounds(topSection.removeFromTop(20));
    numVoicesInput.setBounds(topSection.reduced(2));
    
    juce::Rectangle<int> filterGainFactorSection (slidersSection.removeFromLeft(slidersSection.getWidth() / 4));
    gainLabel.setBounds (filterGainFactorSection.removeFromTop(labelHeight));
    gainSlider.setBounds (filterGainFactorSection);
}
