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

    // setup the processorchain
    processorChain.prepare(spec);
    
    // updating the processorChain configurations
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

    // updating the processorChain configurations
    updateEffects();
    
    // processing the signal
    processorChain.process(context);
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
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void ExoDistAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
    {
        apvts.replaceState(tree);
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout 
    ExoDistAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add
    (
        std::make_unique<juce::AudioParameterFloat>(
            "PreGain",
            "PreGain",
            juce::NormalisableRange<float>
            (
                0.75f,
                12.0f,
                0.000001f,
                0.35f
            ),
            1.0f
        )
    );
        
    layout.add
    (
        std::make_unique<juce::AudioParameterFloat>(
            "Hardness",
            "Hardness",
            juce::NormalisableRange<float>
            (
                0.0f,
                5.0f,
                0.000001f,
                0.5f
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
                0.0f,
                1.0f,
                0.000001f,
                0.5f
            ),
            1.0f
        )
    );

    return layout;
}

void ExoDistAudioProcessor::updateEffects()
{
    // get the parameters
    float preGainParameter = *apvts.getRawParameterValue("PreGain");
    
    float hardnessParameter = *apvts.getRawParameterValue("Hardness");
    float thresholdParameter = *apvts.getRawParameterValue("Threshold");



    // update preGain
    auto& preGain = processorChain.template get<preGainIndex>();
    preGain.setGainLinear(preGainParameter);
    
    // update exoAlgoProcessor
    auto& exoAlgoProcessor = processorChain.template get<exoAlgoIndex>();
    exoAlgoProcessor.setScaleFactor(hardnessParameter);
    exoAlgoProcessor.setMaxThreshold(thresholdParameter);

    // update postGain
    auto& postGain = processorChain.template get<postGainIndex>();
    postGain.setGainDecibels(thresholdParameter*24);
    
    // update the limiter
}

void ExoDistAudioProcessor::initializeEffects()
{
    // initialize preGain
    auto& preGain = processorChain.template get<preGainIndex>();
    preGain.setGainDecibels(juce::Decibels::gainToDecibels(1.0f));
    
    // initialize exoAlgoProcessor
    auto& exoAlgoProcessor = processorChain.template get<exoAlgoIndex>();
    exoAlgoProcessor.setScaleFactor(1.0f);
    exoAlgoProcessor.setMaxThreshold(1.0f);

    // initialize filter
    auto& filter = processorChain.template get<filterIndex>();
    filter.setCutoffFrequencyHz(20000);
    filter.setResonance(0.0f);

    // initialize postGain
    auto& postGain = processorChain.template get<postGainIndex>();
    postGain.setGainDecibels(juce::Decibels::gainToDecibels(1.0f));
    
    // initialize limiter
    auto& limiter = processorChain.template get<limiterIndex>();
    limiter.setThreshold(0.0f);
    limiter.setRelease(400.0f);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ExoDistAudioProcessor();
}
