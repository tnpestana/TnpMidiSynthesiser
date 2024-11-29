/*
  ==============================================================================

    OscillatorParameters.h
    Created: 28 Nov 2024 7:50:23pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct OscillatorParameters {
    String typeID;
    StringArray typeChoices;
    int typeDefault;
    
    String transposeID;
    int transposeMin;
    int transposeMax;
    int transposeDefault;
    
    String attackID;
    NormalisableRange<float> attackRange;
    float attackDefault;
    
    String decayID;
    NormalisableRange<float> decayRange;
    float decayDefault;
    
    String sustainID;
    NormalisableRange<float> sustainRange;
    float sustainDefault;
    
    String releaseID;
    NormalisableRange<float> releaseRange;
    float releaseDefault;
    
    String toggleID;
    int toggleMin;
    int toggleMax;
    int toggleDefault;
    
    // Constructor
    OscillatorParameters(const String& oscPrefix);
    
    // Method to create the actual AudioParameters
    void addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const;
};
