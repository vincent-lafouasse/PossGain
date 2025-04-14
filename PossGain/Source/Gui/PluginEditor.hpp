#pragma once

#include "OutputPanel.hpp"
#include "PossGain.hpp"

class PossGainEditor : public juce::AudioProcessorEditor {
   public:
    explicit PossGainEditor(PossGainProcessor&);
    ~PossGainEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

   private:
    PossGainProcessor& audioProcessor;
    OutputPanel outputPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PossGainEditor)
};
