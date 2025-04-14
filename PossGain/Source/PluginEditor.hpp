#pragma once

#include "PossGain.hpp"

class GainKnob : public juce::Slider {
   public:
    juce::String getTextFromValue(double value) override;
};

class BalanceKnob : public juce::Slider {
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
    void setupOutputPanelLabel();
    void setupGainKnob();
    void setupBalanceKnob();
    PossGainProcessor& audioProcessor;

    juce::Label outputPanelLabel;

    GainKnob gainSlider;
    juce::Label gainLabel;

    BalanceKnob balanceSlider;
    juce::Label balanceLabel;

    juce::TextButton muteButton;
    juce::TextButton dcCutButton;

   public:
    juce::AudioProcessorValueTreeState::SliderAttachment gainSliderAttachment;
    juce::AudioProcessorValueTreeState::ButtonAttachment muteButtonAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PossGainEditor)
};
