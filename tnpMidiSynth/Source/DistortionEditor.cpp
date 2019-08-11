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
    attToggle (std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
        (treeState, "distortionToggle", toggleDistortion))
{
    labelTitle.setText("Distortion", dontSendNotification);

    labelTitle.setJustificationType(Justification::centred);

    //  Populate combo boxes with strings stored as parameter choices
    if (auto* choiceParameter = dynamic_cast<AudioParameterChoice*>(treeState.getParameter("distortionType")))
    {
        comboDistortionType.addItemList(choiceParameter->choices, 1);
        comboDistortionType.setSelectedId(choiceParameter->getIndex() + 1);
    }

    addAndMakeVisible(toggleDistortion);
    addAndMakeVisible(labelTitle);
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
}

void DistortionEditor::resized()
{
    const int labelHeight = 15;
    juce::Rectangle<int> area(getLocalBounds());

    juce::Rectangle<int> topSection(area.removeFromTop(20));
    toggleDistortion.setBounds(topSection.removeFromLeft(22));
    labelTitle.setBounds(topSection.reduced(2));

    labelDistortionType.setBounds(area.removeFromTop(labelHeight));
    comboDistortionType.setBounds(area.removeFromTop(50));
}
