/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ExoDistAudioProcessor::ExoDistAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
    initializeEffects();
}

ExoDistAudioProcessor::~ExoDistAudioProcessor()
{
}

//==============================================================================
const juce::String ExoDistAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ExoDistAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ExoDistAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ExoDistAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ExoDistAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ExoDistAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ExoDistAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ExoDistAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ExoDistAudioProcessor::getProgramName (int index)
{
    return {};
}

void ExoDistAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ExoDistAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;

    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    spec.sampleRate = sampleRate;

    processorChain.prepare(spec);

    updateEffects();
}

void ExoDistAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ExoDistAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ExoDistAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // clear the buffer
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear (i, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    updateEffects();

    processorChain.process(context);
}



//==============================================================================
bool ExoDistAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ExoDistAudioProcessor::createEditor()
{
    return new ExoDistAudioProcessorEditor (*this);
    // return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void ExoDistAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void ExoDistAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

juce::AudioProcessorValueTreeState::ParameterLayout 
    ExoDistAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add
    (
        std::make_unique<juce::AudioParameterFloat>(
            "Gain",
            "Gain",
            juce::NormalisableRange<float>
            (
                1.0f,
                25.0f,
                0.000001f,
                0.35f
            ),
            1.0f
        )
    );

    layout.add
    (
        std::make_unique<juce::AudioParameterFloat>
        (
            "Cutoff",
            "Cutoff",
            juce::NormalisableRange<float>
            (
                20.0f,
                24000.0f,
                0.000001f,
                0.35f
            ),
            24000.0f
        )
    );

    layout.add
    (
        std::make_unique<juce::AudioParameterFloat>
        (
            "Resonance",
            "Resonance",
            juce::NormalisableRange<float>
            (
                0.0f,
                1.0f,
                0.000001f,
                1.0f
            ),
            0.0f
        )
    );

    layout.add
    (
        std::make_unique<juce::AudioParameterFloat>(
            "Threshold",
            "Threshold",
            juce::NormalisableRange<float>
            (
                -20.0f,
                20.0f,
                0.000001f,
                1.0f
            ),
            0.0f
        )
    );

    layout.add
    (
        std::make_unique<juce::AudioParameterFloat>(
            "Release",
            "Release",
            juce::NormalisableRange<float>
            (
                0.0f,
                800.0f,
                0.000001f,
                1.0f
            ),
            200.0f
        )
    );

    return layout;
}

void ExoDistAudioProcessor::updateEffects() 
{
    // get the parameters
    float cutoffParameter = *apvts.getRawParameterValue("Cutoff");
    float resonanceParameter = *apvts.getRawParameterValue("Resonance");
    float thresholdParameter = *apvts.getRawParameterValue("Threshold");
    float releaseParameter = *apvts.getRawParameterValue("Release");
    float gainParameter = *apvts.getRawParameterValue("Gain");

    // update gain
    auto& gain = processorChain.template get<gainIndex>();
    gain.setGainDecibels(juce::Decibels::gainToDecibels(gainParameter));

    // update the filter
    auto& filter = processorChain.template get<filterIndex>();
    filter.setCutoffFrequencyHz(cutoffParameter);
    filter.setResonance(resonanceParameter);

    // update the limiter
    auto& limiter = processorChain.template get<limiterIndex>();
    limiter.setThreshold(thresholdParameter);
    limiter.setRelease(releaseParameter);
}

void ExoDistAudioProcessor::initializeEffects()
{
    // initialize gain
    auto& gain = processorChain.template get<gainIndex>();
    gain.setGainDecibels(juce::Decibels::gainToDecibels(1.0f));

    // initialize waveshaper
    auto& waveshaper = processorChain.template get<waveShaperIndex>();
    waveshaper.functionToUse = [](float x)
        {
            return std::tanh(x);
        };

    // initialize filter
    auto& filter = processorChain.template get<filterIndex>();
    filter.setCutoffFrequencyHz(20000.0f);
    filter.setResonance(1.0f);

    // initialize limiter
    auto& limiter = processorChain.template get<limiterIndex>();
    limiter.setThreshold(0.0f);
    limiter.setRelease(200.0f);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ExoDistAudioProcessor();
}