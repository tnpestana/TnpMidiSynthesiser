/*
  ==============================================================================

    TnpDistortion.h
    Created: 11 Aug 2019 6:22:42pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TnpDistortion
{
public:
    TnpDistortion();
    ~TnpDistortion();

    void prepareToPLay(double sampleRate);
    void processAudioBlock(AudioBuffer<float>& buffer);

private:
};
