/*
  ==============================================================================

    DelayEditor.h
    Created: 4 Aug 2018 6:29:27pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Processors/PluginProcessor.h"

class DelayEditor : public Component
{
public:
	DelayEditor(TnpMidiSynthAudioProcessor&);
	~DelayEditor();

private:
	void paint(Graphics&) override;
	void resized() override;
	
	TnpMidiSynthAudioProcessor& processor;
	AudioProcessorValueTreeState& treeState;

	ToggleButton toggleDelay;

	Label labelTitle;
	Label labelDelayTime;
	Label labelDelayFeedback;
	Label labelDelayMix;

	Slider sliderDelayTime;
	Slider sliderDelayFeedback; 
	Slider sliderdelayMix;

	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> attToggle;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attDelayTime;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attFeedback;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attMix;
};
