/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SineSynth.h"

//==============================================================================
MidiSynthesizerAudioProcessor::MidiSynthesizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	synth.clearVoices();
	for (auto i = 0; i < 5; ++i)
		synth.addVoice(new SineSynthVoice());

	synth.clearSounds();
	synth.addSound(new SineSynthSound());
}

MidiSynthesizerAudioProcessor::~MidiSynthesizerAudioProcessor()
{
}



//==============================================================================
const String MidiSynthesizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiSynthesizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiSynthesizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiSynthesizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidiSynthesizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiSynthesizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiSynthesizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiSynthesizerAudioProcessor::setCurrentProgram (int index)
{
}

const String MidiSynthesizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidiSynthesizerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MidiSynthesizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	synth.setCurrentPlaybackSampleRate(sampleRate);
}

void MidiSynthesizerAudioProcessor::releaseResources()
{
	synth.clearSounds();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiSynthesizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MidiSynthesizerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	buffer.clear();

	keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
	synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool MidiSynthesizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidiSynthesizerAudioProcessor::createEditor()
{
    return new MidiSynthesizerAudioProcessorEditor (*this, keyboardState, deviceManager);
}

//==============================================================================
void MidiSynthesizerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidiSynthesizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiSynthesizerAudioProcessor();
}
