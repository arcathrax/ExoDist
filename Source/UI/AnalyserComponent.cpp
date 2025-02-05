/*
  ==============================================================================

    AnalyserComponent.cpp
    Created: 5 Feb 2025 10:46:13am
    Author:  Administrator

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AnalyserComponent.h"

//==============================================================================
AnalyserComponent::AnalyserComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

AnalyserComponent::~AnalyserComponent()
{
}

void AnalyserComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("AnalyserComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void AnalyserComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
