/*
  ==============================================================================

    ExoLookAndFeel.h
    Created: 5 Feb 2025 8:49:44am
    Author:  Administrator

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ExoLookAndFeel : public juce::LookAndFeel_V4
{
public:
	ExoLookAndFeel();
    ~ExoLookAndFeel();

    void ExoLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

private:

};