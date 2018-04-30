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
	OscillatorEditor(TnpMidiSynthAudioProcessor&);
	~OscillatorEditor();

	void paint(Graphics&) override;
	void resized() override;

private:
	Slider attackSlider, decaySlider, sustainSlider, 
		   releaseSlider, gainSlider, filterFreqSlider;

	Label attackLabel, decayLabel, sustainLabel, 
		  releaseLabel, numVoicesLabel, gainLabel, 
		  oscTypeLabel, filterTypeLabel, filterCutoffLabel;

	ComboBox numVoicesInput, oscTypeInput, filterTypeInput;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackAttachment, decayAttachment, sustainAttachment, 
																  releaseAttachment, gainAttachment, filterFreqAttachment;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> oscTypeAttachment, filterTypeAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorEditor)
};