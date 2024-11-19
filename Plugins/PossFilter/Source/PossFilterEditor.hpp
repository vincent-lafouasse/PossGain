/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include "PossFilter.hpp"

//==============================================================================
/**
 */
class PossFilterEditor : public juce::AudioProcessorEditor,
                         public juce::Slider::Listener {
   public:
    PossFilterEditor(PossFilterProcessor&);
    ~PossFilterEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

   private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PossFilterProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PossFilterEditor)
};
