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
		treeState(*this, nullptr),
		keyboardState(),
		targetGain(0.0f),
		currentGain(targetGain),
		targetFilterCutoff(5000.0f),
		currentFilterCutoff(targetFilterCutoff)
#endif
{
	// Gain parameter.
	NormalisableRange<float> gainRange(0.0f, 1.0f, 0.01f);
	treeState.createAndAddParameter("gain", "Master Gain", String(), gainRange, 0.5f, nullptr, nullptr);
	// Number of voices parameter.
	NormalisableRange<float> numVoicesRange(0, 11);
	treeState.createAndAddParameter("oscNumVoices", "Number of Voices", String(), numVoicesRange, 11, nullptr, nullptr);
	// Oscillator type parameter.
	NormalisableRange<float> oscTypeRange(0, 4);
	treeState.createAndAddParameter("oscType", "Oscillator Type", String(), oscTypeRange, 2, nullptr, nullptr);
	// Transpose parameter.
	NormalisableRange<float> transposeRange(-24.0f, 24.0f, 1.0f);
	treeState.createAndAddParameter("oscTranspose", "Transpose", String(), transposeRange, 0, nullptr, nullptr);

	// Volume envelope parameters.
	NormalisableRange<float> attackRange(0.001f, 5.0f, 0.001f);
	NormalisableRange<float> decayRange(0.001f, 5.0f, 0.001f);
	NormalisableRange<float> sustainRange(0.001f, 1.0f, 0.001f);
	NormalisableRange<float> releaseRange(0.015f, 5.0f, 0.001f);
	attackRange.setSkewForCentre(1.0);
	decayRange.setSkewForCentre(1.0);
	releaseRange.setSkewForCentre(1.0);
	treeState.createAndAddParameter("volEnvAttack", "Volume Envelope Attack", String(), attackRange, 0.05f, nullptr, nullptr);
	treeState.createAndAddParameter("volEnvDecay", "Volume Envelope Decay", String(), decayRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("volEnvSustain", "Volume Envelope Sustain", String(), sustainRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("volEnvRelease", "Volume Envelope Release", String(), releaseRange, 0.05f, nullptr, nullptr);

	// IRR Filter parameter(S).
	// One filter instance for each channel to avoid distortion.
	NormalisableRange<float> filterCutoffRange(20.f, 20000.f, 0.01f);
	NormalisableRange<float> filterTypeRange(0.0f, 6.f, 1.f);
	NormalisableRange<float> filterQRange(0.01f, 3.f, 0.01f);
	NormalisableRange<float> filterGainFactorRange(0.01f, 3.f, 0.01f);
	NormalisableRange<float> toggleFilterRange(0, 1);
	filterCutoffRange.setSkewForCentre(1000.0f);
	filterGainFactorRange.setSkewForCentre(1.0f);
	treeState.createAndAddParameter("filterCutoff", "Filter Cutoff", String(), filterCutoffRange, 1500.f, nullptr, nullptr);
	treeState.createAndAddParameter("filterType", "Filter Type", String(), filterTypeRange, 0, nullptr, nullptr);
	treeState.createAndAddParameter("filterQ", "Filter Q", String(), filterQRange, 1.6f, nullptr, nullptr);
	treeState.createAndAddParameter("filterGainFactor", "Filter Gain Factor", String(), filterGainFactorRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("filterToggle", "Filter Toggle", String(), toggleFilterRange, 1, nullptr, nullptr);

	// LFO parameters.
	NormalisableRange<float> lfoOscTypeRange(0, 3);
	NormalisableRange<float> lfoDepthRange(0.0f, 100.0f, 1.0f);
	NormalisableRange<float> lfoRateRange(0.0f, 20.0f, 0.01f);
	NormalisableRange<float> lfoToggleRange(0, 1);
	lfoRateRange.setSkewForCentre(5.0);
	treeState.createAndAddParameter("lfoOscType", "LFO Oscillator Type", String(), lfoOscTypeRange, 2, nullptr, nullptr);
	treeState.createAndAddParameter("lfoDepth", "LFO Depth", String(), lfoDepthRange, 100.0f, nullptr, nullptr);
	treeState.createAndAddParameter("lfoRate", "LFO Rate", String(), lfoRateRange, 1.0f, nullptr, nullptr);
	treeState.createAndAddParameter("lfoToggle", "LFO Toggle", String(), lfoToggleRange, 0, nullptr, nullptr);

	// Delay parameters.
	NormalisableRange<float> delayTimeRange(0.01f, 2.0f, 0.001f);
	NormalisableRange<float> delayFeedbackRange(0.0f, 1.0f, 0.001f);
	NormalisableRange<float> delayWetRange(0.0f, 1.0f, 0.001f);
	NormalisableRange<float> toggleDelayRange(0, 1);
	treeState.createAndAddParameter("delayTime", "Delay Time", String(), delayTimeRange, 0.8f, nullptr, nullptr);
	treeState.createAndAddParameter("delayFeedback", "Delay Feedback", String(), delayFeedbackRange, 0.2f, nullptr, nullptr);
	treeState.createAndAddParameter("delayMix", "Delay Mix", String(), delayWetRange, 0.2f, nullptr, nullptr);
	treeState.createAndAddParameter("delayToggle", "Delay Toggle", String(), toggleDelayRange, 1, nullptr, nullptr);

	// Reverb parameters.
	NormalisableRange<float> dryWetRange(0.0f, 1.0f, 0.01f);
	NormalisableRange<float> roomSizeRange(0.0f, 1.0f, 0.01f);
	NormalisableRange<float> dampingRange(0.0f, 1.0f, 0.01f);
	NormalisableRange<float> widthRange(0.0f, 1.0f, 0.01f);
	NormalisableRange<float> toggleReverbRange(0, 1);
	treeState.createAndAddParameter("reverbMix", "Reverb Mix", String(), dryWetRange, 0.f, nullptr, nullptr);
	treeState.createAndAddParameter("reverbRoomSize", "Reverb Room Size", String(), roomSizeRange, 0.2f, nullptr, nullptr);
	treeState.createAndAddParameter("reverbDamping", "Reverb Damping", String(), dampingRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("reverbWidth", "Rever bWidth", String(), widthRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("reverbToggle", "Reverb Toggle", String(), toggleReverbRange, 0, nullptr, nullptr);

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
	localSampleRate = sampleRate;
	WavetableOscillator::createWavetable(sampleRate);
	mySynth.setCurrentPlaybackSampleRate(sampleRate);
	delay.prepareToPlay(sampleRate);
	reverb.setSampleRate(sampleRate);
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
	processGain(buffer);
	processFilter(buffer);
	processDelay(buffer);
	processReverb(buffer);
}

void TnpMidiSynthAudioProcessor::manageActiveVoices()
{
	// Check if the number of voices selected has changed.
	int numVoicesParam = *treeState.getRawParameterValue("oscNumVoices") + 1;	// Add one for the values to match the combo box IDs.
	numVoicesParam = numVoicesParam == 11 ? 16 : numVoicesParam;				// If the parameter returns the value 11 it means there are 16 voices.
	numVoicesParam = numVoicesParam == 12 ? 32 : numVoicesParam;
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
			mySynthVoice->getOscillatorType(*treeState.getRawParameterValue("oscType"));
			mySynthVoice->getTransposeValue(*treeState.getRawParameterValue("oscTranspose"));
			mySynthVoice->getEnvelopeParameters(*treeState.getRawParameterValue("volEnvAttack"),
				*treeState.getRawParameterValue("volEnvDecay"),
				*treeState.getRawParameterValue("volEnvSustain"),
				*treeState.getRawParameterValue("volEnvRelease"));
			mySynthVoice->getLfoParameters(*treeState.getRawParameterValue("lfoDepth"),
				*treeState.getRawParameterValue("lfoRate"),
				*treeState.getRawParameterValue("lfoToggle"),
				*treeState.getRawParameterValue("lfoOscType"));
		}
	}
}

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

void TnpMidiSynthAudioProcessor::processFilter(AudioBuffer<float>& buffer)
{
	float toggleFilter = *treeState.getRawParameterValue("filterToggle");
	if (toggleFilter == 1.0f)
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
}

void TnpMidiSynthAudioProcessor::processDelay(AudioBuffer<float>& buffer)
{
	float toggleDelay = *treeState.getRawParameterValue("delayToggle");
	if (toggleDelay == 1.0f)
	{
		delay.updateParams(*treeState.getRawParameterValue("delayTime"),
			*treeState.getRawParameterValue("delayFeedback"),
			*treeState.getRawParameterValue("delayMix"));

		for (int sample = 0; sample < buffer.getNumSamples(); sample++)
		{
			float* outputDataL = buffer.getWritePointer(0, sample);
			float* outputDataR = buffer.getWritePointer(1, sample);
			delay.processAudio(outputDataL, outputDataR);
		}
	}
}

void TnpMidiSynthAudioProcessor::processReverb(AudioBuffer<float>& buffer)
{
	float toggleReverb = *treeState.getRawParameterValue("reverbToggle");
	if (toggleReverb == 1.0f)
	{
		reverbParameters.dryLevel = 1.0f - *treeState.getRawParameterValue("reverbMix");	//	Dereference the result of getRawParameterValue because it returns
		reverbParameters.wetLevel = *treeState.getRawParameterValue("reverbMix");			// a pointer to the parameter's value location.
		reverbParameters.roomSize = *treeState.getRawParameterValue("reverbRoomSize");
		reverbParameters.damping = *treeState.getRawParameterValue("reverbDamping");
		reverbParameters.width = *treeState.getRawParameterValue("reverbWidth");
		reverb.setParameters(reverbParameters);
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
    return new TnpMidiSynthAudioProcessorEditor (*this, treeState, keyboardState);
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
