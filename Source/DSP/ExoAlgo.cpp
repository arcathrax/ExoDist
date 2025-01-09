#define _USE_MATH_DEFINES

#include "ExoAlgo.h"
#include <cmath>

template <typename SampleType>
SampleType ExoAlgo<SampleType>::normalizeBetweenThresholds(SampleType input, SampleType softenTreshold, SampleType hardTreshold) {
    SampleType tresholdDifference;
    SampleType adjustedInput;
    SampleType output;

    tresholdDifference = hardTreshold - softenTreshold;
    adjustedInput = input - softenTreshold;
    output = adjustedInput / tresholdDifference;

    return output;
};

template <typename SampleType>
SampleType ExoAlgo<SampleType>::applySinusoidalClip(SampleType inputValue, SampleType scalingFactor, SampleType maxThreshold)
{
    SampleType finalOutput;
    bool isInputNegative = inputValue < 0;
    inputValue = std::abs(inputValue);

    scalingFactor = maxThreshold * scalingFactor;

    if (inputValue >= scalingFactor)
    {

        SampleType thresholdDifference = maxThreshold - scalingFactor;
        SampleType linearValue = normalizeBetweenThresholds(inputValue, scalingFactor, maxThreshold);

        if (linearValue < M_PI / 2)
        {
            SampleType adjustedOutput = sin(linearValue) * thresholdDifference;
            finalOutput = adjustedOutput + scalingFactor;
        }
        else
        {
            finalOutput = maxThreshold;
        }
    }
    else
    {
        finalOutput = inputValue;
    }

    if (isInputNegative)
    {
        finalOutput = -finalOutput;
    }

    return finalOutput;
};

template <typename SampleType>
void ExoAlgo<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    sampleRate = static_cast<SampleType>(spec.sampleRate);
    maxThreshold = 1.0;  // Reset to a default
    scalingFactor = 1.0; // Reset to a default
};

template <typename SampleType>
void ExoAlgo<SampleType>::reset() 
{
    maxThreshold = 1.0;
    scalingFactor = 0.5;
};

template <typename SampleType>
template <typename ProcessContext>
void ExoAlgo<SampleType>::process(const ProcessContext& context)
{
    auto& inputBlock = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();

    // Ensure the input and output sizes match
    jassert(inputBlock.getNumSamples() == outputBlock.getNumSamples());
    jassert(inputBlock.getNumChannels() == outputBlock.getNumChannels());

    for (size_t channel = 0; channel < inputBlock.getNumChannels(); ++channel)
    {
        auto* input = inputBlock.getChannelPointer(channel);
        auto* output = outputBlock.getChannelPointer(channel);

        for (size_t sample = 0; sample < inputBlock.getNumSamples(); ++sample)
        {
            // Example: Apply the sinusoidal clipping algorithm
            output[sample] = applySinusoidalClip(input[sample], scalingFactor, maxThreshold);
        }
    }
}

template <typename SampleType>
void ExoAlgo<SampleType>::setMaxThreshold(SampleType newMaxThreshold)
{
    this->maxThreshold = newMaxThreshold;
};

template <typename SampleType>
void ExoAlgo<SampleType>::setScalingFactor(SampleType newScalingFactor)
{
    this->scalingFactor = newScalingFactor;
};

// Explizite Instanziierung für SampleType = float
template class ExoAlgo<float>;
template void ExoAlgo<float>::process<juce::dsp::ProcessContextReplacing<float>>(const juce::dsp::ProcessContextReplacing<float>& context);