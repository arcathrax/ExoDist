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

## Die `PluginEditor` Klasse
Dies ist die Klasse,
welche die UI definiert.
In einem JUCE-AudioPlugin sollte
nur eine `PluginEditor` Klasse existieren.
