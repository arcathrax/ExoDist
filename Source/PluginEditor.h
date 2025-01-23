/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct CustomRotarySlider : juce::Slider
{
    CustomRotarySlider() : juce::Slider
    (
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
        juce::Slider::TextEntryBoxPosition::NoTextBox
    )
    {
    }
};

//==============================================================================
/**
*/
class ExoDistAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ExoDistAudioProcessorEditor (ExoDistAudioProcessor&);
    ~ExoDistAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ExoDistAudioProcessor& audioProcessor;

    CustomRotarySlider gainSlider,
        cutoffSlider,
        resonanceSlider,
        thresholdSlider,
        releaseSlider;

    juce::Label titleLabel;

    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;

    Attachment gainSliderAttachment,
        cutoffSliderAttachment,
        resonanceSliderAttachment,
        thresholdSliderAttachment,
        releaseSliderAttachment;

    std::vector<juce::Component*> getComps();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExoDistAudioProcessorEditor)
};
