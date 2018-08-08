/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TnpSynth.h"
#include "TnpDistortion.h"
#include "TnpStereoDelay.h"

//==============================================================================
class TnpMidiSynthAudioProcessor : public AudioProcessor
{
public:
    //==============================================================================
    TnpMidiSynthAudioProcessor();
    ~TnpMidiSynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

	//==============================================================================
	void setNumVoices(int numVoices);

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
	AudioProcessorValueTreeState treeState;

	Synthesiser mySynth;
	TnpSynthVoice* mySynthVoice;

	Reverb reverb;
	Reverb::Parameters reverbParameters;

	IIRFilter filterLeft;
	IIRFilter filterRight;

	TnpDistortion distortion;

	TnpStereoDelay delay;

	double localSampleRate, currentGain, targetGain;
	int targetNumVoices;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpMidiSynthAudioProcessor)
};
