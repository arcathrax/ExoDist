#ifndef EXOALGO_H
#define EXOALGO_H

#include <JuceHeader.h>

template <typename SampleType> class ExoAlgo
{
public:
	float normalizeBetweenThresholds(float rawInput, float softenTreshold, float hardTreshold);
	float applySinusoidalClip(float inputValue, float scaleFactor, float maxThreshold);

	void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
	void reset();
	template <typename ProcessContext> void process(const ProcessContext& context);

private:
	SampleType sampleRate = 44100.0; // Default sample rate
};
#endif
