/*
 ==============================================================================
 
 ReverbParameters.cpp
 Created: 28 Nov 2024 11:55:40pm
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#include "ReverbParameters.h"

// Constructor to initialize Reverb parameters
ReverbParameters::ReverbParameters(const String& prefix)
: mixID(prefix + "Mix"),
mixRange(0.0f, 100.0f, 1.0f),
mixDefault(0.0f),
roomSizeID(prefix + "RoomSize"),
roomSizeRange(0.0f, 100.0f, 1.0f),
roomSizeDefault(20.0f),
dampingID(prefix + "Damping"),
dampingRange(0.0f, 100.0f, 1.0f),
dampingDefault(50.0f),
widthID(prefix + "Width"),
widthRange(0.0f, 100.0f, 1.0f),
widthDefault(50.0f),
toggleID(prefix + "Toggle"),
toggleMin(0),
toggleMax(1),
toggleDefault(0)
{
}

// Method to create and add parameters to the tree
void ReverbParameters::addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const {
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(mixID, 1), "Reverb Mix", mixRange, mixDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(roomSizeID, 1), "Reverb Room Size", roomSizeRange, roomSizeDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(dampingID, 1), "Reverb Damping", dampingRange, dampingDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(widthID, 1), "Reverb Width", widthRange, widthDefault));
    layout.add(std::make_unique<AudioParameterInt>(ParameterID(toggleID, 1), "Reverb Toggle", toggleMin, toggleMax, toggleDefault));
}

