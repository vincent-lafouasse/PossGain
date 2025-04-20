#pragma once

#include <cmath>
#include <juce_core/juce_core.h>

namespace Poss {

// a 1 pole low pass filter that smoothes step functions
// of the form y[n] = beta * y[n - 1] + (1 - beta) * x[n]
// where ln(beta) = - twoPi / (tau * sampleRate)
//
template <typename FloatType>
class Smoothed {
   public:
    Smoothed() = default;

    void setSampleRate(float newSampleRate) {
        this->sampleRate = newSampleRate;
    }

    void setDecayUs(int decayUs) {
        constexpr float threshold = 0.99f;
        float tau =
            1e-6f * static_cast<float>(decayUs) / (-std::log(threshold));
        this->beta = std::expf(-1.0f / (tau * this->sampleRate));
    }

    void setTarget(FloatType newTarget) { this->target = newTarget; }

    FloatType get() {
        if (juce::approximatelyEqual(this->memory, this->target)) {
            return this->target;
        }
        memory = beta * memory + (1.0f - beta) * target;
        return memory;
    }

    FloatType peek() const { return this->memory; }

   private:
    FloatType memory;
    FloatType target;

    float beta;
    float sampleRate = 44100;
};
}  // namespace Poss
