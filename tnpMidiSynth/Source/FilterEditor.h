/*
  ==============================================================================

    FilterEditor.h
    Created: 7 Aug 2018 6:24:53pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class FilterEditor : public Component
{
public:
	FilterEditor(TnpMidiSynthAudioProcessor&, AudioProcessorValueTreeState&);
	~FilterEditor();

private:
	void paint(Graphics&) override;
	void resized() override;

	ToggleButton toggleFilter;

	Label labelFilterTitle;
	Label labelFilterType;
	Label labelFilterCutoff;
	Label labelFilterQ;
	Label labelFilterGainFactor;

	ComboBox comboFilterType;
	Slider sliderFilterCutoff;
	Slider sliderFilterQ;
	Slider sliderFilterGainFactor;

	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> filterToggleAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterQAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterGainFactorAttachment;

	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	TnpMidiSynthAudioProcessor& processor;
};