/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiSynthesizerAudioProcessorEditor::MidiSynthesizerAudioProcessorEditor (MidiSynthesizerAudioProcessor& p, AudioDeviceManager& d)
    :	AudioProcessorEditor (&p),
		processor (p),
		deviceManager(d),
		lastInputIndex(0),
		isAddingFromMidiInput(false)
{
    setSize (400, 200);


	// Populate ComboBox with available MIDI devices.
	addAndMakeVisible(midiInputList);
	midiInputList.setTextWhenNoChoicesAvailable("No MIDI inputs enabled.");
	updateMidiInputList();

	addAndMakeVisible(refreshListButton);
	refreshListButton.setButtonText("refresh");
	refreshListButton.addListener(this);
	

	// midi input label
	addAndMakeVisible(midiInputListLabel);
	midiInputListLabel.setText("MIDI input: ", dontSendNotification);
	midiInputListLabel.setJustificationType(Justification::centredRight);

	// midi note label
	addAndMakeVisible(midiNoteLabel);
	midiNoteLabel.setText("no call", dontSendNotification);
	midiNoteLabel.setJustificationType(Justification::centred);
}

MidiSynthesizerAudioProcessorEditor::~MidiSynthesizerAudioProcessorEditor()
{
}

//==============================================================================
void MidiSynthesizerAudioProcessorEditor::buttonClicked(Button* button)
{
	if (button == &refreshListButton) updateMidiInputList();
}

void MidiSynthesizerAudioProcessorEditor::updateMidiInputList()
{
	auto midiInputs = MidiInput::getDevices();
	midiInputList.clear();
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
}

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

//==============================================================================
void MidiSynthesizerAudioProcessorEditor::handleIncomingMidiMessage(MidiInput * source, const MidiMessage & message)
{
}

//==============================================================================
void MidiSynthesizerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MidiSynthesizerAudioProcessorEditor::resized()
{
	Rectangle<int> area = getLocalBounds();

	Rectangle<int> inputSelection = area.removeFromTop(30);
	midiInputListLabel.setBounds(inputSelection.removeFromLeft(80));
	midiInputList.setBounds(inputSelection.removeFromLeft(250));
	refreshListButton.setBounds(inputSelection.removeFromLeft(70));

	midiNoteLabel.setBounds(area.removeFromTop(70));
}

