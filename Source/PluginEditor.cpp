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
        comp->setLookAndFeel(&exoLookAndFeel);
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
    g.fillAll(juce::Colour(0xFF1a1a19));
}
void ExoDistAudioProcessorEditor::resized()
{
    auto fullBounds = getBounds();
    
    auto titleSection = fullBounds.removeFromTop(fullBounds.getHeight()*0.23);
    auto contentSection = fullBounds.removeFromTop(fullBounds.getHeight()*0.85);
    auto bottomSection = fullBounds;
    
    auto knobsSection = contentSection.removeFromLeft(contentSection.getWidth() * 0.33);
    auto visualisationSection = contentSection.removeFromRight(contentSection.getWidth());

    auto topKnobsSection = knobsSection.removeFromTop(knobsSection.getHeight()*0.5);
    auto bottomKnobsSection = knobsSection;

    auto topLeftKnobsSection = topKnobsSection.removeFromLeft(topKnobsSection.getWidth() * 0.5);
    auto topRightKnobsSection = topKnobsSection;

    hardnessSlider.setBounds(topLeftKnobsSection);
    preGainSlider.setBounds(bottomKnobsSection);
    thresholdSlider.setBounds(topRightKnobsSection);
    
    titleComponent.setBounds(titleSection);
    footerComponent.setBounds(bottomSection);
}


std::vector<juce::Component*> ExoDistAudioProcessorEditor::getComps()
{
    return
    {
        &preGainSlider,
        &hardnessSlider,
        &thresholdSlider,
        &titleComponent,
        &footerComponent
    };
}
