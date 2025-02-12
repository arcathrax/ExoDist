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
#include "UI/Components/VerticalMeter.h"

struct CustomRotarySlider : juce::Slider
{
    CustomRotarySlider() : juce::Slider
    (
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
        juce::Slider::TextEntryBoxPosition::NoTextBox
    )
    {
        setVelocityBasedMode(true);
        setVelocityModeParameters(1, 1, 0.05, true);
    }

    void mouseDrag(const juce::MouseEvent& event) override
    {
        if (event.mods.isShiftDown())
        {
            setVelocityModeParameters(0.25, 1, 0.02, true);
        }
        else
        {
            setVelocityModeParameters(1, 1, 0.05, true);
        }

        juce::Slider::mouseDrag(event);
    }
};




//==============================================================================
/**
*/
class ExoDistAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    ExoDistAudioProcessorEditor (ExoDistAudioProcessor&);
    ~ExoDistAudioProcessorEditor() override;

    //==============================================================================
    void timerCallback() override;
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

    juce::Label preGainLabel, hardnessLabel, thresholdLabel;

    // defining the level meters
    VerticalMeter verticalMeterLeft, verticalMeterRight;

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
