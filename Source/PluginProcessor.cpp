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
    spec.numChannels = 1;
    spec.sampleRate = sampleRate;
    
    previousPreGain = preGain;
    previousPostGain = postGain;

    exoAlgo.setScaleFactor(scaleFactor);
    exoAlgo.setMaxThreshold(maxThreshold);
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
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();

    preGain = *apvts.getRawParameterValue("Pre Gain");
    postGain = *apvts.getRawParameterValue("Post Gain");
    maxThreshold = *apvts.getRawParameterValue("Max Threshold");
    scaleFactor = *apvts.getRawParameterValue("Scale Factor");

    auto currentPreGain = preGain;
    if (juce::approximatelyEqual(currentPreGain, preGain))
    {
        buffer.applyGain(currentPreGain);
    }
    else
    {
        buffer.applyGainRamp(0, numSamples, preGain, currentPreGain);
        preGain = currentPreGain;
    }

    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            float currentSample = channelData[sample];
            exoAlgo.setScaleFactor(scaleFactor);
            exoAlgo.setMaxThreshold(maxThreshold);
            newSample = exoAlgo.process(currentSample);
            channelData[sample] = newSample;
        }
    }

    auto currentPostGain = postGain;
    if (juce::approximatelyEqual(currentPostGain, previousPostGain))
    {
        buffer.applyGain(currentPostGain);
    }
    else
    {
        buffer.applyGainRamp(0, numSamples, previousPostGain, currentPostGain);
        previousPostGain = currentPostGain;
    }
}



//==============================================================================
bool ExoDistAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ExoDistAudioProcessor::createEditor()
{
    // return new ExoDistAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void ExoDistAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void ExoDistAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
    {
        apvts.replaceState(tree);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ExoDistAudioProcessor();
}

// Füge Parameter hinzu
juce::AudioProcessorValueTreeState::ParameterLayout
    ExoDistAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // Füge Pre Gain Parameter hinzu
    layout.add
    (
        std::make_unique<juce::AudioParameterFloat>
        (
            "Pre Gain",
            "Pre Gain",
            juce::NormalisableRange<float>
            (
                0.0f,
                25.0f,
                0.000001f,
                0.25f
            ),
            1.0f
        )
    );

    // Füge Clipper Parameter hinzu
    layout.add
    (
        std::make_unique<juce::AudioParameterFloat>
        (
            "Max Threshold",
            "Max Threshold",
            juce::NormalisableRange<float>
            (
                0.01f,
                1.0f,
                0.000001f,
                1.0f
            ),
            0.75f
        )
    );

    // Füge Clipper Parameter hinzu
    layout.add
    (
        std::make_unique<juce::AudioParameterFloat>
        (
            "Scale Factor",
            "Scale Factor",
            juce::NormalisableRange<float>
            (
                0.0f,
                1.0f,
                0.000001f,
                1.0f
            ),
            1.0f
        )
    );

    // Füge Post Gain Parameter hinzu
    layout.add
    (
        std::make_unique<juce::AudioParameterFloat>
        (
            "Post Gain",
            "Post Gain",
            juce::NormalisableRange<float>
            (
                0.0f,
                4.0f,
                0.000001f,
                0.25f
            ),
            1.0f
        )
    );
    return layout;
}