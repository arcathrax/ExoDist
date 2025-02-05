/*
  ==============================================================================

    FooterComponent.cpp
    Created: 3 Feb 2025 1:18:31pm
    Author:  Ivan Pollak

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FooterComponent.h"

//==============================================================================
FooterComponent::FooterComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

FooterComponent::~FooterComponent()
{
}

void FooterComponent::paint (juce::Graphics& g)
{
    juce::ColourGradient gradient(
        juce::Colour(0xFF1a1a19), 0, 0,
        juce::Colour(0xFF141414), 0, getHeight(),
        false
    );
    
    g.setGradientFill (gradient);
    g.fillRect(getLocalBounds());

    g.setColour(juce::Colour(0xFF4f8131));
    g.setFont (juce::FontOptions (15.0f));
    g.drawText ("arcathrax productions", getLocalBounds(),
                juce::Justification::centredBottom, true);
}

void FooterComponent::resized()
{
    
}
