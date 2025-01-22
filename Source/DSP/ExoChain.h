/*
  ==============================================================================

    ExoChain.h
    Created: 9 Jan 2025 1:51:56pm
    Author:  arcathrax

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ExoAlgo.h"
class ExoChain
{
public:
    ExoChain();

    void prepare(const juce::dsp::ProcessSpec& spec);
    template <typename ProcessContext>
    void process(const ProcessContext& context);
    void reset() noexcept;

    void updateDistortion(float newMaxThreshold, float newScalingFactor);
private:
    enum
    {
        preGainIndex,
        distortionIndex,
        filterIndex,
        postGainIndex
    };

    using Filter = juce::dsp::IIR::Filter<float>;
    using FilterCoefs = juce::dsp::IIR::Coefficients<float>;

    juce::dsp::ProcessorChain<
        juce::dsp::Gain<float>,
        ExoAlgo<float>,
        juce::dsp::ProcessorDuplicator<Filter, FilterCoefs>,
        juce::dsp::Gain<float>
    > processorChain;
};