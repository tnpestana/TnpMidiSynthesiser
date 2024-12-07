/*
 ==============================================================================
 
 DistortionParameters.cpp
 Created: 28 Nov 2024 11:55:53pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#include "DistortionParameters.h"

// Constructor
DistortionParameters::DistortionParameters(const String& prefix)
: toggleID(prefix + "Toggle"),
toggleMin(0),
toggleMax(1),
toggleDefault(0),
gainID(prefix + "Gain"),
gainRange(-48.0f, 6.0f, 0.1f),
gainDefault(0.0f),
typeID(prefix + "Type"),
typeChoices({"Soft Clipping", "Hard Clipping", "Soft Clipping Exponential", "Full Wave Rectifier", "Half Wave Rectifier"}),
typeDefault(0),
mixID(prefix + "Mix"),
mixRange(0.0f, 100.0f, 1.0f),
mixDefault(0.0f)
{
}

// Method to create and add parameters to the tree
void DistortionParameters::addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const {
    layout.add(std::make_unique<AudioParameterInt>(ParameterID(toggleID, 1), "Distortion Toggle", toggleMin, toggleMax, toggleDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(gainID, 1), "Input Gain", gainRange, gainDefault));
    layout.add(std::make_unique<AudioParameterChoice>(ParameterID(typeID, 1), "Distortion Type", typeChoices, typeDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(mixID, 1), "Distortion Mix", mixRange, mixDefault));
}

