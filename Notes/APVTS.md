# Was ist ein APVTS?

*APVTS* steht für Audio Processor Value Tree State.
Dies ist eine Klasse, welche von JUCE bereitgestellt wird,
um Parameter einfacher zu verwalten.
Ausserdem kann man mit dem *APVTS* auch Parameter
an UI-Elemente knüpfen.

# Erstellung des APVTS

Bei dem nachfolgendem Beispipel erstellen wir einen *APVTS*.
Dieser *APVTS* benutzt eine Funktion,
welche die Parameter generiert.
In diesem Beispiel ist dies die
`createParameterLayout` Funktion.

Datei: `PluginProcessor.h`
```c++
static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
juce::AudioProcessorValueTreeState apvts{ *this, nullptr, "Parameters", createParameterLayout() };
```

Datei: `PluginProcessor.cpp`
```c++
juce::AudioProcessorValueTreeState::ParameterLayout
    ExoDistAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
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
    return layout;
}
```

# Parameter aus dem *APVTS* auslesen
```c++
float preGain = *apvts.getRawParameterValue("Pre Gain");
```

# UI mit den Parametern verbinden
Für die Parameter ,in diesem Beispiel nur einer,
kann ein Slider erstellt werden,
welcher automatisch Änderungen an den APVTS übergibt.

Datei: `PluginEditor.h`
```c++
juce::Slider preGainSlider

using APVTS = juce::AudioProcessorValueTreeState;
using Attachment = APVTS::SliderAttachment;

Attachment
    preGainSliderAttachment;

std::vector<juce::Component*> getComps();
```

Datei: `PluginEditor.cpp`
```c++
ExoDistAudioProcessorEditor::ExoDistAudioProcessorEditor (ExoDistAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    preGainSliderAttachment(audioProcessor.apvts, "Pre Gain", preGainSlider)
    {
        for (auto* comp : getComps())
        {
            addAndMakeVisible(comp);
        }

        setSize (650, 380);
        setResizable(false, false);
    }
```

```c++
std::vector<juce::Component*> ExoDistAudioProcessorEditor::getComps()
{
    return
    {
        &preGainSlider
    };
}
```

```c++
void AudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    preGainSlider.setBounds(bounds);
    preGainSlider.setVisible(true);
}
```

# Set- & GetStateInformation

Diese Funktionen sorgen dafür,
dass Parameter an den gespeicherten Ort zurückkehren.
Das heisst, dass wenn man dies nicht macht,
werden Parameter immer bei erneutem Öffnen des Plug-In's
auf die Default werte zurückgesetzt.

Mit dem *APVTS* ist dies sehr einfach zu machen;

Datei: `PluginProcessor.cpp`
```c++
void AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}
```

```c++
void ExoDistAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid())
    {
        apvts.replaceState(tree);
    }
}
```
