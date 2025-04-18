#pragma once

#include <cmath>
#include "JuceHeader.h"

// a 1 pole low pass filter that smoothes step functions
// of the form y[n] = beta * y[n - 1] + (1 - beta) * x[n]
// where ln(beta) = - twoPi / (tau * sampleRate)
//
template <typename FloatType>
class Smoothed {
   public:
    Smoothed();

    void setSampleRate(float newSampleRate) {
        this->sampleRate = newSampleRate;
    }

    void setDecayUs(int decayUs) {
        constexpr float threshold = 0.99f;
        float tau =
            1e-6f * static_cast<float>(decayUs) / (-std::log(threshold));
        this->beta = std::exp(-1.0 / (tau * this->sampleRate));
    }

    void setTarget(FloatType target) { this->target = target; }

    FloatType get() {
        if (juce::approximatelyEqual(this->memory, this->target)) {
            return this->target;
        }
        memory = beta * memory + (1.0f - beta) * target;
        return memory;
    }

   private:
    FloatType memory;
    FloatType target;

    float beta;
    float sampleRate = 44100;
};
