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
		targetGain(0.0f),
		currentGain(targetGain),
		targetFilterCutoff(5000.0f),
		currentFilterCutoff(targetFilterCutoff)
#endif
{
	// Gain parameter.
	NormalisableRange<float> gainRange(0.0f, 1.0f, 0.01f);
	treeState.createAndAddParameter("gain", "Gain", String(), gainRange, 0.5f, nullptr, nullptr);
	
	// Number of voices parameter.
	NormalisableRange<float> numVoicesRange(0, 9);
	treeState.createAndAddParameter("oscNumVoices", "NumVoices", String(), numVoicesRange, 9, nullptr, nullptr);

	// Oscillator type parameter.
	NormalisableRange<float> oscTypeRange(0, 3);
	treeState.createAndAddParameter("oscType", "OscType", String(), oscTypeRange, 2, nullptr, nullptr);

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
	treeState.createAndAddParameter("volEnvAttack", "VolEnvAttack", String(), attackRange, 0.1f, nullptr, nullptr);
	treeState.createAndAddParameter("volEnvDecay", "VolEnvDecay", String(), decayRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("volEnvSustain", "VolEnvSustain", String(), sustainRange, 0.001f, nullptr, nullptr);
	treeState.createAndAddParameter("volEnvRelease", "VolEnvRelease", String(), releaseRange, 0.015f, nullptr, nullptr);

	// IRR Filter parameter(S).
	// One filter instance for each channel to avoid distortions.
	NormalisableRange<float> filterCutoffRange(20.f, 20000.f, 0.01f);
	NormalisableRange<float> filterTypeRange(0.0f, 6.f, 1.f);
	NormalisableRange<float> filterQRange(0.01f, 3.f, 0.01f);
	NormalisableRange<float> filterGainFactorRange(0.01f, 3.f, 0.01f);
	NormalisableRange<float> toggleFilterRange(0, 1);
	filterCutoffRange.setSkewForCentre(1000.0f);
	filterGainFactorRange.setSkewForCentre(1.0f);
	treeState.createAndAddParameter("filterCutoff", "FilterCutoff", String(), filterCutoffRange, 5000.f, nullptr, nullptr);
	treeState.createAndAddParameter("filterType", "FilterType", String(), filterTypeRange, 0, nullptr, nullptr);
	treeState.createAndAddParameter("filterQ", "FilterQ", String(), filterQRange, 0.8f, nullptr, nullptr);
	treeState.createAndAddParameter("filterGainFactor", "FilterGainFactor", String(), filterGainFactorRange, 0.01f, nullptr, nullptr);
	treeState.createAndAddParameter("filterToggle", "FilterToggle", String(), toggleFilterRange, 0, nullptr, nullptr);

	/* Distortion parameters.
	NormalisableRange<float> distortionDriveRange(0.f, 1.f, 0.01f);
	NormalisableRange<float> distortionRangeRange(0.f, 3000.f, 0.01f);
	NormalisableRange<float> distortionMixRange(0.f, 1.f, 0.01f);
	NormalisableRange<float> toggleDistortionRange(0, 1);
	treeState.createAndAddParameter("distortionDrive", "DistortionDrive", String(), distortionDriveRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("distortionRange", "DistortionRange", String(), distortionRangeRange, 1500.f, nullptr, nullptr);
	treeState.createAndAddParameter("distortionMix", "DistortionMix", String(), distortionMixRange, 0.0f, nullptr, nullptr);
	treeState.createAndAddParameter("distortionToggle", "DistortionToggle", String(), toggleDistortionRange, 0, nullptr, nullptr);*/

	// LFO parameters.
	NormalisableRange<float> lfoDepthRange(0.0f, 100.0f, 1.0f);
	NormalisableRange<float> lfoRateRange(0.0f, 20.0f, 0.01f);
	NormalisableRange<float> lfoToggleRange(0, 1);
	lfoRateRange.setSkewForCentre(5.0);
	treeState.createAndAddParameter("lfoDepth", "LfoDepth", String(), lfoDepthRange, 100.0f, nullptr, nullptr);
	treeState.createAndAddParameter("lfoRate", "LfoRate", String(), lfoRateRange, 1.0f, nullptr, nullptr);
	treeState.createAndAddParameter("lfoToggle", "LfoToggle", String(), lfoToggleRange, 1, nullptr, nullptr);

	// Delay parameters.
	NormalisableRange<float> delayTimeRange(0.01f, 2.0f, 0.001f);
	NormalisableRange<float> delayFeedbackRange(0.0f, 1.0f, 0.001f);
	NormalisableRange<float> delayWetRange(0.0f, 1.0f, 0.001f);
	NormalisableRange<float> toggleDelayRange(0, 1);
	treeState.createAndAddParameter("delayTime", "DelayTime", String(), delayTimeRange, 1.f, nullptr, nullptr);
	treeState.createAndAddParameter("delayFeedback", "DelayFeedback", String(), delayFeedbackRange, 0.f, nullptr, nullptr);
	treeState.createAndAddParameter("delayMix", "DelayMix", String(), delayWetRange, 0.0f, nullptr, nullptr);
	treeState.createAndAddParameter("delayToggle", "DelayToggle", String(), toggleDelayRange, 0, nullptr, nullptr);

	// Reverb parameters.
	NormalisableRange<float> dryWetRange(0.0f, 1.0f, 0.01f);
	NormalisableRange<float> roomSizeRange(0.0f, 1.0f, 0.01f);
	NormalisableRange<float> dampingRange(0.0f, 1.0f, 0.01f);
	NormalisableRange<float> widthRange(0.0f, 1.0f, 0.01f);
	NormalisableRange<float> toggleReverbRange(0, 1);
	treeState.createAndAddParameter("reverbMix", "ReverbMix", String(), dryWetRange, 0.f, nullptr, nullptr);
	treeState.createAndAddParameter("reverbRoomSize", "ReverbRoomSize", String(), roomSizeRange, 0.2f, nullptr, nullptr);
	treeState.createAndAddParameter("reverbDamping", "ReverbDamping", String(), dampingRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("reverbWidth", "ReverbWidth", String(), widthRange, 0.5f, nullptr, nullptr);
	treeState.createAndAddParameter("reverbToggle", "ReverbToggle", String(), toggleReverbRange, 0, nullptr, nullptr);

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
	mySynth.setCurrentPlaybackSampleRate(sampleRate);
	delay.prepareToPlay(sampleRate);
	//lfo.prepareToPLay(sampleRate);
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

	// Check if the number of voices selected has changed.
	int numVoicesParam = *treeState.getRawParameterValue("oscNumVoices") + 1;			// Add one for the values to match the combo box IDs.
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
				*treeState.getRawParameterValue("lfoToggle"));
		}
	}

	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	
	// Filter processing.
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

	// Store distortion parameters.
	/*distortion.setParameters(
		*treeState.getRawParameterValue("distortionDrive"),
		*treeState.getRawParameterValue("distortionRange"),
		*treeState.getRawParameterValue("distortionMix"));*/
	
	// Single sample access.
	for (int channel = 0; channel < buffer.getNumChannels(); channel++)
	{
		float* channelData = buffer.getWritePointer(channel);

		for (int sample = 0; sample < buffer.getNumSamples(); sample++)
		{
			// Gain processing:
			// Avoid glicthes via volume increment.
			targetGain = *treeState.getRawParameterValue("gain");
			if (currentGain != targetGain)
				currentGain += (targetGain - currentGain) / buffer.getNumSamples();

			/* Distortion processing.
			float toggleDistortion = *treeState.getRawParameterValue("distortionToggle");
			if (toggleDistortion == 1.0f)
				*channelData = distortion.processSample(*channelData);*/

			// Apply gain.
			*channelData = *channelData * currentGain;
			channelData++;
		}
	}

	// Delay processing.
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

	//  Reverb processing.
	float toggleReverb = *treeState.getRawParameterValue("reverbToggle");
	if (toggleReverb == 1)
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
    return new TnpMidiSynthAudioProcessorEditor (*this, treeState);
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
