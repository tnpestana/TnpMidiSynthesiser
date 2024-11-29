/*
  ==============================================================================

    ReverbParameters.h
    Created: 28 Nov 2024 11:55:40pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct ReverbParameters {
    // Stored initialization values
    String mixID;
    NormalisableRange<float> mixRange;
    float mixDefault;

    String roomSizeID;
    NormalisableRange<float> roomSizeRange;
    float roomSizeDefault;

    String dampingID;
    NormalisableRange<float> dampingRange;
    float dampingDefault;

    String widthID;
    NormalisableRange<float> widthRange;
    float widthDefault;

    String toggleID;
    int toggleMin;
    int toggleMax;
    int toggleDefault;

    // Constructor
    ReverbParameters(const String& prefix);

    // Method to create and add parameters to the tree
    void addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const;
};
