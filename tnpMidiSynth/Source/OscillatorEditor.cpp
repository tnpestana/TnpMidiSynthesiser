/*
  ==============================================================================

    OscillatorEditor.cpp
    Created: 17 Apr 2018 1:57:27pm
    Author:  tnpes

	Main application is suposed to run more than one oscillator, so here is a
	template for its GUI added to the main editor as many times as needed.

  ==============================================================================
*/

#include "OscillatorEditor.h"

OscillatorEditor::OscillatorEditor(TnpMidiSynthAudioProcessor& p)
{
	// Attack.
	addAndMakeVisible(attackSlider);
	attackSlider.setSliderStyle(Slider::LinearVertical);
	attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(attackLabel);
	attackLabel.setText("attack", dontSendNotification);
	attackLabel.setJustificationType(Justification::centred);
	attackAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "attack", attackSlider);

	// Decay.
	addAndMakeVisible(decaySlider);
	decaySlider.setSliderStyle(Slider::LinearVertical);
	decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(decayLabel);
	decayLabel.setText("decay", dontSendNotification);
	decayLabel.setJustificationType(Justification::centred);
	decayAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "decay", decaySlider);

	// Sustain.
	addAndMakeVisible(sustainSlider);
	sustainSlider.setSliderStyle(Slider::LinearVertical);
	sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(sustainLabel);
	sustainLabel.setText("sustain", dontSendNotification);
	sustainLabel.setJustificationType(Justification::centred);
	sustainAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "sustain", sustainSlider);

	// Release. 
	addAndMakeVisible(releaseSlider);
	releaseSlider.setSliderStyle(Slider::LinearVertical);
	releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(releaseLabel);
	releaseLabel.setText("release", dontSendNotification);
	releaseLabel.setJustificationType(Justification::centred);
	releaseAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "release", releaseSlider);

	// Gain.
	addAndMakeVisible(gainSlider);
	gainSlider.setSliderStyle(Slider::LinearVertical);
	gainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(gainLabel);
	gainLabel.setText("gain", dontSendNotification);
	gainLabel.setJustificationType(Justification::centred);
	gainAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "gain", gainSlider);

	// IIR Filter.
	addAndMakeVisible(filterTypeInput);
	filterTypeInput.addItem("lo-pass", 1);
	filterTypeInput.addItem("hi-pass", 2);
	addAndMakeVisible(filterCutoffSlider);
	filterCutoffSlider.setSliderStyle(Slider::LinearHorizontal);
	filterCutoffSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(filterTypeLabel);
	filterTypeLabel.setText("filter type:", dontSendNotification);
	filterTypeLabel.setJustificationType(Justification::centredLeft);
	addAndMakeVisible(filterCutoffLabel);
	filterCutoffLabel.setText("filter cutoff:", dontSendNotification);
	filterCutoffLabel.setJustificationType(Justification::centredLeft);
	filterCutoffAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "filterCutoff", filterCutoffSlider);
	filterTypeAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.treeState, "filterType", filterTypeInput);

	// Oscillator type.
	addAndMakeVisible(oscTypeLabel);
	oscTypeLabel.setText("oscillator type:", dontSendNotification);
	oscTypeLabel.setJustificationType(Justification::centredLeft);
	addAndMakeVisible(oscTypeInput);
	oscTypeInput.addItem("sine wave", 1);				//	Even though the oscType parameter's range is defined we
	oscTypeInput.addItem("square wave", 2);			    // seem to need to populate the combo box anyway.
	oscTypeAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.treeState, "oscType", oscTypeInput);
}

OscillatorEditor::~OscillatorEditor()
{
}

void OscillatorEditor::paint(Graphics& g)
{
	g.fillAll(Colours::sandybrown);
}

void OscillatorEditor::resized()
{
	const int sliderWidth = getWidth() / 5;						// 5 sliders total.
	const int sliderHeight = getHeight() - 20 - 40 - 40;		// 20 - label size; 40 - control section size; 35 - fliter slider.

	const int labelWidth = sliderWidth;					
	const int labelHeight = 20;

	// Total oscillator area.
	juce::Rectangle<int> area(getLocalBounds());

	// Area for gain slider and its label. 
	juce::Rectangle<int> gainLocation(area.removeFromRight(sliderWidth));
	gainSlider.setBounds(gainLocation.removeFromTop(gainLocation.getHeight() - 20));
	gainLabel.setBounds(gainLocation.removeFromTop(20));

	// Area for wave type controls.
	juce::Rectangle<int> controls(area.removeFromTop(40));
	juce::Rectangle<int> oscTypeArea(controls.removeFromLeft(130));
	oscTypeLabel.setBounds(oscTypeArea.removeFromTop(20));
	oscTypeInput.setBounds(oscTypeArea.removeFromTop(20));

	// Area for envelope sliders and labels - needs reviewing.
	juce::Rectangle<int> envelopeSliders(area.removeFromTop(sliderHeight));
	juce::Rectangle<int> labels(area.removeFromTop(labelHeight));

	attackSlider.setBounds(envelopeSliders.removeFromLeft(sliderWidth));
	attackLabel.setBounds(labels.removeFromLeft(labelWidth));

	decaySlider.setBounds(envelopeSliders.removeFromLeft(sliderWidth));
	decayLabel.setBounds(labels.removeFromLeft(labelWidth));

	sustainSlider.setBounds(envelopeSliders.removeFromLeft(sliderWidth));
	sustainLabel.setBounds(labels.removeFromLeft(labelWidth));

	releaseSlider.setBounds(envelopeSliders.removeFromLeft(sliderWidth));
	releaseLabel.setBounds(labels.removeFromLeft(labelWidth));

	// Area for IIR Filter components.
	juce::Rectangle<int> filterLabels(area.removeFromTop(20));
	filterTypeLabel.setBounds(filterLabels.removeFromLeft(100));
	filterCutoffLabel.setBounds(filterLabels.removeFromLeft(getWidth()));
	juce::Rectangle<int> filterComponents(area.removeFromTop(20));
	filterTypeInput.setBounds(filterComponents.removeFromLeft(100));
	filterCutoffSlider.setBounds(filterComponents.removeFromLeft(getWidth()));
}