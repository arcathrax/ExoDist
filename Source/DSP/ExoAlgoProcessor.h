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
    ExoAlgoProcessor() : multiplier(1.0f)
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

    
    void setMultiplier(float newMultiplier)
    {
        this->multiplier = newMultiplier;
    }
private:
    float multiplier;
    
    float processSample(float sample)
    {
        return sample * multiplier;
    }
};
