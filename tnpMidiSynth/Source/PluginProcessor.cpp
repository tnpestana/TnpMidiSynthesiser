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
		//  Processor state variables
		treeState(*this, nullptr, "tnpMidiSynthState",
			//	Parameters
			{
				std::make_unique<AudioParameterFloat>("gain", "Master Gain",
					NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
				std::make_unique<AudioParameterChoice>("numVoices", "Number of Voices", 
					StringArray("1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "16", "32"), 11),
				//  Oscillator
				std::make_unique<AudioParameterChoice>("osc1Type", "Oscillator Type", 
					StringArray("sine", "harmonic", "square", "triangle", "sawtooth"), 2),
				std::make_unique<AudioParameterInt>("osc1Transpose", "Transpose", -24, 24, 0),
				std::make_unique<AudioParameterFloat>("osc1Attack", "Volume Envelope Attack",
					NormalisableRange<float>(0.001f, 5.0f, 0.001f), 0.05f),
				std::make_unique<AudioParameterFloat>("osc1Decay", "Volume Envelope Decay",
					NormalisableRange<float>(0.001f, 5.0f, 0.001f), 0.5f),
				std::make_unique<AudioParameterFloat>("osc1Sustain", "Volume Envelope Sustain",
					NormalisableRange<float>(0.001f, 1.0f, 0.001f), 0.05f),
				std::make_unique<AudioParameterFloat>("osc1Release", "Volume Envelope Release",
					NormalisableRange<float>(0.015f, 5.0f, 0.001f), 0.05f),
				//  Filter
				std::make_unique<AudioParameterFloat>("filterCutoff", "Filter Cutoff",
					NormalisableRange<float>(20.0f, 20000.0f, 0.01f), 1500.0f),
				std::make_unique<AudioParameterChoice>("filterType", "Filter Type",
					StringArray("lo-pass", "hi-pass", "band-pass", "notch", "lo-shelf", "hi-shelf", "peak"), 0),
				std::make_unique<AudioParameterFloat>("filterQ", "Filter Q",
					NormalisableRange<float>(0.01f, 3.0f, 0.01f), 1.6f),
				std::make_unique<AudioParameterFloat>("filterGainFactor", "Filter Gain Factor",
					NormalisableRange<float>(0.01f, 3.0f, 0.01f), 0.5f),
				std::make_unique<AudioParameterInt>("filterToggle", "Filter Toggle", 0, 1, 1),
				//  LFO
				std::make_unique<AudioParameterChoice>("lfoOscType", "LFO Oscillator Type", 
					StringArray("sine", "square", "triangle", "sawtooth"), 2),
				std::make_unique<AudioParameterFloat>("lfoDepth", "LFO Depth",
					NormalisableRange<float>(0.0f, 100.0f, 1.0f), 100.0f),
				std::make_unique<AudioParameterFloat>("lfoRate", "LFO Rate",
					NormalisableRange<float>(0.0f, 20.0f, 0.01f), 1.0f),
				std::make_unique<AudioParameterInt>("lfoToggle", "LFO Toggle", 0, 1, 0),
				//  Delay
				std::make_unique<AudioParameterFloat>("delayTime", "Delay Time",
					NormalisableRange<float>(0.01f, 2.0f, 0.001f), 0.8f),
				std::make_unique<AudioParameterFloat>("delayFeedback", "Delay Feedback",
					NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.2f),
				std::make_unique<AudioParameterFloat>("delayMix", "Delay Mix",
					NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.2f),
				std::make_unique<AudioParameterInt>("delayToggle", "Delay Toggle", 0, 1, 1),
				//  Reverb
				std::make_unique<AudioParameterFloat>("reverbMix", "Reverb Mix",
					NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f),
				std::make_unique<AudioParameterFloat>("reverbRoomSize", "Reverb Room Size",
					NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.2f),
				std::make_unique<AudioParameterFloat>("reverbDamping", "Reverb Damping",
					NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
				std::make_unique<AudioParameterFloat>("reverbWidth", "Rever bWidth",
					NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
				std::make_unique<AudioParameterInt>("reverbToggle", "Reverb Toggle", 0, 1, 0),
			}
		),
		keyboardState(),
		//  Local variables
		targetGain(0.0f),
		currentGain(targetGain),
		targetFilterCutoff(5000.0f),
		currentFilterCutoff(targetFilterCutoff),
		localSampleRate(1.0)
#endif
{
	dynamic_cast<AudioParameterFloat*>(treeState.getParameter("osc1Attack"))->range.setSkewForCentre(1.0f);
	dynamic_cast<AudioParameterFloat*>(treeState.getParameter("osc1Decay"))->range.setSkewForCentre(1.0f);
	dynamic_cast<AudioParameterFloat*>(treeState.getParameter("osc1Release"))->range.setSkewForCentre(1.0f);
	dynamic_cast<AudioParameterFloat*>(treeState.getParameter("filterCutoff"))->range.setSkewForCentre(1000.0f);
	dynamic_cast<AudioParameterFloat*>(treeState.getParameter("filterGainFactor"))->range.setSkewForCentre(1.0f);
	dynamic_cast<AudioParameterFloat*>(treeState.getParameter("lfoRate"))->range.setSkewForCentre(5.0f);
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
	localSampleRate = sampleRate;
	WavetableOscillator::createWavetable(sampleRate);
	mySynth.setCurrentPlaybackSampleRate(sampleRate);

	treeState.addParameterListener("filterType", this);
	treeState.addParameterListener("filterCutoff", this);
	treeState.addParameterListener("filterQ", this);
	treeState.addParameterListener("filterGainFactor", this);
	updateFilter();

	treeState.addParameterListener("lfoToggle", this);
	treeState.addParameterListener("lfoOscType", this);
	treeState.addParameterListener("lfoDepth", this);
	treeState.addParameterListener("lfoRate", this);
	lfo.prepareToPLay(getSampleRate());
	updateLFO();

	treeState.addParameterListener("delayTime", this);
	treeState.addParameterListener("delayFeedback", this);
	treeState.addParameterListener("delayMix", this);
	delay.prepareToPlay(sampleRate);
	updateDelay();

	treeState.addParameterListener("reverbMix", this);
	treeState.addParameterListener("reverbRoomSize", this);
	treeState.addParameterListener("reverbDamping", this);
	treeState.addParameterListener("reverbWidth", this);
	reverb.setSampleRate(sampleRate);
	updateReverb();
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
	for (int i = getNumInputChannels(); i < getNumOutputChannels(); i++)
		buffer.clear(i, 0, buffer.getNumSamples());								
	manageActiveVoices();
	keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

	if (*treeState.getRawParameterValue("filterToggle") == 1.0f)
		processFilter(buffer);

	if (*treeState.getRawParameterValue("lfoToggle") == 1.0)
		processLFO(buffer);
	
	if (*treeState.getRawParameterValue("delayToggle") == 1.0f)
		processDelay(buffer);

	if (*treeState.getRawParameterValue("reverbToggle") == 1.0f)
		processReverb(buffer);

	processGain(buffer);
}

//==============================================================================
void TnpMidiSynthAudioProcessor::manageActiveVoices()
{
	// Check if the number of voices selected has changed.
	int numVoicesParam = *treeState.getRawParameterValue("numVoices") + 1;	//  Add one for the values to match the combo box IDs.
	numVoicesParam = numVoicesParam == 11 ? 16 : numVoicesParam;				//  If the parameter returns the value 11 it means there 
	numVoicesParam = numVoicesParam == 12 ? 32 : numVoicesParam;				// are 16 voices.
	if (numVoicesParam != mySynth.getNumVoices())
	{
		setNumVoices(numVoicesParam);
	}
	// Iterate through activating voices.
	for (int i = 0; i < mySynth.getNumVoices(); i++)
	{
		//  Cast them to see how many of those are being used. If they are,
		// pass them the value tree state gain and envelope parameters.
		if (mySynthVoice = dynamic_cast<TnpSynthVoice*>(mySynth.getVoice(i)))
		{
			mySynthVoice->getOscillatorType(*treeState.getRawParameterValue("osc1Type"));
			mySynthVoice->getTransposeValue(*treeState.getRawParameterValue("osc1Transpose"));
			mySynthVoice->getEnvelopeParameters(*treeState.getRawParameterValue("osc1Attack"),
				*treeState.getRawParameterValue("osc1Decay"),
				*treeState.getRawParameterValue("osc1Sustain"),
				*treeState.getRawParameterValue("osc1Release"));
		}
	}
}

//==============================================================================
void TnpMidiSynthAudioProcessor::processGain(AudioBuffer<float>& buffer)
{
	for (int channel = 0; channel < buffer.getNumChannels(); channel++)
	{
		float* channelData = buffer.getWritePointer(channel);

		for (int sample = 0; sample < buffer.getNumSamples(); sample++)
		{
			// Avoid glicthes via volume increment.
			targetGain = *treeState.getRawParameterValue("gain");
			if (currentGain != targetGain)
				currentGain += (targetGain - currentGain) / buffer.getNumSamples();

			// Apply gain.
			*channelData = *channelData * currentGain;
			channelData++;
		}
	}
}


//==============================================================================
void TnpMidiSynthAudioProcessor::updateLFO()
{
	const float lfoDepth = *treeState.getRawParameterValue("lfoDepth");
	const float lfoRate = *treeState.getRawParameterValue("lfoRate");
	const int lfoOscType = *treeState.getRawParameterValue("lfoOscType");

	lfo.updateParameters(lfoDepth, lfoRate, lfoOscType);
}

void TnpMidiSynthAudioProcessor::processLFO(AudioBuffer<float>& buffer)
{
	for (int sample = 0; sample < buffer.getNumSamples(); sample++)
	{
		for (int channel = 0; channel < buffer.getNumChannels(); channel++)
		{
			float* channelData = buffer.getWritePointer(channel, sample);
			lfo.processAudioFrame(channelData);
		}
	}
}

//==============================================================================
void TnpMidiSynthAudioProcessor::updateFilter()
{
	const int filterType = *treeState.getRawParameterValue("filterType");
	const float filterQ = *treeState.getRawParameterValue("filterQ");
	const float filterCutoff = *treeState.getRawParameterValue("filterCutoff");
	const float filterGainFactor = *treeState.getRawParameterValue("filterGainFactor");
	switch (filterType)
	{
	case 0:
		filterLeft.setCoefficients(IIRCoefficients::makeLowPass(localSampleRate, filterCutoff, filterQ));
		filterRight.setCoefficients(IIRCoefficients::makeLowPass(localSampleRate, filterCutoff, filterQ));
		break;
	case 1:
		filterLeft.setCoefficients(IIRCoefficients::makeHighPass(localSampleRate, filterCutoff, filterQ));
		filterRight.setCoefficients(IIRCoefficients::makeHighPass(localSampleRate, filterCutoff, filterQ));
		break;
	case 2:
		filterLeft.setCoefficients(IIRCoefficients::makeBandPass(localSampleRate, filterCutoff, filterQ));
		filterRight.setCoefficients(IIRCoefficients::makeBandPass(localSampleRate, filterCutoff, filterQ));
		break;
	case 3:
		filterLeft.setCoefficients(IIRCoefficients::makeNotchFilter(localSampleRate, filterCutoff, filterQ));
		filterRight.setCoefficients(IIRCoefficients::makeNotchFilter(localSampleRate, filterCutoff, filterQ));
		break;
	case 4:
		filterLeft.setCoefficients(IIRCoefficients::makeLowShelf(localSampleRate, filterCutoff, filterQ, filterGainFactor));
		filterRight.setCoefficients(IIRCoefficients::makeLowShelf(localSampleRate, filterCutoff, filterQ, filterGainFactor));
		break;
	case 5:
		filterLeft.setCoefficients(IIRCoefficients::makeHighShelf(localSampleRate, filterCutoff, filterQ, filterGainFactor));
		filterRight.setCoefficients(IIRCoefficients::makeHighShelf(localSampleRate, filterCutoff, filterQ, filterGainFactor));
		break;
	case 6:
		filterLeft.setCoefficients(IIRCoefficients::makePeakFilter(localSampleRate, filterCutoff, filterQ, filterGainFactor));
		filterRight.setCoefficients(IIRCoefficients::makePeakFilter(localSampleRate, filterCutoff, filterQ, filterGainFactor));
		break;
	}
}

void TnpMidiSynthAudioProcessor::processFilter(AudioBuffer<float>& buffer)
{
	if (buffer.getNumChannels() == 1)
	{
		filterLeft.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
	}
	else if (buffer.getNumChannels() == 2)
	{
		filterLeft.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
		filterRight.processSamples(buffer.getWritePointer(1), buffer.getNumSamples());
	}
}

//==============================================================================
void TnpMidiSynthAudioProcessor::updateDelay()
{
	delay.updateParams(*treeState.getRawParameterValue("delayTime"),
		*treeState.getRawParameterValue("delayFeedback"),
		*treeState.getRawParameterValue("delayMix"));
}

void TnpMidiSynthAudioProcessor::processDelay(AudioBuffer<float>& buffer)
{
	for (int sample = 0; sample < buffer.getNumSamples(); sample++)
	{
		float* outputDataL = buffer.getWritePointer(0, sample);
		float* outputDataR = buffer.getWritePointer(1, sample);
		delay.processAudio(outputDataL, outputDataR);
	}
}

//==============================================================================
void TnpMidiSynthAudioProcessor::updateReverb()
{
	reverbParameters.dryLevel = 1.0f - *treeState.getRawParameterValue("reverbMix");	//	Dereference the result of getRawParameterValue because it returns
	reverbParameters.wetLevel = *treeState.getRawParameterValue("reverbMix");			// a pointer to the parameter's value location.
	reverbParameters.roomSize = *treeState.getRawParameterValue("reverbRoomSize");
	reverbParameters.damping = *treeState.getRawParameterValue("reverbDamping");
	reverbParameters.width = *treeState.getRawParameterValue("reverbWidth");
	reverb.setParameters(reverbParameters);
}

void TnpMidiSynthAudioProcessor::processReverb(AudioBuffer<float>& buffer)
{
	// Support reverb processing for mono and stereo systems.
	if (buffer.getNumChannels() == 1)
	{
		reverb.processMono(buffer.getWritePointer(0), buffer.getNumSamples());
	}
	else if (buffer.getNumChannels() == 2)
	{
		reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
	}
}

//==============================================================================
AudioProcessorValueTreeState & TnpMidiSynthAudioProcessor::getTreeState()
{
	return treeState;
}

MidiKeyboardState & TnpMidiSynthAudioProcessor::getMidiState()
{
	return keyboardState;
}

//==============================================================================
// This method is called to change the synth's number of voices.
void TnpMidiSynthAudioProcessor::setNumVoices(int numVoices)
{
	mySynth.clearVoices();
	for (int i = 0; i < numVoices; i++)
		mySynth.addVoice(new TnpSynthVoice());
	mySynth.clearSounds();
	mySynth.addSound(new TnpSynthSound());
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

void TnpMidiSynthAudioProcessor::parameterChanged(const String & parameterID, float newValue)
{
	if (parameterID == "filterToggle" ||
		parameterID == "filterType" ||
		parameterID == "filterCutoff" ||
		parameterID == "filterQ" ||
		parameterID == "filterGainFactor")
	{
		updateFilter();
	}
	else if (parameterID == "lfoOscType" ||
		parameterID == "lfoDepth" ||
		parameterID == "lfoRate")
	{
		updateLFO();
	}
	else if (parameterID == "delayTime" ||
		parameterID == "delayFeedback" ||
		parameterID == "delayMix")
	{
		updateDelay();
	}
	else if (parameterID == "reverbMix" ||
		parameterID == "reverbRoomSize" ||
		parameterID == "delayDamping" ||
		parameterID == "reverbWidth")
	{
		updateReverb();
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TnpMidiSynthAudioProcessor();
}
