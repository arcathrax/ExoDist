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
    for (auto* comp : getComps())
    {
        addAndMakeVisible(comp);
    }

    setSize (600, 400);
}

ExoDistAudioProcessorEditor::~ExoDistAudioProcessorEditor()
{
}

//==============================================================================
void ExoDistAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::ColourGradient gradient(
        juce::Colour(0xFFf6fcdf), 0, 0,
        juce::Colour(0xFFf6fcdf), 0, getHeight(),
        false
    );
    g.setGradientFill(gradient);
    g.fillAll();
}

void ExoDistAudioProcessorEditor::resized()
{
}


std::vector<juce::Component*> ExoDistAudioProcessorEditor::getComps()
{
    return
    {
    };
}
