/*
  ==============================================================================

    OscillatorEditor.cpp
    Created: 17 Apr 2018 1:57:27pm
    Author:  tnpes

  ==============================================================================
*/

#include "OscillatorEditor.h"

OscillatorEditor::OscillatorEditor(TnpMidiSynthAudioProcessor& p)
{
	// attack
	addAndMakeVisible(attackSlider);
	attackSlider.setSliderStyle(Slider::LinearVertical);
	attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(attackLabel);
	attackLabel.setText("attack", dontSendNotification);
	attackLabel.setJustificationType(Justification::centred);
	attackAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "attack", attackSlider);

	// decay
	addAndMakeVisible(decaySlider);
	decaySlider.setSliderStyle(Slider::LinearVertical);
	decaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(decayLabel);
	decayLabel.setText("decay", dontSendNotification);
	decayLabel.setJustificationType(Justification::centred);
	decayAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "decay", decaySlider);

	// sustain slider
	addAndMakeVisible(sustainSlider);
	sustainSlider.setSliderStyle(Slider::LinearVertical);
	sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(sustainLabel);
	sustainLabel.setText("sustain", dontSendNotification);
	sustainLabel.setJustificationType(Justification::centred);
	sustainAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "sustain", sustainSlider);

	// release 
	addAndMakeVisible(releaseSlider);
	releaseSlider.setSliderStyle(Slider::LinearVertical);
	releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(releaseLabel);
	releaseLabel.setText("release", dontSendNotification);
	releaseLabel.setJustificationType(Justification::centred);
	releaseAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "release", releaseSlider);

	// gain
	addAndMakeVisible(gainSlider);
	gainSlider.setSliderStyle(Slider::LinearVertical);
	gainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(gainLabel);
	gainLabel.setText("gain", dontSendNotification);
	gainLabel.setJustificationType(Justification::centred);
	gainAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "gain", gainSlider);
}

OscillatorEditor::~OscillatorEditor()
{
}

void OscillatorEditor::paint(Graphics& g)
{
	g.fillAll(Colours::grey);
}

void OscillatorEditor::resized()
{
	const int sliderWidth = getWidth() / 5;
	const int labelWidth = sliderWidth;

	const int labelHeight = 20;
	const int sliderHeight = getHeight() - 20 - 40;

	juce::Rectangle<int> area(getLocalBounds());

	juce::Rectangle<int> gainLocation(area.removeFromRight(sliderWidth));
	gainSlider.setBounds(gainLocation.removeFromTop(gainLocation.getHeight() - 20));
	gainLabel.setBounds(gainLocation.removeFromTop(20));


	juce::Rectangle<int> controls(area.removeFromTop(40));
	juce::Rectangle<int> sliders(area.removeFromTop(sliderHeight));
	juce::Rectangle<int> labels(area.removeFromTop(labelHeight));

	attackSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	attackLabel.setBounds(labels.removeFromLeft(labelWidth));

	decaySlider.setBounds(sliders.removeFromLeft(sliderWidth));
	decayLabel.setBounds(labels.removeFromLeft(labelWidth));

	sustainSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	sustainLabel.setBounds(labels.removeFromLeft(labelWidth));

	releaseSlider.setBounds(sliders.removeFromLeft(sliderWidth));
	releaseLabel.setBounds(labels.removeFromLeft(labelWidth));

}