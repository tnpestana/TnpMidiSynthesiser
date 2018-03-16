/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiSynthesizerAudioProcessorEditor::MidiSynthesizerAudioProcessorEditor (MidiSynthesizerAudioProcessor& p, 
	MidiKeyboardState& k, AudioDeviceManager& d)
    :	AudioProcessorEditor (&p),
		processor (p),
		keyboardState(k),
		deviceManager(d),
		keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard),
		lastInputIndex(0),
		isAddingFromMidiInput(false)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 200);

	addAndMakeVisible(keyboardComponent);

	// Populate ComboBox with available MIDI devices.
	addAndMakeVisible(midiInputList);
	midiInputList.setTextWhenNoChoicesAvailable("No MIDI inputs enabled.");
	auto midiInputs = MidiInput::getDevices();
	midiInputList.addItemList(midiInputs, 1);
	midiInputList.onChange = [this] {setMidiInput
		(midiInputList.getSelectedItemIndex()); };
	
	// Find the first enabled device and use it by default
	for (auto device : midiInputs)
	{
		if (deviceManager.isMidiInputEnabled(device))
		{
			setMidiInput(midiInputs.indexOf(device));
			break;
		}
	}

	if (midiInputList.getSelectedId() == 0)
	{
		setMidiInput(0);
	}

	addAndMakeVisible(midiInputListLabel);
	midiInputListLabel.setText("MIDI input: ", dontSendNotification);
	midiInputListLabel.setJustificationType(Justification::centredRight);
}

MidiSynthesizerAudioProcessorEditor::~MidiSynthesizerAudioProcessorEditor()
{
}

//==============================================================================
void MidiSynthesizerAudioProcessorEditor::setMidiInput(int index)
{
	auto list = MidiInput::getDevices();
	deviceManager.removeMidiInputCallback(list[lastInputIndex], this);

	auto newInput = list[index];
	if (!deviceManager.isMidiInputEnabled(newInput))
		deviceManager.setMidiInputEnabled(newInput, true);

	deviceManager.addMidiInputCallback(newInput, this);
	midiInputList.setSelectedId(index + 1, dontSendNotification);

	lastInputIndex = index;
}

void MidiSynthesizerAudioProcessorEditor::handleIncomingMidiMessage(MidiInput * source, const MidiMessage & message)
{
	const ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
	keyboardState.processNextMidiEvent(message);
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

