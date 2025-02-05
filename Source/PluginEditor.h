/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/Components/TitleComponent.h"
#include "UI/Components/FooterComponent.h"
#include "UI/ExoLookAndFeel.h"

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

    // defining custom look and feel
    ExoLookAndFeel exoLookAndFeel;

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
    
    TitleComponent titleComponent;
    FooterComponent footerComponent;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExoDistAudioProcessorEditor)
};
