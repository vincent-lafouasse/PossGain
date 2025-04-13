#pragma once

#include "PossGain.hpp"

class GainKnob : public juce::Slider {
   public:
    juce::String getTextFromValue(double value) override;
};

class PossGainEditor : public juce::AudioProcessorEditor {
   public:
    explicit PossGainEditor(PossGainProcessor&);
    ~PossGainEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

   private:
    void setupGainKnob();
    PossGainProcessor& audioProcessor;

    GainKnob gainSlider;
    juce::Label gainLabel;

    juce::ToggleButton muteButton;

   public:
    juce::AudioProcessorValueTreeState::SliderAttachment gainSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PossGainEditor)
};
