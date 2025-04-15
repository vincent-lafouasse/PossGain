#pragma once

#include "InputPanel.hpp"
#include "OutputPanel.hpp"
#include "PossGain.hpp"

class PossGainEditor : public juce::AudioProcessorEditor {
   public:
    explicit PossGainEditor(PossGainProcessor&);
    ~PossGainEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

   private:
    [[maybe_unused]] PossGainProcessor& audioProcessor;
    InputPanel inputPanel;
    OutputPanel outputPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PossGainEditor)
};
