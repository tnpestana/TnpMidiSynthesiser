/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewSynthesiserAudioProcessorEditor::NewSynthesiserAudioProcessorEditor (NewSynthesiserAudioProcessor& p, MidiKeyboardState& k)
    : AudioProcessorEditor (&p), processor (p), keyboardState(k), keyboardComponent(k, MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 200);

	addAndMakeVisible(label);

	addAndMakeVisible(keyboardComponent);

	label.setText("no call", dontSendNotification);
	label.setJustificationType(Justification::centred);

	keyboardState.addListener(this);
}

NewSynthesiserAudioProcessorEditor::~NewSynthesiserAudioProcessorEditor()
{
}

//==============================================================================
void NewSynthesiserAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void NewSynthesiserAudioProcessorEditor::resized()
{
	Rectangle<int> area = getLocalBounds();
	keyboardComponent.setBounds(area.removeFromTop(150));
	label.setBounds(area.removeFromTop(50));
}

//==============================================================================
void NewSynthesiserAudioProcessorEditor::handleNoteOn(MidiKeyboardState * source, int midiChannel, int midiNoteNumber, float velocity)
{
	label.setText((String)MidiMessage::getMidiNoteInHertz(midiNoteNumber), dontSendNotification);
}

void NewSynthesiserAudioProcessorEditor::handleNoteOff(MidiKeyboardState * source, int midiChannel, int midiNoteNumber, float velocity)
{
}

