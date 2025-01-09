#ifndef EXOALGO_H
#define EXOALGO_H

#include <JuceHeader.h>

template <typename SampleType> class ExoAlgo
{
public:
	// algorithm functions
	SampleType normalizeBetweenThresholds(SampleType rawInput, SampleType softenTreshold, SampleType hardTreshold);
	SampleType applySinusoidalClip(SampleType inputValue, SampleType scaleFactor, SampleType maxThreshold);

	// processor chain functions
	void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
	void reset();
	template <typename ProcessContext> 
	void process(const ProcessContext& context);

	// update variable functions
	void setMaxThreshold(SampleType newMaxThreshold);
	void setScalingFactor(SampleType newScalingFactor);

private:
	// default variables
	SampleType sampleRate = 44100.0; // Default sample rate
	SampleType maxThreshold = 1.0; // Reset to a default
	SampleType scalingFactor = 1.0; // Reset to a default
};

#endif
