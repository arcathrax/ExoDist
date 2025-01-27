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
    
    // setup description labels
    juce::FontOptions descriptionFontOptions = juce::FontOptions(15.f, juce::Font::plain);
    authorLabel.setFont(descriptionFontOptions);
    preGainLabel.setFont(descriptionFontOptions);
    scaleFactorLabel.setFont(descriptionFontOptions);
    maxThresholdLabel.setFont(descriptionFontOptions);
    cutoffLabel.setFont(descriptionFontOptions);
    thresholdLabel.setFont(descriptionFontOptions);
    postGainLabel.setFont(descriptionFontOptions);
    mixLabel.setFont(descriptionFontOptions);
    
    authorLabel.setText("by arcathrax", juce::NotificationType::dontSendNotification);
    preGainLabel.setText("pregain", juce::NotificationType::dontSendNotification);
    scaleFactorLabel.setText("scalefactor", juce::NotificationType::dontSendNotification);
    maxThresholdLabel.setText("maxthreshold", juce::NotificationType::dontSendNotification);
    cutoffLabel.setText("cutoff", juce::NotificationType::dontSendNotification);
    thresholdLabel.setText("threshold", juce::NotificationType::dontSendNotification);
    postGainLabel.setText("postgain", juce::NotificationType::dontSendNotification);
    mixLabel.setText("mix", juce::NotificationType::dontSendNotification);
    
    authorLabel.setColour(juce::Label::textColourId, juce::Colour(TitleColor));
    preGainLabel.setColour(juce::Label::textColourId, juce::Colour(TitleColor));
    scaleFactorLabel.setColour(juce::Label::textColourId, juce::Colour(TitleColor));
    maxThresholdLabel.setColour(juce::Label::textColourId, juce::Colour(TitleColor));
    cutoffLabel.setColour(juce::Label::textColourId, juce::Colour(TitleColor));
    thresholdLabel.setColour(juce::Label::textColourId, juce::Colour(TitleColor));
    postGainLabel.setColour(juce::Label::textColourId, juce::Colour(TitleColor));
    mixLabel.setColour(juce::Label::textColourId, juce::Colour(TitleColor));
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
