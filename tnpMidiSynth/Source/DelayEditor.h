/*
  ==============================================================================

    DelayEditor.h
    Created: 4 Aug 2018 6:29:27pm
    Author:  Tiago Pestana

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
	
	ToggleButton toggleDelay;

	Label labelTitle;
	Label labelDelayTime;
	Label labelDelayFeedback;
	Label labelDelayMix;

	Slider sliderDelayTime;
	Slider sliderDelayFeedback; 
	Slider sliderdelayMix;

	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> delayToggleAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayTimeAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayFeedbackAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayMixAttachment;

};