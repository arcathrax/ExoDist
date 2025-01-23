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
    gainSliderAttachment(audioProcessor.apvts, "Gain", gainSlider),
    cutoffSliderAttachment(audioProcessor.apvts, "Cutoff", cutoffSlider),
    resonanceSliderAttachment(audioProcessor.apvts, "Resonance", resonanceSlider),
    thresholdSliderAttachment(audioProcessor.apvts, "Threshold", thresholdSlider),
    releaseSliderAttachment(audioProcessor.apvts, "Release", releaseSlider)
{
    for (auto* comp : getComps())
    {
        addAndMakeVisible(comp);
    }

    addAndMakeVisible(titleLabel);

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

    titleLabel.setFont(juce::Font(getY()*1.5, juce::Font::bold));
    titleLabel.setText("ExoDist", juce::NotificationType::dontSendNotification);
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::lightgreen);
    titleLabel.setJustificationType(juce::Justification::centred);
}

void ExoDistAudioProcessorEditor::resized()
{
    auto fullWindowSection = getLocalBounds();

    auto titleSection = fullWindowSection.removeFromTop(fullWindowSection.getHeight() * 0.15);

    auto effectsSection = fullWindowSection.removeFromTop(fullWindowSection.getHeight());

    auto gainSection = effectsSection.removeFromLeft(effectsSection.getWidth() * 0.5);

    auto filterSection = effectsSection.removeFromLeft(effectsSection.getWidth() * 0.5);
    auto cutoffSection = filterSection.removeFromTop(filterSection.getHeight() * 0.5);
    auto resonanceSection = filterSection.removeFromTop(filterSection.getHeight());

    auto limiterSection = effectsSection.removeFromLeft(effectsSection.getWidth());
    auto thresholdSection = limiterSection.removeFromTop(limiterSection.getHeight() * 0.5);
    auto releaseSection = limiterSection.removeFromTop(limiterSection.getHeight());

    titleLabel.setBounds(titleSection);
    gainSlider.setBounds(gainSection);

    cutoffSlider.setBounds(cutoffSection);
    resonanceSlider.setBounds(resonanceSection);

    thresholdSlider.setBounds(thresholdSection);
    releaseSlider.setBounds(releaseSection);
}


std::vector<juce::Component*> ExoDistAudioProcessorEditor::getComps()
{
    return
    {
        &gainSlider,
        &cutoffSlider,
        &resonanceSlider,
        &thresholdSlider,
        &releaseSlider,
    };
}