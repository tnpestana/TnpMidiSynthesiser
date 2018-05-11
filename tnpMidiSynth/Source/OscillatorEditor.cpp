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
	// Title label.
	addAndMakeVisible(titleLabel);
	titleLabel.setText("OSCILLATOR", dontSendNotification);
	titleLabel.setJustificationType(Justification::centred);

	// Number of voices components. 
	addAndMakeVisible(numVoicesLabel);
	numVoicesLabel.setText("number of voices: ", dontSendNotification);
	numVoicesLabel.setJustificationType(Justification::bottomLeft);
	addAndMakeVisible(numVoicesInput);
	for (int i = 1; i < 11; i++)							//	Even though the numVoices parameter's range is defined we
		numVoicesInput.addItem((String)i, i);				// seem to need to populate the combo box anyway.
	numVoicesAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.treeState, "numVoices", numVoicesInput);

	// Oscillator type.
	addAndMakeVisible(oscTypeLabel);
	oscTypeLabel.setText("wave type:", dontSendNotification);
	oscTypeLabel.setJustificationType(Justification::bottomLeft);
	addAndMakeVisible(oscTypeInput);
	oscTypeInput.addItem("sine wave", 1);				//	Even though the oscType parameter's range is defined we
	oscTypeInput.addItem("square wave", 2);				// seem to need to populate the combo box anyway.
	oscTypeInput.addItem("triangle wave", 3);
	oscTypeAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.treeState, "oscType", oscTypeInput);

	// Attack.
	addAndMakeVisible(attackSlider);
	attackSlider.setSliderStyle(Slider::LinearVertical);
	attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(attackLabel);
	attackLabel.setText("attack", dontSendNotification);
	attackLabel.setJustificationType(Justification::centredTop);
	attackAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "attack", attackSlider);

	// Decay.
	addAndMakeVisible(decaySlider);
	decaySlider.setSliderStyle(Slider::LinearVertical);
	decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(decayLabel);
	decayLabel.setText("decay", dontSendNotification);
	decayLabel.setJustificationType(Justification::centredTop);
	decayAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "decay", decaySlider);

	// Sustain.
	addAndMakeVisible(sustainSlider);
	sustainSlider.setSliderStyle(Slider::LinearVertical);
	sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(sustainLabel);
	sustainLabel.setText("sustain", dontSendNotification);
	sustainLabel.setJustificationType(Justification::centredTop);
	sustainAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "sustain", sustainSlider);

	// Release. 
	addAndMakeVisible(releaseSlider);
	releaseSlider.setSliderStyle(Slider::LinearVertical);
	releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(releaseLabel);
	releaseLabel.setText("release", dontSendNotification);
	releaseLabel.setJustificationType(Justification::centredTop);
	releaseAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "release", releaseSlider);

	// Gain.
	addAndMakeVisible(gainSlider);
	gainSlider.setSliderStyle(Slider::LinearVertical);
	gainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(gainLabel);
	gainLabel.setText("gain", dontSendNotification);
	gainLabel.setJustificationType(Justification::centredTop);
	gainAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "gain", gainSlider);

	// IIR Filter.
	addAndMakeVisible(filterTypeInput);
	filterTypeInput.addItem("lo-pass", 1);
	filterTypeInput.addItem("hi-pass", 2);
	filterTypeInput.addItem("band-pass", 3);
	addAndMakeVisible(filterCutoffSlider);
	filterCutoffSlider.setSliderStyle(Slider::LinearHorizontal);
	filterCutoffSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(filterTypeLabel);
	filterTypeLabel.setText("filter type:", dontSendNotification);
	filterTypeLabel.setJustificationType(Justification::bottomLeft);
	addAndMakeVisible(filterCutoffLabel);
	filterCutoffLabel.setText("filter cutoff:", dontSendNotification);
	filterCutoffLabel.setJustificationType(Justification::bottomLeft);
	filterCutoffAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.treeState, "filterCutoff", filterCutoffSlider);
	filterTypeAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.treeState, "filterType", filterTypeInput);
}

