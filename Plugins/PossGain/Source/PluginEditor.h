/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PossGainAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    PossGainAudioProcessorEditor(PossGainAudioProcessor&);
    ~PossGainAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PossGainAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PossGainAudioProcessorEditor)
};
