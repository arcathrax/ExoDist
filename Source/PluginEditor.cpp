/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ExoDistAudioProcessorEditor::ExoDistAudioProcessorEditor (ExoDistAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor(p)
{
    setSize (650, 380);
}

ExoDistAudioProcessorEditor::~ExoDistAudioProcessorEditor()
{
}

//==============================================================================
void ExoDistAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
}

void ExoDistAudioProcessorEditor::resized()
{
}