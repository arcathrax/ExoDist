/*
  ==============================================================================

    VerticalMeter.h
    Created: 5 Feb 2025 3:53:11pm
    Author:  Administrator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class VerticalMeter  : public juce::Component
{
public:
    VerticalMeter()
    {
    }

    ~VerticalMeter() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();

        g.setColour(juce::Colours::white.withBrightness(0.4f));
        g.fillRoundedRectangle(bounds, 5.f);

        g.setColour(juce::Colours::white);
        const auto scaledY = juce::jmap(level, -60.f, 6.f, 0.f, static_cast<float>(getHeight()));
        g.fillRoundedRectangle(bounds.removeFromBottom(scaledY).reduced(2.5f), 5.f);
    }

    void resized() override
    {
    }

    void setLevel(const float value)
    {
        level = value;
    }

private:
    float level = -60.f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VerticalMeter)
};
