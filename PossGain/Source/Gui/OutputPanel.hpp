#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Knobs/BalanceKnob.hpp"
#include "Knobs/GainKnob.hpp"
#include "PossGain.hpp"


class OutputPanel final : public juce::Component {
   public:
    explicit OutputPanel(PossGainProcessor&);
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
