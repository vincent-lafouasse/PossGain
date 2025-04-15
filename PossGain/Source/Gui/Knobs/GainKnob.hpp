#pragma once

#include "JuceHeader.h"

#include <cmath>
#include <iomanip>
#include <sstream>

class GainKnob : public juce::Slider {
   public:
    juce::String getTextFromValue(double value) override {
        if (value == 0.0)
            return "-inf dB";

        if (juce::approximatelyEqual(value, 1.0))
            return "0.00 dB";

        std::stringstream ss{};
        ss << std::setprecision(3);
        ss << 20.0 * std::log10(value);
        ss << " dB";
        return ss.str();
    }
};
