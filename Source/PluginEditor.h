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
struct CustomLabel : juce::Label
{
public:
    CustomLabel()
    {
//      setColour(juce::Label::backgroundColourId, juce::Colours::lightblue);
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

    CustomRotarySlider 
        preGainSlider,
        tresholdValueSlider,
        hardnessValueSlider,
        postGainSlider;

    CustomLabel preGainLabel;
    CustomLabel postGainLabel;
    CustomLabel tresholdLabel;
    CustomLabel hardnessLabel;
    CustomLabel title;


    float fontSizeS;
    float fontSizeM;
    float fontSizeL;

    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;

    Attachment 
        preGainSliderAttachment,
        tresholdValueSliderAttachment,
        hardnessValueSliderAttachment,
        postGainSliderAttachment;

    std::vector<juce::Component*> getComps();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExoDistAudioProcessorEditor)
};
