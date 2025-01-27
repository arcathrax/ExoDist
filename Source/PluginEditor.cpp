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
    titleLabel.setJustificationType(juce::Justification::left);
    
    addAndMakeVisible(titleLabel);
    
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
    
    authorLabel.setColour(juce::Label::textColourId, juce::Colour(ContentColor));
    preGainLabel.setColour(juce::Label::textColourId, juce::Colour(ContentColor));
    scaleFactorLabel.setColour(juce::Label::textColourId, juce::Colour(ContentColor));
    maxThresholdLabel.setColour(juce::Label::textColourId, juce::Colour(ContentColor));
    cutoffLabel.setColour(juce::Label::textColourId, juce::Colour(ContentColor));
    thresholdLabel.setColour(juce::Label::textColourId, juce::Colour(ContentColor));
    postGainLabel.setColour(juce::Label::textColourId, juce::Colour(ContentColor));
    mixLabel.setColour(juce::Label::textColourId, juce::Colour(ContentColor));
    fftLabel.setColour(juce::Label::backgroundColourId, juce::Colour(HighlightColor));
    
    preGainLabel.setJustificationType(juce::Justification::centred);
    scaleFactorLabel.setJustificationType(juce::Justification::centred);
    maxThresholdLabel.setJustificationType(juce::Justification::centred);
    cutoffLabel.setJustificationType(juce::Justification::centred);
    thresholdLabel.setJustificationType(juce::Justification::centred);
    postGainLabel.setJustificationType(juce::Justification::centred);
    mixLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(authorLabel);
    addAndMakeVisible(preGainLabel);
    addAndMakeVisible(scaleFactorLabel);
    addAndMakeVisible(maxThresholdLabel);
    addAndMakeVisible(cutoffLabel);
    addAndMakeVisible(thresholdLabel);
    addAndMakeVisible(postGainLabel);
    addAndMakeVisible(mixLabel);
    
    addAndMakeVisible(fftLabel);
}

void ExoDistAudioProcessorEditor::resized()
{
    auto fullWindowSection = getLocalBounds();
    
    // setup main sections
    auto titleSection = fullWindowSection.removeFromTop(fullWindowSection.getHeight()*0.2);
    auto fftSection = fullWindowSection.removeFromTop(fullWindowSection.getHeight()*0.070);
    auto parameterSection = fullWindowSection.removeFromBottom(fullWindowSection.getHeight());
    
    // setup title/postgain section
    auto titleLabelSection = titleSection.removeFromTop(titleSection.getHeight()*0.85);
    
    auto postGainSection = titleLabelSection.removeFromRight(titleSection.getWidth()*0.15);
    auto postGainSliderSection = postGainSection.removeFromTop(postGainSection.getHeight()*0.85);
    
    const int preGainSliderSectionMargin = 10;
       postGainSliderSection = postGainSliderSection.withTrimmedLeft(preGainSliderSectionMargin).withTrimmedTop(preGainSliderSectionMargin);
    
    // auto postGainLabelSection = postGainSection;
    auto authorLabelSection = titleSection;
    titleLabel.setBounds(titleLabelSection);
    authorLabel.setBounds(authorLabelSection);
    
    postGainSlider.setBounds(postGainSliderSection);
    // postGainLabel.setBounds(postGainLabelSection);
    
    // setup fft section
    const int fftSectionMargin = 10;
    fftSection = fftSection.withTrimmedLeft(fftSectionMargin).withTrimmedRight(fftSectionMargin).withTrimmedTop(fftSectionMargin).withTrimmedBottom(fftSectionMargin);
    fftLabel.setBounds(fftSection);
    
    auto leftParametersSection = parameterSection.removeFromLeft(parameterSection.getWidth()*0.33);
    auto middleParametersSection = parameterSection.removeFromLeft(parameterSection.getWidth()*0.50);
    auto rightParametersSection = parameterSection;
    
    // setup left parameters
    
    // setup scaleFactorSlider
    auto scaleFactorSection = leftParametersSection.removeFromTop(leftParametersSection.getHeight()*0.5);
    auto scaleFactorSliderSection = scaleFactorSection.removeFromTop(scaleFactorSection.getHeight()*0.85);
    auto scaleFactorLabelSection = scaleFactorSection;
    scaleFactorSlider.setBounds(scaleFactorSliderSection);
    scaleFactorLabel.setBounds(scaleFactorLabelSection);
    
    // setup maxThresholdSlider
    auto maxThresholdSection = leftParametersSection;
    auto maxThresholdSliderSection = maxThresholdSection.removeFromTop(maxThresholdSection.getHeight()*0.85);
    auto maxThresholdLabelSection = maxThresholdSection;
    maxThresholdSlider.setBounds(maxThresholdSliderSection);
    maxThresholdLabel.setBounds(maxThresholdLabelSection);
    
    // setup middle parameters
    auto preGainSliderSection = middleParametersSection.removeFromTop(middleParametersSection.getHeight()*0.85);
    auto preGainLabelSection = middleParametersSection;
    preGainSlider.setBounds(preGainSliderSection);
    preGainLabel.setBounds(preGainLabelSection);
    
    // setup right parameters
    
    // setup cutoffSlider
    auto cutoffSection = rightParametersSection.removeFromTop(rightParametersSection.getHeight()*0.5);
    auto cutoffSliderSection = cutoffSection.removeFromTop(cutoffSection.getHeight()*0.85);
    auto cutoffLabelSection = cutoffSection;
    cutoffSlider.setBounds(cutoffSliderSection);
    cutoffLabel.setBounds(cutoffLabelSection);
    
    // setup thresholdSlider
    auto thresholdSection = rightParametersSection;
    auto thresholdSliderSection = rightParametersSection.removeFromTop(thresholdSection.getHeight()*0.85);
    auto thresholdLabelSection = rightParametersSection;
    thresholdSlider.setBounds(thresholdSliderSection);
    thresholdLabel.setBounds(thresholdLabelSection);
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
