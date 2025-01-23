# Erstellung
Ein *AudioPlugin* ist eine Typ von Applikation in Projucer bzw. JUCE.
Um dies zu Erstellen muss man bei Projucer auf `File>New Project` clicken.
Nun sollte man auf der linken Seite der Applikation `Plug-In>Basic` auswählen können.

Man sollte den Namen ändern und bei Bedarf nocht Module hinzufügen.

# Was beinhaltet ein AudioPlugin?
Ein *AudioPlugin* beinhaltet minimalen Code,
welcher für ein Audio Plugin benötigt wird.

Hierzu gehören folgende Files:
- `PluginProcessor.cpp`
- `PluginProcessor.h`
- `PluginEditor.cpp`
- `PluginEditor.h`

## Die `PluginProcessor` Klasse
Dies ist die Klasse,
welche für die Verarbeitung der Audio verwendet wird.

Diese Klasse beinhaltet mehrere verschiedene Funktionen,
wobei die *prepareToPlay* und die *processBlock* die wichtigsten sind.

### Prepare to Play

Dies ist die Funktion,
welche verwendet wird,
bevor Audio abgespielt wird.

Hier werden also z.B.
Filter initialisiert,
Defaultparameter an Klassen übergeben
oder aber auch *ProcessorChains* vorbereitet.

```c++
void ExoDistAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}
```

### Process Block

Dies ist die Funktion,
in welcher das Audiosignal tatsächlich
verändert wird.

```c++
void ExoDistAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // clear unused input channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        // ..do something to the data...
    }
}
```
## Die `PluginEditor` Klasse
Dies ist die Klasse,
welche die UI definiert.
In einem JUCE-AudioPlugin sollte
nur eine `PluginEditor` Klasse existieren.

In dieser Klasse gibt es vier Funktionen.
Die *paint* Funktion und die *resized* Funktion sind hierbei die wichtigsten.

### Paint
Hier wird der initialwert des Fensters definiert.
Das heisst hier wird definiert,
was auf dem Fenster angezeigt wird und
wie es aussehen soll.

```c++
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}
```

### Resized
Hier werden die Elemente angeordnet.
Z.B. wird hier definiert wie gross die Elemente sind.
So kann z.B. ein Knob immer 1/3 des Bildschirmes einnehmen und
somit passt dieser sich an die Grösse des Fensters an.

```c++
void NewProjectAudioProcessorEditor::resized()
{
}
```
