/*
 ==============================================================================
 
 LFOParameters.cpp
 Created: 28 Nov 2024 11:55:30pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#include "LFOParameters.h"


// Constructor
LFOParameters::LFOParameters(const String& prefix)
: oscTypeID(prefix + "OscType"),
oscTypeChoices({"sine", "square", "triangle", "sawtooth"}),
oscTypeDefault(2),
depthID(prefix + "Depth"), depthRange(0.0f, 100.0f, 1.0f),
depthDefault(100.0f),
rateID(prefix + "Rate"),
rateRange(0.0f, 20.0f, 0.01f),
rateDefault(1.0f),
toggleID(prefix + "Toggle"),
toggleMin(0),
toggleMax(1),
toggleDefault(0)
{    
}

// Method to create and add parameters to the tree
void LFOParameters::addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const {
    layout.add(std::make_unique<AudioParameterChoice>(ParameterID(oscTypeID, 1), "LFO Oscillator Type", oscTypeChoices, oscTypeDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(depthID, 1), "LFO Depth", depthRange, depthDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(rateID, 1), "LFO Rate", rateRange, rateDefault));
    layout.add(std::make_unique<AudioParameterInt>(ParameterID(toggleID, 1), "LFO Toggle", toggleMin, toggleMax, toggleDefault));
}

