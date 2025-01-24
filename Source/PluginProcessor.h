/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DSP/ExoAlgoProcessor.h"

//==============================================================================
/**
*/
class ExoDistAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    ExoDistAudioProcessor();
    ~ExoDistAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts{ *this, nullptr, "Parameters", createParameterLayout() };

private:
    enum
    {
        gainIndex,
        exoAlgoIndex,
        filterIndex,
        limiterIndex
    };

    using ProcessorChain = juce::dsp::ProcessorChain<
        juce::dsp::Gain<float>,
        ExoAlgoProcessor<float>,
        juce::dsp::LadderFilter<float>,
        juce::dsp::Limiter<float>
    >;

    ProcessorChain processorChain;

    void updateEffects();
    void initializeEffects();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ExoDistAudioProcessor);
};
