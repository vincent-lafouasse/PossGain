/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include "PossGain.hpp"

//==============================================================================
/**
 */
class PossGainEditor : public juce::AudioProcessorEditor,
                       public juce::Slider::Listener {
   public:
    PossGainEditor(PossGainProcessor&);
    ~PossGainEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

   private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PossGainProcessor& audioProcessor;

    juce::Slider logGainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PossGainEditor)
};
