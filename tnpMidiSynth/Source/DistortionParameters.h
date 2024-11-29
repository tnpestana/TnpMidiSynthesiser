/*
  ==============================================================================

    DistortionParameters.h
    Created: 28 Nov 2024 11:55:53pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct DistortionParameters {
    // Stored initialization values
    String toggleID;
    int toggleMin;
    int toggleMax;
    int toggleDefault;

    String gainID;
    NormalisableRange<float> gainRange;
    float gainDefault;

    String typeID;
    StringArray typeChoices;
    int typeDefault;

    String mixID;
    NormalisableRange<float> mixRange;
    float mixDefault;

    // Constructor
    DistortionParameters(const String& prefix);

    // Method to create and add parameters to the tree
    void addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const;
};
