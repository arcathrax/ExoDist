/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ExoDistAudioProcessorEditor::ExoDistAudioProcessorEditor (ExoDistAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor(p),
        preGainSliderAttachment(audioProcessor.apvts, "PreGain", preGainSlider),
        scaleFactorSliderAttachment(audioProcessor.apvts, "ScaleFactor", scaleFactorSlider),
        maxThresholdSliderAttachment(audioProcessor.apvts, "MaxThreshold", maxThresholdSlider),
        cutoffSliderAttachment(audioProcessor.apvts, "Cutoff", cutoffSlider),
        thresholdSliderAttachment(audioProcessor.apvts, "Threshold", thresholdSlider),
        postGainSliderAttachment(audioProcessor.apvts, "PostGain", postGainSlider),
        mixSliderAttachment(audioProcessor.apvts, "Mix", mixSlider)
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
    g.fillAll (juce::Colour(BackgroundColor));
    
    // setup title label
    juce::FontOptions titleFontOptions = juce::FontOptions(50.f, juce::Font::bold);
    titleLabel.setFont(titleFontOptions);
    titleLabel.setText("ExoDist", juce::NotificationType::dontSendNotification);
    titleLabel.setColour(juce::Label::textColourId, juce::Colour(TitleColor));
    titleLabel.setJustificationType(juce::Justification::centred);
}

void ExoDistAudioProcessorEditor::resized()
{
    auto fullWindowSection = getLocalBounds();
}


std::vector<juce::Component*> ExoDistAudioProcessorEditor::getComps()
{
    return
    {
        &preGainSlider,
        &scaleFactorSlider,
        &maxThresholdSlider,
        &cutoffSlider,
        &thresholdSlider,
        &postGainSlider
    };
}
