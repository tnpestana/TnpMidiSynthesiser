/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */
#include "../Processors/PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TnpMidiSynthAudioProcessorEditor::TnpMidiSynthAudioProcessorEditor (TnpMidiSynthAudioProcessor& p)
: AudioProcessorEditor (&p),
//	Processor references
processor (p),
treeState(p.getTreeState()),
midiState (p.getMidiState()),
visualiser(p.getVisualiserState()),
midiKeyboard(p.getMidiState() , MidiKeyboardComponent::horizontalKeyboard),
//	Editor components
masterGUI(p),
oscillator1GUI(p, 1),
oscillator2GUI(p, 2),
filterGUI(p),
lfoGUI(p),
delayGUI(p),
reverbGUI(p),
distortionGUI(p)
{
    // Main editor's size.
    setSize(800, 580);
    setLookAndFeel(&tnpLookAndFeel);
    setResizable(false, false);
    
    backgroundImage = ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);
    
    addAndMakeVisible(masterGUI);
    addAndMakeVisible(oscillator1GUI);
    addAndMakeVisible(oscillator2GUI);
    addAndMakeVisible(filterGUI);
    addAndMakeVisible(lfoGUI);
    addAndMakeVisible(reverbGUI);
    addAndMakeVisible(delayGUI);
    addAndMakeVisible(distortionGUI);
    addAndMakeVisible(midiKeyboard);
    addAndMakeVisible(visualiser);
    
    midiKeyboard.setLowestVisibleKey(36);
}

TnpMidiSynthAudioProcessorEditor::~TnpMidiSynthAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//=============================================================================
void TnpMidiSynthAudioProcessorEditor::paint (Graphics& g)
{
    Colour mainColor = Colours::darkseagreen;
    Colour secondaryColor = Colours::darkseagreen;
    Colour outlineColor = Colours::black;
    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (mainColor);
    
    LookAndFeel& lookAndFeel = getLookAndFeel();
    
    lookAndFeel.setColour(Slider::textBoxBackgroundColourId, mainColor);    // doesnt work?
    lookAndFeel.setColour(Slider::rotarySliderFillColourId, secondaryColor);
    lookAndFeel.setColour(Slider::thumbColourId, outlineColor);
    lookAndFeel.setColour(Slider::rotarySliderOutlineColourId, outlineColor);
    
    // Color scheme for properties that always remain the same.
    lookAndFeel.setColour(Slider::backgroundColourId, mainColor);
    lookAndFeel.setColour(Slider::ColourIds::trackColourId, secondaryColor);
    lookAndFeel.setColour(Slider::textBoxTextColourId, outlineColor);
    lookAndFeel.setColour(Slider::textBoxOutlineColourId, mainColor);
    
    lookAndFeel.setColour(ComboBox::textColourId, outlineColor);
    lookAndFeel.setColour(ComboBox::backgroundColourId, mainColor);
    lookAndFeel.setColour(ComboBox::outlineColourId, mainColor);
    lookAndFeel.setColour(ComboBox::arrowColourId, mainColor);
    
    lookAndFeel.setColour(PopupMenu::backgroundColourId, mainColor);
    lookAndFeel.setColour(PopupMenu::textColourId, outlineColor);
    
    lookAndFeel.setColour(Label::textColourId, outlineColor);
    lookAndFeel.setColour(Label::outlineColourId, mainColor);
    
    lookAndFeel.setColour(ToggleButton::tickColourId, outlineColor);
    lookAndFeel.setColour(ToggleButton::tickDisabledColourId, mainColor);
    
    lookAndFeel.setColour(TextButton::buttonColourId, secondaryColor);
    lookAndFeel.setColour(TextButton::textColourOffId, outlineColor);
    
    midiKeyboard.setWantsKeyboardFocus(true);
    midiKeyboard.grabKeyboardFocus();
}

void TnpMidiSynthAudioProcessorEditor::resized()
{
    // Total main editor's area.
    juce::Rectangle<int> area (getLocalBounds());
    
    // MIDI keyboard area.
    midiKeyboard.setBounds(area.removeFromBottom(100).reduced(5));
    
    juce::Rectangle<int> left (area.removeFromLeft(area.getWidth() / 3));
    juce::Rectangle<int> center (area.removeFromLeft(area.getWidth() / 2));
    juce::Rectangle<int> right (area);
    
    // Oscillator area.
    oscillator1GUI.setBounds(left.removeFromTop(180).reduced(5));
    oscillator2GUI.setBounds(center.removeFromTop(180).reduced(5));
    
    // IRRFilter area.
    filterGUI.setBounds(left.removeFromTop(170).reduced(5));
    
    // Distortion area.
    lfoGUI.setBounds((center.removeFromTop(170).reduced(5)));
    
    // Delay area.
    delayGUI.setBounds(center.reduced(5));
    
    // Reverb area.
    reverbGUI.setBounds(left.reduced(5));
    
    // Master area.
    masterGUI.setBounds(right.removeFromTop(180).reduced(5));
    
    // Distortion area.
    distortionGUI.setBounds(right.removeFromTop(170).reduced(5));
    
    // Visualiser area.
    visualiser.setBounds(right.reduced(10));
}
