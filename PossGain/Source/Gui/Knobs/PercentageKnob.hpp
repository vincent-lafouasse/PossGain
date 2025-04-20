#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include <cmath>

class PercentageKnob : public juce::Slider {
   public:
    juce::String getTextFromValue(double value) override {
        const int percentage = static_cast<int>(std::round(100.0 * value));

        return std::to_string(percentage) + "%";
    }
};
