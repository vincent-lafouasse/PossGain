# PossDSP

very cool plugins

Special thanks to @eyalamirmusic for the project template, and @sammithy for the guidance

## Plugins

- PossGain, a revolutionary plugin to control a signal's gain for proper gain staging.

## Build

- Run `cmake -B build -S .` from the root of the repository.
- Run `cmake --build build` to build all targets

Alternatively, you can build specific targets with `cmake --build build --target $TARGET_NAME`, with `TARGET_NAME` being among:
- `PossGain_All`
- `PossGain_VST3`
- `PossGain_AU`
- `PossGain_Standalone`
- `Noisemaker`

You will find the binaries in `./build/Plugins/${PLUGIN_NAME}/${PLUGIN_NAME}_artefacts/` for plugins, for example at `./build/Plugins/PossGain/PossGain_artefacts/` for the PossGain plugin
Similarly, you will find standalone apps in `./build/Apps/${APP_NAME}/${APP_NAME}_artefacts/`, for example at `./build/Plugins/Noisemaker/Noisemaker/` for the Noisemaker app

### To do

- PossNoiseGate, so you can control your signal's makeup.
- PossFilter, a toggleable highpass/lowpass filter with basic controls.
- PossEQ, a more elaborate tool with HPF, LPF, shelves and bells.

## JUCE CMake Repo Prototype
A prototype to model a way to create an entire repo using JUCE 6 and CMake.

This is inspired by a desire to keep the environment setting of my projects to minimum,
making sure the environment is identical for every developer/machine.

The main concept is to set all the different variables (where JUCE is, custom modules, etc) 
in the top CMakeLists.txt, then add all your projects with very little setup time.

Another important concept is to share all 'related' projects under the same configuration,
which I prefer, since it encourages code-sharing and build system settings sharing.
In some of the examples I added minimal usages of juce-style modules to illustrate how that
can be done.

To build, all you have to do is load this project in your favorite IDE 
(CLion/Visual Studio/VSCode/etc) 
and click 'build' for one of the targets (templates, JUCE examples, Projucer, etc).

You can also generate a project for an IDE by using (Mac):
```
cmake -G Xcode -B build
```
Windows:
```
cmake -G "Visual Studio 16 2022" -B build
```

For package management, I'm using the amazing CPM.cmake:
#https://github.com/TheLartians/CPM.cmake
It automatically fetches JUCE from git, but you can also set the variable:
CPM_JUCE_SOURCE to point it to a local folder, by using:
``-DCPM_JUCE_SOURCE="Path_To_JUCE"``
when invoking CMake

JUCE can be found here:
#https://github.com/juce-framework/JUCE

License:
Anything from me in this repo is completely free to use for any purpose. 
However, please check the licenses for CPM and JUCE as described in their repo. 
