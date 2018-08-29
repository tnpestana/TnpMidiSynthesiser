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

	ToggleButton toggleReverb;

	Label labelTitle;
	Label labelMix;
	Label roomSizeLabel;
	Label dampingLabel;
	Label widthLabel;

	Slider mixSlider;
	Slider roomSizeSlider;
	Slider dampingSlider;
	Slider widthSlider;

	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> toggleAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> widthAttachment;

	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	TnpMidiSynthAudioProcessor& processor;
};
