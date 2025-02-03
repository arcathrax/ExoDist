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

    // defining the sliders
    CustomRotarySlider preGainSlider,
        hardnessSlider,
        thresholdSlider;

    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;

    // defining the slider attachments
    Attachment preGainSliderAttachment,
        hardnessSliderAttachment,
        thresholdSliderAttachment;

    std::vector<juce::Component*> getComps();
    
    juce::uint32 BackgroundColor = 0xFFf6fcdf;
    juce::uint32 ContentColor = 0xFF80993c;
    juce::uint32 TitleColor = 0xFF4f8131;
    juce::uint32 HighlightColor = 0xFF1a1a19;
    
    

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExoDistAudioProcessorEditor)
};
