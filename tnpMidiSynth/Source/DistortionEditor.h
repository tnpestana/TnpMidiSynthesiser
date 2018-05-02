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
	DistortionEditor(TnpMidiSynthAudioProcessor&);
	~DistortionEditor();

private:
	void paint(Graphics&) override;
	void resized() override;

	Slider driveSlider, rangeSlider, mixSlider;
	
	Label driveLabel, rangeLabel, mixLabel;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
};