/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TnpMidiSynthAudioProcessor::TnpMidiSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
		treeState(*this, nullptr)
#endif
{
	// Gain parameter.
	NormalisableRange<float> gainRange(0.0f, 1.0f, 0.01f);
	treeState.createAndAddParameter("gain", "Gain", String(), gainRange, 1.0f, nullptr, nullptr);

	// Volume envelope parameters.
	NormalisableRange<float> attackRange(0.001f, 5.0f, 0.001f);
	NormalisableRange<float> decayRange(0.001f, 5.0f, 0.001f);
	NormalisableRange<float> sustainRange(0.001f, 1.0f, 0.001f);
	NormalisableRange<float> releaseRange(0.015f, 5.0f, 0.001f);
	attackRange.setSkewForCentre(1.0);
	decayRange.setSkewForCentre(1.0);
	releaseRange.setSkewForCentre(1.0);
	treeState.createAndAddParameter("attack", "Attack", String(), attackRange, 0.1f, nullptr, nullptr);
	treeState.createAndAddParameter("decay", "Decay", String(), decayRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("sustain", "Sustain", String(), sustainRange, 0.001f, nullptr, nullptr);
	treeState.createAndAddParameter("release", "Release", String(), releaseRange, 0.015f, nullptr, nullptr);

	// Reverb parameters.
	reverb = new Reverb();
	NormalisableRange<float> dryWetRange(0.0f, 1.0f, 0.01f);
	NormalisableRange<float> roomSizeRange(0.0f, 1.0f, 0.01f);
	NormalisableRange<float> dampingRange(0.0f, 1.0f, 0.01f);
	treeState.createAndAddParameter("dryWet", "DryWet", String(), dryWetRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("roomSize", "RoomSize", String(), roomSizeRange, 0.2f, nullptr, nullptr);
	treeState.createAndAddParameter("damping", "Damping", String(), dampingRange, 0.0f, nullptr, nullptr);

	// IRR Filter parameter(S).
	NormalisableRange<float> filterCutoffRange(20.f, 20000.f, 1.f);
	NormalisableRange<float> filterTypeRange(0, 1);
	filterCutoffRange.setSkewForCentre(5000.f);
	treeState.createAndAddParameter("filterCutoff", "FilterCutoff", String(), filterCutoffRange, 5000.f, nullptr, nullptr);
	treeState.createAndAddParameter("filterType", "FilterType", String(), filterTypeRange, 0, nullptr, nullptr);


	// Number of voices parameter.
	NormalisableRange<float> numVoicesRange(0, 9);
	treeState.createAndAddParameter("numVoices", "NumVoices", String(), numVoicesRange, 9, nullptr, nullptr);

	// Oscillator type parameter.
	NormalisableRange<float> oscTypeRange(0, 1);
	treeState.createAndAddParameter("oscType", "OscType", String(), oscTypeRange, 0, nullptr, nullptr);

	treeState.state = ValueTree(Identifier("tnpMidiSynthState"));
}

TnpMidiSynthAudioProcessor::~TnpMidiSynthAudioProcessor()
{
}

//==============================================================================
const String TnpMidiSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TnpMidiSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TnpMidiSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TnpMidiSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TnpMidiSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TnpMidiSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TnpMidiSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TnpMidiSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String TnpMidiSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void TnpMidiSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TnpMidiSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	mySynth.setCurrentPlaybackSampleRate(sampleRate);
}

void TnpMidiSynthAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TnpMidiSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TnpMidiSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	buffer.clear();

	//  Dry and wet levels are bound to the same slider as they should be
	// inversely proportioned.
	reverbParameters.dryLevel = 1.0f - *treeState.getRawParameterValue("dryWet");	//	Dereference the result of getRawParameterValue because it returns
	reverbParameters.wetLevel = *treeState.getRawParameterValue("dryWet");			// a pointer to the parameter's value location.
	reverbParameters.roomSize = *treeState.getRawParameterValue("roomSize");
	reverbParameters.damping = *treeState.getRawParameterValue("damping");
	reverb->setParameters(reverbParameters);

	// Check if the number of voices selected has changed.
	int numVoicesParam = *treeState.getRawParameterValue("numVoices") + 1;
	if (numVoicesParam != mySynth.getNumVoices())
	{
		setNumVoices(numVoicesParam);
	}

	// Iterate through activating voices.
	for (int i = 0; i < mySynth.getNumVoices(); i++)
	{
		//  Cast them to see how many of those are being used. If they are,
		// pass them the value tree state gain and envelope parameters.
		if (mySynthVoice = dynamic_cast<MySynthVoice*>(mySynth.getVoice(i)))
		{
			mySynthVoice->getOscillatorType(*treeState.getRawParameterValue("oscType") + 1);
			mySynthVoice->getGainValue(*treeState.getRawParameterValue("gain"));
			mySynthVoice->getEnvelopeParameters(*treeState.getRawParameterValue("attack"),
				*treeState.getRawParameterValue("decay"),
				*treeState.getRawParameterValue("sustain"),
				*treeState.getRawParameterValue("release"));
			mySynthVoice->getFilterParameters(*treeState.getRawParameterValue("filterType"),
										      *treeState.getRawParameterValue("filterCutoff"));
		}
	}

	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

	// Support reverb processing for mono and stereo systems.
	if (buffer.getNumChannels() == 1)
		reverb->processMono(buffer.getWritePointer(0), buffer.getNumSamples());
	else if (buffer.getNumChannels() == 2)
		reverb->processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
}

//==============================================================================
// This method is called to change the synth's number of voices.
void TnpMidiSynthAudioProcessor::setNumVoices(int numVoices)
{
	mySynth.clearVoices();
	for (int i = 0; i < numVoices; i++)
		mySynth.addVoice(new MySynthVoice());
	mySynth.clearSounds();
	mySynth.addSound(new MySynthSound());
}

//==============================================================================
bool TnpMidiSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TnpMidiSynthAudioProcessor::createEditor()
{
    return new TnpMidiSynthAudioProcessorEditor (*this);
}

//==============================================================================
void TnpMidiSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	auto state = treeState.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void TnpMidiSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(treeState.state.getType()))
			treeState.replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TnpMidiSynthAudioProcessor();
}
