/*
  ==============================================================================

    OscillatorEditor.h
    Created: 17 Apr 2018 1:57:27pm
    Author:  Tiago Pestana

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
	TnpMidiSynthAudioProcessor& processor;
	AudioProcessorValueTreeState& treeState;

	Slider attackSlider;
	Slider decaySlider; 
	Slider sustainSlider;
	Slider releaseSlider; 
	
	Slider transposeSlider;

	Label attackLabel;
	Label decayLabel;
	Label sustainLabel;
	Label releaseLabel; 
	Label numVoicesLabel; 
	Label oscTypeLabel;
	Label titleLabel;
	Label transposeLabel;

	ComboBox numVoicesInput;
	ComboBox oscTypeInput;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attAttack;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attDecay;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attSustain;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attRelease;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attTranspose;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> attNumVoices;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> attOscType;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorEditor)
};