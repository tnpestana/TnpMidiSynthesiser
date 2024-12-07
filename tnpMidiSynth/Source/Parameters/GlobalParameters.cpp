/*
  ==============================================================================

    GlobalParameters.cpp
    Created: 28 Nov 2024 7:50:38pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "GlobalParameters.h"

// Constructor
GlobalParameters::GlobalParameters()
: gainID("gain"),
gainRange(-48.0f, 6.0f, 0.1f), gainDefault(0.0f),
numVoicesID("numVoices"),
numVoicesChoices({"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "16", "32"}),
numVoicesDefault(11)
{
}

// Method to create and add parameters to the tree
void GlobalParameters::addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const {
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID { gainID, 1 }, "Master Gain", gainRange, gainDefault));
    layout.add(std::make_unique<AudioParameterChoice>(ParameterID { numVoicesID, 1 }, "Number of Voices", numVoicesChoices, numVoicesDefault));
}
