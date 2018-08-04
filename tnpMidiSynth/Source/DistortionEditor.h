/*
  ==============================================================================

    DistortionEditor.h
    Created: 1 May 2018 8:47:46pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class DistortionEditor : public Component
{
public:
	DistortionEditor(TnpMidiSynthAudioProcessor&, AudioProcessorValueTreeState&);
	~DistortionEditor();

private:
	void paint(Graphics&) override;
	void resized() override;

	Label titleLabel;
	Label driveLabel;
	Label rangeLabel;
	Label mixLabel;

	Slider driveSlider;
	Slider rangeSlider; 
	Slider mixSlider;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
};