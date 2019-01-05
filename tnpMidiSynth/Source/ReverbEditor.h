/*
  ==============================================================================

    ReverbEditor.h
    Created: 17 Apr 2018 5:19:12pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class ReverbEditor : public Component
{
public:
	ReverbEditor(TnpMidiSynthAudioProcessor&);
	~ReverbEditor();

private:
	void paint(Graphics&) override;
	void resized() override;

	TnpMidiSynthAudioProcessor& processor;
	AudioProcessorValueTreeState& treeState;

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

	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> attToggle;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attMix;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attRoomSize;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attDamping;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attWidth;
};
