/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TnpSynth.h"
#include "TnpStereoDelay.h"
#include "TnpLFO.h"

//==============================================================================
class TnpMidiSynthAudioProcessor : public AudioProcessor, public AudioProcessorValueTreeState::Listener
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

    void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;
	void manageActiveVoices();
	void processGain (AudioBuffer<float>& buffer);

	void updateFilter();
	void processFilter (AudioBuffer<float>& buffer);

	void updateLFO();
	void processLFO(AudioBuffer<float>& buffer);

	void updateDelay();
	void processDelay (AudioBuffer<float>& buffer);

	void updateReverb();
	void processReverb (AudioBuffer<float>& buffer);

	//==============================================================================
	AudioProcessorValueTreeState& getTreeState();
	MidiKeyboardState& getMidiState();

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
	// Inherited via Listener
	virtual void parameterChanged(const String & parameterID, float newValue) override;

	AudioProcessorValueTreeState treeState;
	MidiKeyboardState keyboardState;
	
	Synthesiser mySynth;
	TnpSynthVoice* mySynthVoice;
	Reverb reverb;
	Reverb::Parameters reverbParameters;
	IIRFilter filterLeft;
	IIRFilter filterRight;
	TnpStereoDelay delay;
	TnpLFO lfo;

	float targetGain, currentGain;
	float  targetFilterCutoff, currentFilterCutoff;
	int targetNumVoices;
    double localSampleRate;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TnpMidiSynthAudioProcessor)
};
