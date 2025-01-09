/*
  ==============================================================================

    ExoChain.cpp
    Created: 9 Jan 2025 1:51:56pm
    Author:  arcathrax

  ==============================================================================
*/

#include "ExoChain.h"

ExoChain::ExoChain()
{
    auto& preGain = processorChain.template get<preGainIndex>();
    auto& postGain = processorChain.template get<postGainIndex>();

    preGain.setGainDecibels(10.0f);
    postGain.setGainDecibels(-10.0f);
};

void ExoChain::reset() noexcept
{
    processorChain.reset();
};

void ExoChain::prepare(const juce::dsp::ProcessSpec& spec)
{
    auto& filter = processorChain.template get<filterIndex>();
    filter.state = FilterCoefs::makeFirstOrderLowPass(spec.sampleRate, 5000.0f);

    processorChain.prepare(spec);
};

template <typename ProcessContext>
void ExoChain::process(const ProcessContext& context)
{
    processorChain.process(context);
}

void ExoChain::updateDistortion(float newMaxThreshold, float newScalingFactor)
{
    auto& distortion = processorChain.template get<distortionIndex>();
    distortion.setMaxThreshold(newMaxThreshold);
    distortion.setScalingFactor(newScalingFactor);
};