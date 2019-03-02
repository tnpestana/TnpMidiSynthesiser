/*
  ==============================================================================

    OscillatorEditor.cpp
    Created: 17 Apr 2018 1:57:27pm
    Author:  Tiago Pestana

	Main application is suposed to run more than one oscillator, so here is a
	template for its GUI added to the main editor as many times as needed.

  ==============================================================================
*/

#include "OscillatorEditor.h"

OscillatorEditor::OscillatorEditor(TnpMidiSynthAudioProcessor& p)
	//  Processor references
	: processor (p),
	treeState (p.getTreeState()),
	//  Parameter attachments
	
	attTranspose (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "osc1Transpose", transposeSlider)),
	attOscType (std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
		(treeState, "osc1Type", oscTypeInput)),
	attAttack (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "osc1Attack", attackSlider)),
	attDecay (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "osc1Decay", decaySlider)),
	attSustain (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "osc1Sustain", sustainSlider)),
	attRelease (std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(treeState, "osc1Release", releaseSlider))
{
	titleLabel.setText("OSCILLATOR", dontSendNotification);
	transposeLabel.setText("transpose: ", dontSendNotification);
	oscTypeLabel.setText("wave type:", dontSendNotification);
	attackLabel.setText("attack", dontSendNotification);
	decayLabel.setText("decay", dontSendNotification);
	sustainLabel.setText("sustain", dontSendNotification);
	releaseLabel.setText("release", dontSendNotification);

	titleLabel.setJustificationType(Justification::centred);
	transposeLabel.setJustificationType(Justification::bottomLeft);
	oscTypeLabel.setJustificationType(Justification::bottomLeft);
	attackLabel.setJustificationType(Justification::centredBottom);
	decayLabel.setJustificationType(Justification::centredBottom);
	sustainLabel.setJustificationType(Justification::centredBottom);
	releaseLabel.setJustificationType(Justification::centredBottom);

	transposeSlider.setSliderStyle(Slider::LinearHorizontal);
	attackSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	decaySlider.setSliderStyle(Slider::RotaryVerticalDrag);
	sustainSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	releaseSlider.setSliderStyle(Slider::RotaryVerticalDrag);

	transposeSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 40, 15);
	attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);
	releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 15);

	//  Populate combo boxes with strings stored as parameter choices
	if (auto* choiceParameter = dynamic_cast<AudioParameterChoice*>(treeState.getParameter("osc1Type")))
	{
		oscTypeInput.addItemList(choiceParameter->choices, 1);
		oscTypeInput.setSelectedId(choiceParameter->getIndex() + 1);
	}

	addAndMakeVisible(titleLabel);
	addAndMakeVisible(transposeLabel);
	addAndMakeVisible(transposeSlider);
	addAndMakeVisible(oscTypeLabel);
	addAndMakeVisible(oscTypeInput);
	addAndMakeVisible(attackLabel);
	addAndMakeVisible(attackSlider);
	addAndMakeVisible(decayLabel);
	addAndMakeVisible(decaySlider);
	addAndMakeVisible(sustainLabel);
	addAndMakeVisible(sustainSlider);
	addAndMakeVisible(releaseLabel);
	addAndMakeVisible(releaseSlider);
}

OscillatorEditor::~OscillatorEditor()
{
}

void OscillatorEditor::paint(Graphics& g)
{
	titleLabel.setColour(Label::backgroundColourId, Colours::lightgrey);
	titleLabel.setColour(Label::outlineColourId, Colours::black);
	transposeSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	attackSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	decaySlider.setColour(Slider::textBoxTextColourId, Colours::black);
	sustainSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	releaseSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	oscTypeInput.setColour(ComboBox::textColourId, Colours::black);
}

void OscillatorEditor::resized()
{
	//  Total oscillator area.
	juce::Rectangle<int> oscArea(getLocalBounds());
	titleLabel.setBounds(oscArea.removeFromTop(20).reduced(2));

	//  Controls area.
	juce::Rectangle<int> controls(oscArea.removeFromTop(oscArea.getHeight() * 0.30).reduced(2));
	
	//  Oscillator Type.
	juce::Rectangle<int> oscTypeArea(controls.removeFromLeft(100));
	oscTypeLabel.setBounds(oscTypeArea.removeFromTop(20));
	oscTypeInput.setBounds(oscTypeArea.reduced(2));

	//  Transpose selection area.
	juce::Rectangle<int> transposeArea(controls);
	transposeLabel.setBounds(transposeArea.removeFromTop(20));
	transposeSlider.setBounds(transposeArea);

	//  Envelope sliders and labels area - needs reviewing.
	juce::Rectangle<int> oscEnvelope(oscArea.reduced(10));
	const double sliderWidth = oscEnvelope.getWidth() / 4;

	juce::Rectangle<int> oscEnvelopeLabel(oscEnvelope.removeFromTop(20));
	attackLabel.setBounds(oscEnvelopeLabel.removeFromLeft(sliderWidth));
	decayLabel.setBounds(oscEnvelopeLabel.removeFromLeft(sliderWidth));
	sustainLabel.setBounds(oscEnvelopeLabel.removeFromLeft(sliderWidth));
	releaseLabel.setBounds(oscEnvelopeLabel.removeFromLeft(sliderWidth));

	juce::Rectangle<int> oscEnvelopeSlider(oscEnvelope);
	attackSlider.setBounds(oscEnvelopeSlider.removeFromLeft(sliderWidth));
	decaySlider.setBounds(oscEnvelopeSlider.removeFromLeft(sliderWidth));
	sustainSlider.setBounds(oscEnvelopeSlider.removeFromLeft(sliderWidth));
	releaseSlider.setBounds(oscEnvelopeSlider.removeFromLeft(sliderWidth));
}