/*
  ==============================================================================

    LFOEditor.h
    Created: 30 Aug 2018 6:26:46pm
    Author:  Tiago Pestana

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

	ComboBox comboOscType;

	Label labelTitle;
	Label labelLfoOscType;
	Label labelLfoDepth;
	Label labelLfoRate;

	Slider sliderLfoDepth;
	Slider sliderLfoRate;

	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> oscTypeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> depthAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> rateAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> toggleAttachment;
};