/*
  ==============================================================================

    DelayEditor.h
    Created: 4 Aug 2018 6:29:27pm
    Author:  tnpes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class DelayEditor : public Component
{
public:
	DelayEditor(TnpMidiSynthAudioProcessor&, AudioProcessorValueTreeState&);
	~DelayEditor();

private:
	void paint(Graphics&) override;
	void resized() override;

	Slider delayTimeSlider, delayFeedbackSlider, delayWetSlider;

	Label titleLabel, delayTimeLabel, delayFeedbackLabel,
		delayWetLabel;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayTimeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayFeedbackAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayWetAttachment;
};