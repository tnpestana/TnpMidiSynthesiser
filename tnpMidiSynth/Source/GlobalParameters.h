/*
  ==============================================================================

    GlobalParameters.h
    Created: 28 Nov 2024 7:50:38pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct GlobalParameters {
    // Parameter values
    std::string gainID;
    NormalisableRange<float> gainRange;
    float gainDefault;

    std::string numVoicesID;
    StringArray numVoicesChoices;
    int numVoicesDefault;
    
    // Constructor
    GlobalParameters();

    // Method to create and add parameters to the tree
    void addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const;
};
