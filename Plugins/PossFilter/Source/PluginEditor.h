#pragma once

#include "PluginProcessor.h"

class PossFilterEditor : public juce::AudioProcessorEditor
{
public:
    explicit PossFilterEditor(PossFilterProcessor&);

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::GenericAudioProcessorEditor editor {processor};
};
