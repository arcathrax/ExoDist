/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ExoDistAudioProcessorEditor::ExoDistAudioProcessorEditor(ExoDistAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p),
    preGainSliderAttachment(audioProcessor.apvts, "PreGain", preGainSlider),
    hardnessSliderAttachment(audioProcessor.apvts, "Hardness", hardnessSlider),
    thresholdSliderAttachment(audioProcessor.apvts, "Threshold", thresholdSlider)
{
    // Slider hinzufügen
    for (auto* comp : getComps())
    {
        addAndMakeVisible(comp);
    }

    setSize(600, 400);
}

ExoDistAudioProcessorEditor::~ExoDistAudioProcessorEditor()
{
    auto bounds = getLocalBounds();
    preGainSlider.setBounds(bounds);
}

//==============================================================================
void ExoDistAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(BackgroundColor));
}
void ExoDistAudioProcessorEditor::resized()
{
    auto fullBounds = getBounds();
    
    auto titleSection = fullBounds.removeFromTop(fullBounds.getHeight()*0.23);
    auto knobsSection = fullBounds.removeFromTop(fullBounds.getHeight()*0.85);
    auto bottomSection = fullBounds;
    
    auto leftPart = knobsSection.removeFromLeft(knobsSection.getWidth() * 0.25);
    auto rightPart = knobsSection.removeFromRight(knobsSection.getWidth() * 0.33);
    auto middlePart = knobsSection;

    hardnessSlider.setBounds(leftPart);
    preGainSlider.setBounds(middlePart);
    thresholdSlider.setBounds(rightPart);
}


std::vector<juce::Component*> ExoDistAudioProcessorEditor::getComps()
{
    return
    {
        &preGainSlider,
        &hardnessSlider,
        &thresholdSlider
    };
}
