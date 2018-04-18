/*
  ==============================================================================

    OscillatorEditor.h
    Created: 17 Apr 2018 1:57:27pm
    Author:  tnpes

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
	Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
	Label attackLabel, decayLabel, sustainLabel, releaseLabel, numVoicesLabel;
	ComboBox numVoicesInput;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackAttachment, 
																  decayAttachment, 
																  sustainAttachment, 
																  releaseAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorEditor)
};