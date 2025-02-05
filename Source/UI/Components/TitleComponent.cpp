/*
  ==============================================================================

    TitleComponent.cpp
    Created: 3 Feb 2025 11:43:38am
    Author:  Ivan Pollak

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TitleComponent.h"

//==============================================================================
TitleComponent::TitleComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

TitleComponent::~TitleComponent()
{
}

void TitleComponent::paint (juce::Graphics& g)
{
    juce::ColourGradient gradient(
        juce::Colour(0xFF1a1a19), 0, 0,
        juce::Colour(0xFF1a1a19), 0, getHeight(),
                                  
        false
    );
    
    g.setGradientFill (gradient);
    g.fillRect(getLocalBounds());

    g.setColour(juce::Colour(0xFF4f8131));
    g.setFont (juce::FontOptions (40.0f));
    g.drawText ("exodist", getLocalBounds(),
                juce::Justification::centred, true);
}

void TitleComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
