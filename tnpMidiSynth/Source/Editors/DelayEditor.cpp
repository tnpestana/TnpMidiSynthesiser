/*
 ==============================================================================
 
 DelayEditor.cpp
 Created: 4 Aug 2018 6:29:27pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#include "DelayEditor.h"

DelayEditor::DelayEditor(TnpMidiSynthAudioProcessor& p)
//  Processor references
: processor (p),
treeState (p.getTreeState()),
//  Parameter attachments
attToggle (std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
           (treeState, "delayToggle", toggleDelay)),
attDelayTime (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
              (treeState, "delayTime", sliderDelayTime)),
attFeedback (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
             (treeState, "delayFeedback", sliderDelayFeedback)),
attMix (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (treeState, "delayMix", sliderdelayMix))
{
    labelTitle.setText("DELAY", dontSendNotification);
    labelDelayTime.setText("time", dontSendNotification);
    labelDelayFeedback.setText("feedback", dontSendNotification);
    labelDelayMix.setText("mix", dontSendNotification);
    
    labelTitle.setJustificationType(Justification::centred);
    labelDelayTime.setJustificationType(Justification::centredTop);
    labelDelayFeedback.setJustificationType(Justification::centredTop);
    labelDelayMix.setJustificationType(Justification::centredTop);
    
    sliderDelayTime.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderDelayFeedback.setSliderStyle(Slider::RotaryVerticalDrag);
    sliderdelayMix.setSliderStyle(Slider::RotaryVerticalDrag);
    
    sliderDelayTime.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    sliderDelayFeedback.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    sliderdelayMix.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
    
    sliderDelayTime.setTextValueSuffix(" ms");
    sliderDelayFeedback.setTextValueSuffix(" %");
    sliderdelayMix.setTextValueSuffix(" %");
    
    addAndMakeVisible(labelTitle);
    addAndMakeVisible(toggleDelay);
    addAndMakeVisible(labelDelayTime);
    addAndMakeVisible(sliderDelayTime);
    addAndMakeVisible(labelDelayFeedback);
    addAndMakeVisible(sliderDelayFeedback);
    addAndMakeVisible(labelDelayMix);
    addAndMakeVisible(sliderdelayMix);
}

DelayEditor::~DelayEditor()
{
}

void DelayEditor::paint(Graphics& g)
{
    g.fillAll (Palette::primaryColor);
}

void DelayEditor::resized()
{
    juce::Rectangle<int> area(getLocalBounds());
    
    juce::Rectangle<int> topSection(area.removeFromTop(20));
    toggleDelay.setBounds(topSection.removeFromLeft(22));
    labelTitle.setBounds(topSection.reduced(2));
    
    juce::Rectangle<int> controlsArea(area.reduced(5));
    
    int controlWidth = controlsArea.getWidth() / 4;
    
    juce::Rectangle<int> delayTimeArea(controlsArea.removeFromLeft(controlWidth));
    labelDelayTime.setBounds(delayTimeArea.removeFromTop(15));
    sliderDelayTime.setBounds(delayTimeArea);
    
    juce::Rectangle<int> feedbackArea(controlsArea.removeFromLeft(controlWidth));
    labelDelayFeedback.setBounds(feedbackArea.removeFromTop(15));
    sliderDelayFeedback.setBounds(feedbackArea);
    
    juce::Rectangle<int> mixArea(controlsArea.removeFromLeft(controlWidth));
    labelDelayMix.setBounds(mixArea.removeFromTop(15));
    sliderdelayMix.setBounds(mixArea);
}
