/*
 ==============================================================================
 
 FilterParameters.cpp
 Created: 28 Nov 2024 7:50:49pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#include "FilterParameters.h"

// Constructor
FilterParameters::FilterParameters(const String& prefix)
: cutoffID(prefix + "Cutoff"),
cutoffRange(20.0f, 20000.0f, 0.01f),
cutoffDefault(1500.0f),
filterTypeID(prefix + "Type"),
filterTypeChoices({"lo-pass", "hi-pass", "band-pass", "notch", "lo-shelf", "hi-shelf", "peak"}),
filterTypeDefault(0),
qFactorID(prefix + "Q"),
qFactorRange(0.01f, 3.0f, 0.01f),
qFactorDefault(1.6f),
gainFactorID(prefix + "GainFactor"),
gainFactorRange(0.0f, 300.0f, 1.0f),
gainFactorDefault(50.0f),
toggleID(prefix + "Toggle"),
toggleMin(0),
toggleMax(1),
toggleDefault(1)
{
}

// Method to create and add parameters to the tree
void FilterParameters::addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const {
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(cutoffID, 1), "Filter Cutoff", cutoffRange, cutoffDefault));
    layout.add(std::make_unique<AudioParameterChoice>(ParameterID(filterTypeID, 1), "Filter Type", filterTypeChoices, filterTypeDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(qFactorID, 1), "Filter Q", qFactorRange, qFactorDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(gainFactorID, 1), "Filter Gain Factor", gainFactorRange, gainFactorDefault));
    layout.add(std::make_unique<AudioParameterInt>(ParameterID(toggleID, 1), "Filter Toggle", toggleMin, toggleMax, toggleDefault));
}

