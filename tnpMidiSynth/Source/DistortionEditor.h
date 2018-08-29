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

	ToggleButton toggleDistortion;

	Label labelTitle;
	Label labelDrive;
	Label labelRange;
	Label labelMix;

	Slider sliderDrive;
	Slider sliderRange; 
	Slider sliderMix;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> toggleAttachment;
};