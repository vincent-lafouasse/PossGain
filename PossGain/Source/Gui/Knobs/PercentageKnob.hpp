#pragma once

#include "JuceHeader.h"

#include <cmath>

class PercentageKnob : public juce::Slider {
   public:
    juce::String getTextFromValue(double value) override {
        const int percentage = static_cast<int>(std::round(100.0 * value));

        return std::to_string(percentage) + "%";
    }
};
