# Was ist die ProcessorChain

Die *ProcessorChain* ist eine Klasse,
die eine Reihe von Audio-Prozessoren verwaltet und
in einer festen Anordnung verarbeitet.

Man kann dies mit dem Effect Rack von jeglichen DAW's vergleichen.
Z.B. kann an erster Stelle ein Filter sein,
an zweiter Stelle ein Reverb und
an dritter Stelle nochmals ein Filter.

Die *ProcessorChain* ist Teil des *DSP*-Modul von JUCE.
Daher muss also bei jeglicher Verwendung von dieser Klasse
das *DSP*-Modul im Projekt integriert werden.

# Erstellung der ProcessorChain

Der Nachfolgende Code ist nur ein Beispiel für eine *ProcessorChain*.
Hierbei erstellen wir eine *ProcessorChain*,
welche folgene Reihenfolge hat;
1. Oszillator
2. Filter

Wir wir geben dem Oszillator eine Funktion,
welche uns eine einfache Sägezahwelle gibt.
Für den Filter setzen wir den *CutOff* bei
500 Hz und die Resonance auf 0.7.

Datei: `PluginProcessor.h`
```c++
enum
{
    oscIndex,
    filterIndex
};

using ProcessorChain = juce::dsp::ProcessorChain<
    juce::dsp::Oscillator<float>,
    juce::dsp::LadderFilter<float>
>;
ProcessorChain processorChain;
```

Datei: `PluginProcessor.cpp`
```c++
AudioProcessor::NewProjectAudioProcessor()
{
    auto& osc = processorChain.template get<oscIndex>();
    osc.initialise([](float x)
        {
            return juce::jmap(x,
                float(-juce::MathConstants<double>::pi),
                float(juce::MathConstants<double>::pi),
                float(-1),
                float(1));
        }, 2);
    osc.setFrequency(400);

    auto& filter = processorChain.template get<filterIndex>();
    filter.setCutoffFrequencyHz(500.0f);
    filter.setResonance(0.7f);
}
```

```c++
void AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;

    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    spec.sampleRate = sampleRate;

    processorChain.prepare(spec);
}
```

```c++
void AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    processorChain.process(context);
}
```
