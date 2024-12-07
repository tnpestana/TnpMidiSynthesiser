/*
 ==============================================================================
 
 DelayParameters.cpp
 Created: 29 Nov 2024 12:04:09am
 Author:  Tiago Pestana
 
 ==============================================================================
 */

#include "DelayParameters.h"

// Constructor
DelayParameters::DelayParameters(const String& prefix)
: timeID(prefix + "Time"),
timeRange(0.0f, 2000.0f, 1.0f),
timeDefault(800.0f),
feedbackID(prefix + "Feedback"),
feedbackRange(0.0f, 100.0f, 1.0f),
feedbackDefault(20.0f),
mixID(prefix + "Mix"),
mixRange(0.0f, 100.0f, 1.0f),
mixDefault(20.0f),
toggleID(prefix + "Toggle"),
toggleMin(0),
toggleMax(1),
toggleDefault(1)
{
}

// Method to create and add parameters to the tree
void DelayParameters::addToParameterTree(AudioProcessorValueTreeState::ParameterLayout& layout) const {
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(timeID, 1), "Delay Time", timeRange, timeDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(feedbackID, 1), "Delay Feedback", feedbackRange, feedbackDefault));
    layout.add(std::make_unique<AudioParameterFloat>(ParameterID(mixID, 1), "Delay Mix", mixRange, mixDefault));
    layout.add(std::make_unique<AudioParameterInt>(ParameterID(toggleID, 1), "Delay Toggle", toggleMin, toggleMax, toggleDefault));
}

