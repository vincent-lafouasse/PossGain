#pragma once

#include "JuceHeader.h"
#include "PossGain.hpp"

class OutputPanel final : public juce::Component {
   public:
    OutputPanel(PossGainProcessor&);
    ~OutputPanel() override;
    void paint(juce::Graphics&) override;
    void resized() override;

   private:
    PossGainProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OutputPanel)
};
