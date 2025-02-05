/*
  ==============================================================================

    AnalyserComponent.h
    Created: 5 Feb 2025 10:46:13am
    Author:  Administrator

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AnalyserComponent  : public juce::Component
{
public:
    AnalyserComponent();
    ~AnalyserComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalyserComponent)
};
