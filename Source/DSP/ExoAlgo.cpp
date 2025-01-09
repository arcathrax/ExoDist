#define _USE_MATH_DEFINES

#include "ExoAlgo.h"
#include <cmath>

template <typename SampleType>
float ExoAlgo<SampleType>::normalizeBetweenThresholds(float input, float softenTreshold, float hardTreshold) {
    float tresholdDifference;
    float adjustedInput;
    float output;

    tresholdDifference = hardTreshold - softenTreshold;
    adjustedInput = input - softenTreshold;
    output = adjustedInput / tresholdDifference;

    return output;
};

template <typename SampleType>
float ExoAlgo<SampleType>::applySinusoidalClip(float inputValue, float scalingFactor, float maxThreshold)
{
    float finalOutput;
    bool isInputNegative = inputValue < 0;
    inputValue = std::abs(inputValue);

    scalingFactor = maxThreshold * scalingFactor;

    if (inputValue >= scalingFactor)
    {

        float thresholdDifference = maxThreshold - scalingFactor;
        float linearValue = normalizeBetweenThresholds(inputValue, scalingFactor, maxThreshold);

        if (linearValue < M_PI / 2)
        {
            float adjustedOutput = sin(linearValue) * thresholdDifference;
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
};

template <typename SampleType>
void ExoAlgo<SampleType>::reset() 
{

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
