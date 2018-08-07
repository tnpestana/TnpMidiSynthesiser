/*
  ==============================================================================

    FilterEditor.h
    Created: 7 Aug 2018 6:24:53pm
    Author:  tnpes

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

	Label titleLabel;
	Label filterTypeLabel;
	Label filterCutoffLabel;
	Label filterQLabel;

	Slider filterCutoffSlider;
	Slider filterQSlider;

	ComboBox filterTypeInput;

	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterQAttachment;

	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	TnpMidiSynthAudioProcessor& processor;
};