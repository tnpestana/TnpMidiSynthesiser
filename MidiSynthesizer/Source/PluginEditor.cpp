/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiSynthesizerAudioProcessorEditor::MidiSynthesizerAudioProcessorEditor (MidiSynthesizerAudioProcessor& p, MidiKeyboardState& k)
    :	AudioProcessorEditor (&p),
		processor (p),
		keyboardComponent(k, MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 200);

	addAndMakeVisible(keyboardComponent);

	addAndMakeVisible(midiInputList);
	midiInputList.setTextWhenNoChoicesAvailable("No MIDI inputs enabled.");
	auto midiInputs = MidiInput::getDevices();
	midiInputList.addItemList(midiInputs, 1);

	addAndMakeVisible(midiInputListLabel);
	midiInputListLabel.setText("MIDI input: ", dontSendNotification);
	midiInputListLabel.setJustificationType(Justification::centredRight);
}

MidiSynthesizerAudioProcessorEditor::~MidiSynthesizerAudioProcessorEditor()
{
}

//==============================================================================
void MidiSynthesizerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void MidiSynthesizerAudioProcessorEditor::resized()
{
	Rectangle<int> area = getLocalBounds();

	Rectangle<int> inputSelection = area.removeFromTop(30);

	midiInputListLabel.setBounds(inputSelection.removeFromLeft(100));
	midiInputList.setBounds(inputSelection.removeFromLeft(300));

	keyboardComponent.setBounds(area.removeFromTop(170));
}
