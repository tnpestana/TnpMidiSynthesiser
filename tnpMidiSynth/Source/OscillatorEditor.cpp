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

OscillatorEditor::OscillatorEditor(TnpMidiSynthAudioProcessor& p, AudioProcessorValueTreeState& apvts)
{
	// Title label.
	addAndMakeVisible(titleLabel);
	titleLabel.setText("OSCILLATOR", dontSendNotification);
	titleLabel.setJustificationType(Justification::centred);

	// Number of voices components. 
	addAndMakeVisible(numVoicesLabel);
	numVoicesLabel.setText("voices: ", dontSendNotification);
	numVoicesLabel.setJustificationType(Justification::bottomLeft);
	addAndMakeVisible(numVoicesInput);
	for (int i = 1; i < 11; i++)							//	Even though the numVoices parameter's range is defined we
		numVoicesInput.addItem((String)i, i);				// seem to need to populate the combo box anyway.
	numVoicesAttachment = std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment>
		(new AudioProcessorValueTreeState::ComboBoxAttachment(apvts, "numVoices", numVoicesInput));

	// Transpose
	addAndMakeVisible(transposeSlider);
	transposeSlider.setSliderStyle(Slider::LinearHorizontal);
	transposeSlider.setTextBoxStyle(Slider::TextBoxLeft, true, 25, 15);
	addAndMakeVisible(transposeLabel);
	transposeLabel.setText("transpose: ", dontSendNotification);
	transposeLabel.setJustificationType(Justification::bottomLeft);
	transposeAttachment = std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>
		(new AudioProcessorValueTreeState::SliderAttachment(apvts, "transpose", transposeSlider));

	// Oscillator type.
	addAndMakeVisible(oscTypeLabel);
	oscTypeLabel.setText("wave type:", dontSendNotification);
	oscTypeLabel.setJustificationType(Justification::bottomLeft);
	addAndMakeVisible(oscTypeInput);
	oscTypeInput.addItem("sine", 1);					//	Even though the oscType parameter's range is defined we
	oscTypeInput.addItem("square", 2);					// seem to need to populate the combo box anyway.
	oscTypeInput.addItem("triangle", 3);
	oscTypeInput.addItem("sawtooth", 4);
	oscTypeAttachment = std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> 
		(new AudioProcessorValueTreeState::ComboBoxAttachment(apvts, "oscType", oscTypeInput));

	// Attack.
	addAndMakeVisible(attackSlider);
	attackSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(attackLabel);
	attackLabel.setText("attack", dontSendNotification);
	attackLabel.setJustificationType(Justification::centredTop);
	attackAttachment = std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>
		(new AudioProcessorValueTreeState::SliderAttachment(apvts, "attack", attackSlider));

	// Decay.
	addAndMakeVisible(decaySlider);
	decaySlider.setSliderStyle(Slider::RotaryVerticalDrag);
	decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(decayLabel);
	decayLabel.setText("decay", dontSendNotification);
	decayLabel.setJustificationType(Justification::centredTop);
	decayAttachment = std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>
		(new AudioProcessorValueTreeState::SliderAttachment(apvts, "decay", decaySlider));

	// Sustain.
	addAndMakeVisible(sustainSlider);
	sustainSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(sustainLabel);
	sustainLabel.setText("sustain", dontSendNotification);
	sustainLabel.setJustificationType(Justification::centredTop);
	sustainAttachment = std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>
		(new AudioProcessorValueTreeState::SliderAttachment(apvts, "sustain", sustainSlider));

	// Release. 
	addAndMakeVisible(releaseSlider);
	releaseSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(releaseLabel);
	releaseLabel.setText("release", dontSendNotification);
	releaseLabel.setJustificationType(Justification::centredTop);
	releaseAttachment = std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>
		(new AudioProcessorValueTreeState::SliderAttachment(apvts, "release", releaseSlider));

	// Gain.
	addAndMakeVisible(gainSlider);
	gainSlider.setSliderStyle(Slider::LinearVertical);
	gainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	addAndMakeVisible(gainLabel);
	gainLabel.setText("gain", dontSendNotification);
	gainLabel.setJustificationType(Justification::centredTop);
	gainAttachment = std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>
		(new AudioProcessorValueTreeState::SliderAttachment(apvts, "gain", gainSlider));

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
	filterCutoffAttachment = std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>
		(new AudioProcessorValueTreeState::SliderAttachment(apvts, "filterCutoff", filterCutoffSlider));
	filterTypeAttachment = std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment>
		(new AudioProcessorValueTreeState::ComboBoxAttachment(apvts, "filterType", filterTypeInput));
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
	juce::Rectangle<int> gainLocation(oscArea.removeFromRight(oscArea.getWidth() * 0.13).reduced(2));
	gainLabel.setBounds(gainLocation.removeFromBottom(25));
	gainSlider.setBounds(gainLocation);

	// Controls area.
	juce::Rectangle<int> controls(oscArea.removeFromTop(oscArea.getHeight() * 0.25).reduced(2));

	// Number of voices selection area.
	juce::Rectangle<int> numVoicesArea(controls.removeFromLeft(60));
	numVoicesLabel.setBounds(numVoicesArea.removeFromTop(20));
	numVoicesInput.setBounds(numVoicesArea);
	
	// Oscillator Type.
	juce::Rectangle<int> oscTypeArea(controls.removeFromLeft(80));
	oscTypeLabel.setBounds(oscTypeArea.removeFromTop(20));
	oscTypeInput.setBounds(oscTypeArea);

	// Transpose selection area.
	juce::Rectangle<int> transposeArea(controls);
	transposeLabel.setBounds(transposeArea.removeFromTop(20));
	transposeSlider.setBounds(transposeArea);

	// Envelope sliders and labels area - needs reviewing.
	juce::Rectangle<int> oscEnvelope(oscArea.removeFromTop(oscArea.getHeight() * 0.7).reduced(5));

	juce::Rectangle<int> oscEnvelopeSlider(oscEnvelope.removeFromTop(oscEnvelope.getHeight() * 0.7));
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