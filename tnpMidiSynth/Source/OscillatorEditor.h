/*
  ==============================================================================

    OscillatorEditor.h
    Created: 17 Apr 2018 1:57:27pm
    Author:  tnpes

	Main application is suposed to run more than one oscillator, so here is a
	template for its GUI added to the main editor as many times as needed.

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class OscillatorEditor : public Component
{
public:
	OscillatorEditor(TnpMidiSynthAudioProcessor&, AudioProcessorValueTreeState&);
	~OscillatorEditor();

	void paint(Graphics&) override;
	void resized() override;

private:
	Slider attackSlider;
	Slider decaySlider; 
	Slider sustainSlider;
	Slider releaseSlider; 
	Slider gainSlider;
	Slider filterCutoffSlider;
	Slider transposeSlider;

	Label attackLabel;
	Label decayLabel;
	Label sustainLabel;
	Label releaseLabel; 
	Label numVoicesLabel; 
	Label gainLabel;
	Label oscTypeLabel;
	Label filterTypeLabel;
	Label filterCutoffLabel;
	Label titleLabel;
	Label transposeLabel;

	ComboBox numVoicesInput;
	ComboBox oscTypeInput;
	ComboBox filterTypeInput;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> transposeAttachment;

	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> numVoicesAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> oscTypeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorEditor)
};