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

    // Überschreiben der paint-Methode
    void paint (juce::Graphics& g) override
    {
        const float diameter = juce::jmin(getWidth(), getHeight());
        const float radius = diameter / 2.0f;
        const float centerX = getWidth() / 2.0f;
        const float centerY = getHeight() / 2.0f;

        g.setColour(juce::Colour(0xFF1a1a19));
        g.fillEllipse(centerX - radius, centerY - radius, diameter, diameter);

        float value = getValue();
        float minValue = getMinimum();
        float maxValue = getMaximum();

        float normalizedValue = (value - minValue) / (maxValue - minValue);

        float angle = (normalizedValue*5)-(juce::MathConstants<float>::pi*1.25);

        const float endX = centerX + radius * std::cos(angle);
        const float endY = centerY + radius * std::sin(angle);

        g.setColour(juce::Colour(0xFF4f8131));
        g.drawLine(centerX, centerY, endX, endY, getWidth()*0.03);
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

    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;

    // defining the slider attachments

    std::vector<juce::Component*> getComps();
    
    juce::uint32 BackgroundColor = 0xFFf6fcdf;
    juce::uint32 ContentColor = 0xFF80993c;
    juce::uint32 TitleColor = 0xFF4f8131;
    juce::uint32 HighlightColor = 0xFF1a1a19;
    
    

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExoDistAudioProcessorEditor)
};
