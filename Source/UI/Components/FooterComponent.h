/*
  ==============================================================================

    FooterComponent.h
    Created: 3 Feb 2025 1:18:31pm
    Author:  Ivan Pollak

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FooterComponent  : public juce::Component
{
public:
    FooterComponent();
    ~FooterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FooterComponent)
};
