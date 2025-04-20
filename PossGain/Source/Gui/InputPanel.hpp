#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Knobs/PercentageKnob.hpp"
#include "PossGain.hpp"

class InputPanel final : public juce::Component {
   public:
    explicit InputPanel(PossGainProcessor&);
    ~InputPanel() override;
    void paint(juce::Graphics&) override;
    void resized() override;

   private:
    void setupWidthSlider();

    [[maybe_unused]] PossGainProcessor& processor;

    juce::Label heading;

    juce::TextButton leftPhaseInvertButton;
    juce::TextButton rightPhaseInvertButton;

    juce::ComboBox inputMode;

    PercentageKnob widthSlider;
    juce::Label widthLabel;

    juce::TextButton monoButton;

    juce::TextButton bassMonoButton;

    juce::TextButton bassMonoCutoffButton;
    juce::TextButton bassMonoAudiationButton;

   public:
    // juce::AudioProcessorValueTreeState::SliderAttachment
    // gainSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputPanel)
};
