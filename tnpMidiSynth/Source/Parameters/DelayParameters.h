/*
  ==============================================================================

    DelayParameters.h
    Created: 29 Nov 2024 12:04:09am
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct DelayParameters {
    // Stored initialization values
    String timeID;
    NormalisableRange<float> timeRange;
    float timeDefault;

    String feedbackID;
    NormalisableRange<float> feedbackRange;
    float feedbackDefault;

    String mixID;
    NormalisableRange<float> mixRange;
    float mixDefault;

    String toggleID;
    int toggleMin;
    int toggleMax;
    int toggleDefault;

    // Constructor
    DelayParameters(const String& prefix);

    // Method to create and add parameters to the tree
    void addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const;
};
