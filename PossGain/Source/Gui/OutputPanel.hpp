#pragma once

#include "BalanceKnob.hpp"
#include "GainKnob.hpp"
#include "JuceHeader.h"
#include "PossGain.hpp"

class OutputPanel final : public juce::Component {
   public:
    OutputPanel(PossGainProcessor&);
    ~OutputPanel() override;
    void paint(juce::Graphics&) override;
    void resized() override;

   private:
    void setupGainKnob();
    void setupBalanceKnob();

    [[maybe_unused]] PossGainProcessor& processor;

    juce::Label heading;

    GainKnob gainSlider;
    juce::Label gainLabel;

    BalanceKnob balanceSlider;
    juce::Label balanceLabel;

    juce::TextButton muteButton;
    juce::TextButton dcCutButton;

   public:
    juce::AudioProcessorValueTreeState::SliderAttachment gainSliderAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment
        balanceSliderAttachment;
    juce::AudioProcessorValueTreeState::ButtonAttachment muteButtonAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OutputPanel)
};
