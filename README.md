# ExoDist

*ExoDist* is an easy to use audio plugin
designed to bring unique distortion to your sound.

Built on a custom distortion algorithm,
ExoDist processes incoming signals with precision,
delivering anything from subtle harmonic enhancement to extreme,
aggressive saturation.

## Features

- zero-latency
- easy user interface

## Getting ExoDist

Download the latest version [here](https://github.com/arcathrax/ExoDist/releases).
For installation, just download the `*.vst3.zip` file and extract it in your plug-in folder.

## Technical Stuff

- Written in C++
- Based on the [JUCE](https://juce.com) framework

## TODO
- [x] update `ExoAlgo` so it can be used in a `ProcessorChain`
- [ ] create a github pages website for the plugin
- [x] update UI
  - [x] add labels to sliders
  - [x] update how sliders look
  - [ ] update font
  - [x] update background
  - [ ] update background to be a gradient
- [x] update how the parameters are stored so they will be in the right position after reopening the project
- [x] add dry wet knob
- [ ] setup air for vocals
