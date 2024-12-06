/*
 ==============================================================================
 
 LFOEditor.cpp
 Created: 30 Aug 2018 6:26:46pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#include "LFOEditor.h"

LFOEditor::LFOEditor(TnpMidiSynthAudioProcessor& p)
//  Processor references
: processor (p),
treeState(p.getTreeState()),
//  Parameter attachments
attOscType (std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
            (treeState, "lfoOscType", comboOscType)),
attDepth (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
          (treeState, "lfoDepth", sliderLfoDepth)),
attRate (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
         (treeState, "lfoRate", sliderLfoRate)),
attToggle (std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
           (treeState, "lfoToggle", toggleLfo))
{
    labelTitle.setText("LFO", dontSendNotification);
    labelLfoOscType.setText("wave: ", dontSendNotification);
    labelLfoDepth.setText("depth", dontSendNotification);
    labelLfoRate.setText("rate", dontSendNotification);
    
    labelLfoOscType.setJustificationType(Justification::centredRight);
    labelLfoDepth.setJustificationType(Justification::centredBottom);
    labelLfoRate.setJustificationType(Justification::centredBottom);
    labelTitle.setJustificationType(Justification::centred);
    
    sliderLfoDepth.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderLfoDepth.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    sliderLfoRate.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderLfoRate.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    
    sliderLfoDepth.setTextValueSuffix(" %");
    sliderLfoRate.setTextValueSuffix(" Hz");
    
    //  Populate combo boxes with strings stored as paramneter choices
    if (auto* choiceParameter = dynamic_cast<AudioParameterChoice*>(treeState.getParameter("lfoOscType")))
    {
        comboOscType.addItemList(choiceParameter->choices, 1);
        comboOscType.setSelectedId(choiceParameter->getIndex() + 1);
    }
    
    addAndMakeVisible(labelTitle);
    addAndMakeVisible(toggleLfo);
    addAndMakeVisible(comboOscType);
    addAndMakeVisible(sliderLfoDepth);
    addAndMakeVisible(sliderLfoRate);
    addAndMakeVisible(labelLfoOscType);
    addAndMakeVisible(labelLfoDepth);
    addAndMakeVisible(labelLfoRate);
}

LFOEditor::~LFOEditor()
{
}

void LFOEditor::paint(Graphics& g)
{
    g.fillAll (Colours::yellow);
}

void LFOEditor::resized()
{
    const int labelHeight = 15;
    
    juce::Rectangle<int> area (getLocalBounds());
    juce::Rectangle<int> titleSection    (area.removeFromTop(20));
    toggleLfo.setBounds (titleSection.removeFromLeft(22));
    labelTitle.setBounds (titleSection.reduced(2));
    
    juce::Rectangle<int> topSection (area.removeFromTop(area.getHeight() / 4).reduced(5));
    juce::Rectangle<int> slidersSection (area.reduced(5));
    
    labelLfoOscType.setBounds (topSection.removeFromLeft(topSection.getWidth() / 5));
    comboOscType.setBounds (topSection);
    
    juce::Rectangle<int> filterGainFactorSection (slidersSection.removeFromLeft(slidersSection.getWidth() / 4));
    labelLfoRate.setBounds (filterGainFactorSection.removeFromTop(labelHeight));
    sliderLfoRate.setBounds (filterGainFactorSection);
    
    juce::Rectangle<int> filterCutoffSection (slidersSection.removeFromLeft(slidersSection.getWidth() / 3));
    labelLfoDepth.setBounds (filterCutoffSection.removeFromTop(labelHeight));
    sliderLfoDepth.setBounds (filterCutoffSection);
}
