/*
  ==============================================================================

    VisualiserEditor.cpp
    Created: 1 Sep 2019 4:05:07pm
    Author:  Tiago Pestana

  ==============================================================================
*/

#include "VisualiserEditor.h"

VisualiserEditor::VisualiserEditor() : AudioVisualiserComponent(2)
{
    setBufferSize(512);
    setSamplesPerBlock(256);
}

VisualiserEditor::~VisualiserEditor()
{
    
}
