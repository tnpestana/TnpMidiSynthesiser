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

OscillatorEditor::OscillatorEditor(TnpMidiSynthAudioProcessor& p, int osc)
	//  Processor references
	: processor (p),
	treeState (p.getTreeState()),
	osc(osc)
{
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

	transposeSlider.setTextValueSuffix(" st");
	attackSlider.setTextValueSuffix(" ms");
	decaySlider.setTextValueSuffix(" ms");
	sustainSlider.setTextValueSuffix(" %");
	releaseSlider.setTextValueSuffix(" ms");

	transposeSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 50, 15);
	attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
	decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
	sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);
	releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 15);

	//  Parameter attachments
	if (osc == 1)
	{
		titleLabel.setText("OSCILLATOR 1", dontSendNotification);
		attTranspose = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
			(treeState, "osc1Transpose", transposeSlider);
		attOscType = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
			(treeState, "osc1Type", oscTypeInput);
		attAttack = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
			(treeState, "osc1Attack", attackSlider);
		attDecay = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
			(treeState, "osc1Decay", decaySlider);
		attSustain = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
			(treeState, "osc1Sustain", sustainSlider);
		attRelease = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
				(treeState, "osc1Release", releaseSlider);

		//  Populate combo boxes with strings stored as parameter choices
		if (auto* choiceParameter = dynamic_cast<AudioParameterChoice*>(treeState.getParameter("osc1Type")))
		{
			oscTypeInput.addItemList(choiceParameter->choices, 1);
			oscTypeInput.setSelectedId(choiceParameter->getIndex() + 1);
		}
	}
	else if (osc == 2)
	{
		titleLabel.setText("OSCILLATOR 2", dontSendNotification);
		attTranspose = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
			(treeState, "osc2Transpose", transposeSlider);
		attOscType = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
			(treeState, "osc2Type", oscTypeInput);
		attAttack = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
			(treeState, "osc2Attack", attackSlider);
		attDecay = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
			(treeState, "osc2Decay", decaySlider);
		attSustain = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
			(treeState, "osc2Sustain", sustainSlider);
		attRelease = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
			(treeState, "osc2Release", releaseSlider);
		attOsc2Toggle = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
			(treeState, "osc2Toggle", toggle);

		//  Populate combo boxes with strings stored as parameter choices
		if (auto* choiceParameter = dynamic_cast<AudioParameterChoice*>(treeState.getParameter("osc2Type")))
		{
			oscTypeInput.addItemList(choiceParameter->choices, 1);
			oscTypeInput.setSelectedId(choiceParameter->getIndex() + 1);
		}

		addAndMakeVisible(toggle);
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

	juce::Rectangle<int> topSection(oscArea.removeFromTop(20));
	if (osc == 2)
		toggle.setBounds(topSection.removeFromLeft(22));
	titleLabel.setBounds(topSection.reduced(2));

	//  Controls area.
	juce::Rectangle<int> controls(oscArea.removeFromTop(oscArea.getHeight() / 3));
	
	//  Oscillator Type.
	juce::Rectangle<int> oscTypeArea(controls.removeFromLeft(100));
	oscTypeLabel.setBounds(oscTypeArea.removeFromTop(20));
	oscTypeInput.setBounds(oscTypeArea.reduced(2));

	//  Transpose selection area.
	juce::Rectangle<int> transposeArea(controls);
	transposeLabel.setBounds(transposeArea.removeFromTop(20));
	transposeSlider.setBounds(transposeArea);

	//  Envelope sliders and labels area - needs reviewing.
	juce::Rectangle<int> oscEnvelope(oscArea);
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
