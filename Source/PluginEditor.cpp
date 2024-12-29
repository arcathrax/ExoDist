/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ExoDistAudioProcessorEditor::ExoDistAudioProcessorEditor (ExoDistAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    preGainSliderAttachment(audioProcessor.apvts, "Pre Gain", preGainSlider),
    tresholdValueSliderAttachment(audioProcessor.apvts, "Treshold", tresholdValueSlider),
    hardnessValueSliderAttachment(audioProcessor.apvts, "Hardness", hardnessValueSlider),
    postGainSliderAttachment(audioProcessor.apvts, "Post Gain", postGainSlider)
{
    preGainSlider.setTooltip("Pre Gain Knob");
    preGainLabel.setText("Pre Gain", juce::dontSendNotification);
    preGainLabel.setJustificationType(juce::Justification::centred);

    tresholdValueSlider.setTooltip("Treshold Knob");
    tresholdLabel.setText("Treshold", juce::dontSendNotification);
    tresholdLabel.setJustificationType(juce::Justification::centred);

    hardnessValueSlider.setTooltip("Hardness Knob");
    hardnessLabel.setText("Hardness", juce::dontSendNotification);
    hardnessLabel.setJustificationType(juce::Justification::centred);

    postGainSlider.setTooltip("Post Gain Knob");
    postGainLabel.setText("Post Gain", juce::dontSendNotification);
    postGainLabel.setJustificationType(juce::Justification::centred);

    title.setText("ExoDist", juce::dontSendNotification);
    title.setJustificationType(juce::Justification::centred);

    for (auto* comp : getComps())
    {
        addAndMakeVisible(comp);
    }

    setResizeLimits(500, 300, 800, 550);
    setSize (650, 380);
    setResizable(true, true);
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
    auto originalBounds = getLocalBounds();
    auto bounds = getLocalBounds();
    auto mainBounds = bounds.removeFromBottom(bounds.getHeight()*0.80);

    fontSizeS = originalBounds.getHeight() / 30;
    fontSizeM = originalBounds.getHeight() / 20;
    fontSizeL = originalBounds.getHeight() / 7;

    preGainLabel.setFont(juce::Font(fontSizeS));
    tresholdLabel.setFont(juce::Font(fontSizeM));
    hardnessLabel.setFont(juce::Font(fontSizeM));
    postGainLabel.setFont(juce::Font(fontSizeS));
    title.setFont(juce::Font(fontSizeL));

    auto gainArea = mainBounds.removeFromLeft(mainBounds.getWidth() * 0.25);
    auto clipperArea = mainBounds.removeFromRight(mainBounds.getWidth());
    auto tresholdArea = clipperArea.removeFromRight(clipperArea.getWidth()*0.5);
    auto hardnessArea = clipperArea.removeFromRight(clipperArea.getWidth());
    auto preGainArea = gainArea.removeFromBottom(gainArea.getHeight() * 0.5);
    auto postGainArea = gainArea.removeFromTop(gainArea.getHeight());

    preGainLabel.setVisible(true);
    tresholdValueSlider.setVisible(true);
    tresholdLabel.setVisible(true);
    hardnessValueSlider.setVisible(true);
    hardnessLabel.setVisible(true);
    postGainLabel.setVisible(true);

    title.setBounds(bounds);
    if (originalBounds.getHeight()<325)
    {
        preGainLabel.setVisible(false);
        tresholdLabel.setVisible(false);
        hardnessLabel.setVisible(false);
        postGainLabel.setVisible(false);

        preGainSlider.setBounds(preGainArea);
        tresholdValueSlider.setBounds(tresholdArea);
        hardnessValueSlider.setBounds(hardnessArea);
        postGainSlider.setBounds(postGainArea);
    }
    else
    {
        auto tresholdSliderArea = tresholdArea.removeFromTop(tresholdArea.getHeight() * 0.75);
        auto tresholdLabelArea = tresholdArea.removeFromBottom(tresholdArea.getHeight());

        auto hardnessSliderArea = hardnessArea.removeFromTop(hardnessArea.getHeight() * 0.75);
        auto hardnessLabelArea = hardnessArea.removeFromBottom(hardnessArea.getHeight());

        auto preGainKnobArea = preGainArea.removeFromTop(preGainArea.getHeight() * 0.80);

        auto postGainKnobArea = postGainArea.removeFromTop(postGainArea.getHeight() * 0.80);

        preGainSlider.setBounds(preGainKnobArea);
        preGainLabel.setBounds(preGainArea);

        tresholdValueSlider.setBounds(tresholdSliderArea);
        tresholdLabel.setBounds(tresholdLabelArea);

        hardnessValueSlider.setBounds(hardnessSliderArea);
        hardnessLabel.setBounds(hardnessLabelArea);

        postGainSlider.setBounds(postGainKnobArea);
        postGainLabel.setBounds(postGainArea);
    }
}

std::vector<juce::Component*> ExoDistAudioProcessorEditor::getComps()
{
    return
    {
        &preGainSlider,
        &preGainLabel,

        &tresholdValueSlider,
        &tresholdLabel,

        &hardnessValueSlider,
        &hardnessLabel,

        &postGainSlider,
        &postGainLabel,

        &title
    };
}
