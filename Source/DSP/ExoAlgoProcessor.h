/*
  ==============================================================================

    ExoAlgoProcessor.h
    Created: 24 Jan 2025 1:01:18pm
    Author:  Ivan Pollak

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

template <typename Type>
class ExoAlgoProcessor : public juce::dsp::ProcessorBase
{
public:
    ExoAlgoProcessor() : scaleFactor(1.0f), maxThreshold(1.0f)
    {
        
    }

    void prepare (const juce::dsp::ProcessSpec& spec) override
    {
        
    }
    
    void process (const juce::dsp::ProcessContextReplacing<Type>& context) override
    {
        auto& inputBlock = context.getInputBlock();
        auto& outputBlock = context.getOutputBlock();

        auto numChannels = outputBlock.getNumChannels();
        auto numSamples = outputBlock.getNumSamples();

        for (size_t ch = 0; ch < numChannels; ++ch)
        {
            auto* channelData = outputBlock.getChannelPointer(ch);

            for (size_t i = 0; i < numSamples; ++i)
            {
                channelData[i] = processSample(channelData[i]);
            }
        }
    }
    
    void reset() override
    {
        
    }

    
    void setScaleFactor(float newScaleFactor)
    {
        this->scaleFactor = newScaleFactor;
    }

    void setMaxThreshold(float newMaxThreshold)
    {
        this->maxThreshold = newMaxThreshold;
    }
private:
    float scaleFactor;
    float maxThreshold;
    
    float processSample(float sample)
    {
        return applySinusodialClip(sample);
    }
    
    float normalizeBetweenThresholds(float input, float softenThreshold, float hardThreshold) {
        float tresholdDifference;
        float adjustedInput;
        float output;

        tresholdDifference = hardThreshold - softenThreshold;
        adjustedInput = input - softenThreshold;
        output = adjustedInput / tresholdDifference;

        return output;
    };
    
    float applySinusodialClip(float inputValue)
    {
        float finalOutput;
        bool isInputNegative = inputValue < 0;
        inputValue = std::abs(inputValue);

        float softenThreshold = maxThreshold * scaleFactor;

        if (inputValue >= softenThreshold)
        {


            float thresholdDifference = maxThreshold - softenThreshold;
            float linearValue = normalizeBetweenThresholds(inputValue, softenThreshold, maxThreshold);

            if (linearValue < M_PI / 2)
            {
                float adjustedOutput = sin(linearValue) * thresholdDifference;
                finalOutput = adjustedOutput + softenThreshold;
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

    }
};
