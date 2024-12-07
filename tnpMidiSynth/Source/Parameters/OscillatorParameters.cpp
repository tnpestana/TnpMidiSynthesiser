/*
  ==============================================================================

    OscillatorParameters.cpp
    Created: 28 Nov 2024 7:50:23pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "OscillatorParameters.h"

// Constructor
OscillatorParameters::OscillatorParameters(const String& prefix)
: typeID(prefix + "Type"),
typeChoices({"sine", "harmonic", "square", "triangle", "sawtooth"}),
typeDefault(2),
transposeID(prefix + "Transpose"),
transposeMin(-24),
transposeMax(24),
transposeDefault(0),
attackID(prefix + "Attack"),
attackRange(1.0f, 5000.0f, 1.0f),
attackDefault(50.0f),
decayID(prefix + "Decay"),
decayRange(1.0f, 5000.0f, 1.0f),
decayDefault(50.0f),
sustainID(prefix + "Sustain"),
sustainRange(0.0f, 100.0f, 1.0f),
sustainDefault(5.0f),
releaseID(prefix + "Release"),
releaseRange(1.0f, 5000.0f, 1.0f),
releaseDefault(50.0f),
toggleID(prefix + "Toggle"),
toggleMin(0),
toggleMax(1),
toggleDefault(0)
{
}

// Method to create the actual AudioParameters
void OscillatorParameters::addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const {
    layout.add(std::make_unique<AudioParameterChoice>(ParameterID { typeID, 1 }, "Oscillator Type", typeChoices, typeDefault));
    layout.add(std::make_unique<AudioParameterInt>(ParameterID { transposeID, 1 }, "Transpose", transposeMin, transposeMax, transposeDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID { attackID, 1 }, "Volume Envelope Attack", attackRange, attackDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID { decayID, 1 }, "Volume Envelope Decay", decayRange, decayDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID { sustainID, 1 }, "Volume Envelope Sustain", sustainRange, sustainDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID { releaseID, 1 }, "Volume Envelope Release", releaseRange, releaseDefault));
    layout.add(std::make_unique<AudioParameterInt>(ParameterID { toggleID,  1 }, "Oscillator Toggle", toggleMin, toggleMax, toggleDefault));
}

