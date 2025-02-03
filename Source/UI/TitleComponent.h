/*
  ==============================================================================

    TitleComponent.h
    Created: 3 Feb 2025 11:43:38am
    Author:  Ivan Pollak

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TitleComponent  : public juce::Component
{
public:
    TitleComponent();
    ~TitleComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TitleComponent)
};
