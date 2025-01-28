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
    // Hintergrund
    juce::ColourGradient gradient(
        juce::Colour(HighlightColor), getWidth() / 2.0f, getHeight() / 2.0f,
        juce::Colour(TitleColor), 0, 0, true
    );

    g.setGradientFill(gradient);
    g.fillAll();
}
void ExoDistAudioProcessorEditor::resized()
{
    auto fullBounds = getBounds();
    auto leftPart = fullBounds.removeFromLeft(fullBounds.getWidth() * 0.33);
    auto rightPart = fullBounds.removeFromRight(fullBounds.getWidth() * 0.5);
    auto middlePart = fullBounds;

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
