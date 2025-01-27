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
        scaleFactorSlider,
        maxThresholdSlider,
        cutoffSlider,
        thresholdSlider,
        postGainSlider,
        mixSlider;
    
    // defining the labels
    juce::Label titleLabel;
    
    juce::Label authorLabel;
    juce::Label preGainLabel;
    juce::Label scaleFactorLabel;
    juce::Label maxThresholdLabel;
    juce::Label cutoffLabel;
    juce::Label thresholdLabel;
    juce::Label postGainLabel;
    juce::Label mixLabel;
    
    juce::Label fftLabel;

    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;

    // defining the slider attachments
    Attachment preGainSliderAttachment,
        scaleFactorSliderAttachment,
        maxThresholdSliderAttachment,
        cutoffSliderAttachment,
        thresholdSliderAttachment,
        postGainSliderAttachment,
        mixSliderAttachment;

    std::vector<juce::Component*> getComps();
    
    juce::uint32 BackgroundColor = 0xFF1a1a19;
    juce::uint32 ContentColor = 0xFF4f8131;
    juce::uint32 TitleColor = 0xFF80993c;
    juce::uint32 HighlightColor = 0xFFf6fcdf;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExoDistAudioProcessorEditor)
};
