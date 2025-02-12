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
    
    setSize(500, 400);
    startTimerHz(20);
    setAlwaysOnTop(false);

    preGainLabel.setText("pregain", juce::NotificationType::sendNotification);
    preGainLabel.setJustificationType(juce::Justification::centred);
    preGainLabel.setFont(juce::FontOptions(20.0f));

    hardnessLabel.setText("hardness", juce::NotificationType::sendNotification);
    hardnessLabel.setJustificationType(juce::Justification::centred);

    thresholdLabel.setText("threshold", juce::NotificationType::sendNotification);
    thresholdLabel.setJustificationType(juce::Justification::centred);
}

ExoDistAudioProcessorEditor::~ExoDistAudioProcessorEditor()
{
    auto bounds = getLocalBounds();
    preGainSlider.setBounds(bounds);
}

void ExoDistAudioProcessorEditor::timerCallback()
{
    verticalMeterLeft.setLevel(audioProcessor.getRmsValue(0));
    verticalMeterRight.setLevel(audioProcessor.getRmsValue(1));

    verticalMeterLeft.repaint();
    verticalMeterRight.repaint();
}

//==============================================================================
void ExoDistAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xFF1a1a19));
}
void ExoDistAudioProcessorEditor::resized()
{
    auto fullBounds = getBounds();
        auto titleSection = fullBounds.removeFromTop(fullBounds.getHeight()*0.15);
        auto contentSection = fullBounds.removeFromTop(fullBounds.getHeight()*0.95);
        auto bottomSection = fullBounds;
    
            auto knobsSection = contentSection.removeFromLeft(contentSection.getWidth() * 0.85);
                auto preGainSection = knobsSection.removeFromLeft(knobsSection.getWidth() * 0.50);
                    auto preGainSliderSection = preGainSection.removeFromTop(preGainSection.getHeight()*0.75);
                    auto preGainLabelSection = preGainSection;

                auto hardnessSection = knobsSection.removeFromTop(knobsSection.getHeight()*0.5);
                    auto hardnessSliderSection = hardnessSection.removeFromTop(hardnessSection.getHeight()*0.75);
                    auto hardnessLabelSection = hardnessSection;

                auto thresholdSection = knobsSection;
                    auto thresholdSliderSection = thresholdSection.removeFromTop(thresholdSection.getHeight() * 0.75);
                    auto thresholdLabelSection = thresholdSection;

    auto visualisationSection = contentSection.removeFromRight(contentSection.getWidth());
    auto verticalMeterLeftSection = visualisationSection.removeFromLeft(visualisationSection.getWidth()*0.5).reduced(10.f);
    auto verticalMeterRightSection = visualisationSection.reduced(10.f);

    preGainSlider.setBounds(preGainSliderSection);
    hardnessSlider.setBounds(hardnessSliderSection);
    thresholdSlider.setBounds(thresholdSliderSection);

    preGainLabel.setBounds(preGainLabelSection);
    hardnessLabel.setBounds(hardnessLabelSection);
    thresholdLabel.setBounds(thresholdLabelSection);

    
    titleComponent.setBounds(titleSection);
    footerComponent.setBounds(bottomSection);

    verticalMeterLeft.setBounds(verticalMeterLeftSection);
    verticalMeterRight.setBounds(verticalMeterRightSection);
}


std::vector<juce::Component*> ExoDistAudioProcessorEditor::getComps()
{
    return
    {
        &preGainSlider,
        &hardnessSlider,
        &thresholdSlider,

        &preGainLabel,
        &hardnessLabel,
        &thresholdLabel,

        &titleComponent,
        &footerComponent,

        &verticalMeterLeft,
        &verticalMeterRight
    };
}
