#ifndef EXOALGO_H
#define EXOALGO_H
#include <JuceHeader.h>
class ExoAlgo
{
public:
	// variables

	//functions
    void prepare (const juce::dsp::ProcessSpec& spec) noexcept
    {
    }
    
    void reset() noexcept
    {
    }
    
    template <typename SampleType>
    SampleType processSample (SampleType s) noexcept
    {
        return applySinusodialClip(s);
    }

    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        auto&& inBlock = context.getInputBlock();
        auto&& outBlock = context.getOutputBlock();
        auto numChannels = inBlock.getNumChannels();
        auto numSamples = inBlock.getNumSamples();
        
        for (int channel = 0; channel < numChannels; ++channel)
        {
            auto* input = inBlock.getChannelPointer(channel);
            auto* output = outBlock.getChannelPointer(channel);
            
            for (int i = 0; i < numSamples; ++i)
            {
                output[i] = processSample(input[i]);
            }
        }
    }
    
	float applySinusodialClip(float inputValue);
	
	void setScaleFactor(float newScaleFactor);
	void setMaxThreshold(float newMaxThreshold);
private:
	// variables
	float scaleFactor;
	float maxThreshold;
	float softenThreshold;

	// functions
	float normalizeBetweenThresholds(float rawInput, float softenTreshold, float hardTreshold);
};

#endif