OscillatorEditor::~OscillatorEditor()
{
}

void OscillatorEditor::paint(Graphics& g)
{
	g.fillAll(Colours::lightsalmon);
	
	getLookAndFeel().setColour(ComboBox::backgroundColourId, Colours::lightsalmon);
	getLookAndFeel().setColour(ComboBox::outlineColourId, Colours::lightsalmon);
	getLookAndFeel().setColour(Label::backgroundColourId, Colours::lightsalmon);
	getLookAndFeel().setColour(PopupMenu::ColourIds::backgroundColourId, Colours::darksalmon);
	getLookAndFeel().setColour(Slider::ColourIds::trackColourId, Colours::lightpink);
	getLookAndFeel().setColour(Slider::ColourIds::thumbColourId, Colours::coral);
	getLookAndFeel().setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::lightpink);

	titleLabel.setColour(Label::backgroundColourId, Colours::darksalmon);
}

void OscillatorEditor::resized()
{
	// Total oscillator area.
	juce::Rectangle<int> oscArea(getLocalBounds());
	titleLabel.setBounds(oscArea.removeFromTop(20).reduced(2));

	// Gain controls area. 
	juce::Rectangle<int> gainLocation(oscArea.removeFromRight(oscArea.getWidth() * 0.2).reduced(2));
	gainLabel.setBounds(gainLocation.removeFromBottom(25));
	gainSlider.setBounds(gainLocation);

	// Wave type controls area.
	juce::Rectangle<int> controls(oscArea.removeFromTop(oscArea.getHeight() * 0.2).reduced(2));

	// Number of voices selection area.
	juce::Rectangle<int> numVoicesArea(controls.removeFromLeft(100));
	numVoicesLabel.setBounds(numVoicesArea.removeFromTop(20));
	numVoicesInput.setBounds(numVoicesArea);
	
	// Oscillator Type.
	juce::Rectangle<int> oscTypeArea(controls);
	oscTypeLabel.setBounds(oscTypeArea.removeFromTop(20));
	oscTypeInput.setBounds(oscTypeArea);

	// Envelope sliders and labels area - needs reviewing.
	juce::Rectangle<int> oscEnvelope(oscArea.removeFromTop(oscArea.getHeight() * 0.75).reduced(5));

	juce::Rectangle<int> oscEnvelopeSlider(oscEnvelope.removeFromTop(oscEnvelope.getHeight() * 0.9));
	const double sliderWidth = oscEnvelopeSlider.getWidth() / 4;
	attackSlider.setBounds(oscEnvelopeSlider.removeFromLeft(sliderWidth));
	decaySlider.setBounds(oscEnvelopeSlider.removeFromLeft(sliderWidth));
	sustainSlider.setBounds(oscEnvelopeSlider.removeFromLeft(sliderWidth));
	releaseSlider.setBounds(oscEnvelopeSlider.removeFromLeft(sliderWidth));

	juce::Rectangle<int> oscEnvelopeLabel(oscEnvelope);
	attackLabel.setBounds(oscEnvelopeLabel.removeFromLeft(sliderWidth));
	decayLabel.setBounds(oscEnvelopeLabel.removeFromLeft(sliderWidth));
	sustainLabel.setBounds(oscEnvelopeLabel.removeFromLeft(sliderWidth));
	releaseLabel.setBounds(oscEnvelopeLabel.removeFromLeft(sliderWidth));

	// IIR Filter components area.
	juce::Rectangle<int> oscFilter(oscArea.reduced(2));

	juce::Rectangle<int> oscFilterType(oscFilter.removeFromLeft(100));
	filterTypeLabel.setBounds(oscFilterType.removeFromTop(20));
	filterTypeInput.setBounds(oscFilterType);

	juce::Rectangle<int> oscFilterCutoff(oscFilter);
	filterCutoffLabel.setBounds(oscFilterCutoff.removeFromTop(20));
	filterCutoffSlider.setBounds(oscFilterCutoff);
}