/*
  ==============================================================================

    LFOEditor.h
    Created: 30 Aug 2018 6:26:46pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class LFOEditor : public Component
{
public:
	LFOEditor(TnpMidiSynthAudioProcessor&, AudioProcessorValueTreeState&);
	~LFOEditor();

private:
	void paint(Graphics&) override;
	void resized() override;

	ToggleButton toggleLfo;

	Label labelTitle;
	Label labelLfoDepth;
	Label labelLfoRate;

	Slider sliderLfoDepth;
	Slider sliderLfoRate;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> depthAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> rateAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> toggleAttachment;
};