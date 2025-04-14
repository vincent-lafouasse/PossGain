#pragma once

#include "JuceHeader.h"
#include "PercentageKnob.hpp"
#include "PossGain.hpp"

class InputPanel final : public juce::Component {
   public:
    InputPanel(PossGainProcessor&);
    ~InputPanel() override;
    void paint(juce::Graphics&) override;
    void resized() override;

   private:
    void setupWidthSlider();

    PossGainProcessor& processor;

    juce::Label heading;

    PercentageKnob widthSlider;
    juce::Label widthLabel;

   public:
    // juce::AudioProcessorValueTreeState::SliderAttachment
    // gainSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputPanel)
};
