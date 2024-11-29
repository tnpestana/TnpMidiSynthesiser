/*
  ==============================================================================

    FilterParameters.h
    Created: 28 Nov 2024 7:50:49pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct FilterParameters {
    // Stored initialization values
    String cutoffID;
    NormalisableRange<float> cutoffRange;
    float cutoffDefault;

    String filterTypeID;
    StringArray filterTypeChoices;
    int filterTypeDefault;

    String qFactorID;
    NormalisableRange<float> qFactorRange;
    float qFactorDefault;

    String gainFactorID;
    NormalisableRange<float> gainFactorRange;
    float gainFactorDefault;

    String toggleID;
    int toggleMin;
    int toggleMax;
    int toggleDefault;

    // Constructor
    FilterParameters(const String& prefix);

    // Method to create and add parameters to the tree
    void addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const;
};
