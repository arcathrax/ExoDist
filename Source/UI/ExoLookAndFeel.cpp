/*
  ==============================================================================

    ExoLookAndFeel.cpp
    Created: 5 Feb 2025 8:49:44am
    Author:  Administrator

  ==============================================================================
*/

#include "ExoLookAndFeel.h"
ExoLookAndFeel::ExoLookAndFeel()
{
    setColour(juce::Slider::thumbColourId, juce::Colour(0xFFf6fcdf));
    setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xFF4f8131));
    setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xFF363633));
}

ExoLookAndFeel::~ExoLookAndFeel()
{
}

void ExoLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    auto outline = slider.findColour(juce::Slider::rotarySliderOutlineColourId);
    auto fill = slider.findColour(juce::Slider::rotarySliderFillColourId);

    // scale the slider if hovered over
    bool isInteracting = slider.isMouseOverOrDragging();
    float scaleFactor = isInteracting ? 0.98f : 1.0f;

    // calculate scaled bounds
    int scaledWidth = static_cast<int>(width * scaleFactor);
    int scaledHeight = static_cast<int>(height * scaleFactor);

    auto bounds = juce::Rectangle<int>(x + (width - scaledWidth) / 2,
        y + (height - scaledHeight) / 2,
        scaledWidth, scaledHeight).toFloat().reduced(10);

    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = juce::jmin(8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;

    // draw background circle
    juce::Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(),
        bounds.getCentreY(),
        arcRadius,
        arcRadius,
        0.0f,
        rotaryStartAngle,
        rotaryEndAngle,
        true);

    g.setColour(outline);
    g.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            toAngle,
            true);

        juce::ColourGradient gradient(fill.darker(1.2f), bounds.getCentreX() - arcRadius, bounds.getCentreY(),
            fill, bounds.getCentreX() + arcRadius, bounds.getCentreY(), false);
        g.setGradientFill(gradient);
        g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    // thumb
    auto thumbWidth = lineW * 2.f * scaleFactor;
    juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - juce::MathConstants<float>::halfPi),
        bounds.getCentreY() + arcRadius * std::sin(toAngle - juce::MathConstants<float>::halfPi));

    g.setColour(slider.findColour(juce::Slider::thumbColourId));
    g.fillEllipse(juce::Rectangle<float>(thumbWidth, thumbWidth).withCentre(thumbPoint));
}