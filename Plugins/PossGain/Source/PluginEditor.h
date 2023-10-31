#pragma once

#include "PluginProcessor.h"

class PossGainEditor : public juce::AudioProcessorEditor
{
public:
    explicit PossGainEditor(PossGainProcessor&);

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::GenericAudioProcessorEditor editor {processor};
};
