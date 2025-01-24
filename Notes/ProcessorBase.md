# Was ist die ProcessorBase
Die *ProcessorBase* ist eine Klasse
des *DSP*-Modul von JUCE.

Diese Klasse bzw. dieses Strukt sorgt dafür,
dass jegliche Funktionen,
welche ein Prozessor bracht,
implementiert wird.


# Beispiel

Bei diesem Beispiel wird ein einfacher GainProzessor erstellt.

```c++
class GainProcessor : public juce::ProcessorBase
{
public:
    GainProcessor() : gainParameter(1.0f) {} // Standard-Gain auf 1.0 setzen

    void prepare(const juce::dsp::ProcessSpec& spec) override
    {
        sampleRate = spec.sampleRate;
        numChannels = spec.numChannels;
    }

    void process(const juce::dsp::ProcessContextReplacing<float>& context) override
    {
        auto& block = context.getOutputBlock();
        for (size_t channel = 0; channel < block.getNumChannels(); ++channel)
        {
            auto* channelData = block.getChannelPointer(channel);
            for (size_t sample = 0; sample < block.getNumSamples(); ++sample)
            {
                channelData[sample] *= gainParameter;
            }
        }
    }

    void reset() override
    {
        // Falls erforderlich, hier interne Zustände zurücksetzen
    }

    void setGain(float newGain)
    {
        gainParameter = newGain;
    }

private:
    float gainParameter;
    double sampleRate = 0.0;
    int numChannels = 0;
};

```
