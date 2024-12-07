/*
  ==============================================================================

    LFOParameters.h
    Created: 28 Nov 2024 11:55:30pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct LFOParameters {
    // Stored initialization values
    String oscTypeID;
    StringArray oscTypeChoices;
    int oscTypeDefault;

    String depthID;
    NormalisableRange<float> depthRange;
    float depthDefault;

    String rateID;
    NormalisableRange<float> rateRange;
    float rateDefault;

    String toggleID;
    int toggleMin;
    int toggleMax;
    int toggleDefault;

    // Constructor
    LFOParameters(const String& prefix);

    // Method to create and add parameters to the tree
    void addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const;
};
