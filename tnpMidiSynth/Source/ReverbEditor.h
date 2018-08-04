/*
  ==============================================================================

    ReverbEditor.h
    Created: 17 Apr 2018 5:19:12pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class ReverbEditor : public Component
{
public:
	ReverbEditor(TnpMidiSynthAudioProcessor&, AudioProcessorValueTreeState&);
	~ReverbEditor();

private:
	void paint(Graphics&) override;
	void resized() override;

	Label titleLabel;
	Label mixLabel;
	Label roomSizeLabel;
	Label dampingLabel;

	Slider mixSlider;
	Slider roomSizeSlider;
	Slider dampingSlider;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;

	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	TnpMidiSynthAudioProcessor& processor;
};
