#pragma once

#include "JuceHeader.h"

class BalanceKnob : public juce::Slider {
   public:
    juce::String getTextFromValue(double value) override {
        if (juce::approximatelyEqual(value, 0.5)) {
            return "C";
        }

        const int panAmount =
            static_cast<int>(std::round(std::fabs(value * 100.0 - 50.0)));
        const char* panDirection = value > 0.5 ? "R" : "L";

        return std::to_string(panAmount) + panDirection;
    }
};
