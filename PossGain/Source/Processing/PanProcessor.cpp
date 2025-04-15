#include "PanProcessor.hpp"

#include <cassert>

#include "JuceHeader.h"

#define LEFT 0
#define RIGHT 1

void PanProcessor::processBlock(Poss::Buffer& buffer) {
    for (std::size_t sample = 0; sample < buffer.sz; ++sample) {
        buffer.left[sample] = this->balance[LEFT] * buffer.left[sample];
        buffer.right[sample] = this->balance[RIGHT] * buffer.right[sample];

        for (std::size_t channel = 0; channel < 2; ++channel) {
            if (!juce::approximatelyEqual(balance[channel],
                                          targetBalance[channel])) {
                balance[channel] =
                    smoothingForwardWeight * targetBalance[channel] +
                    (1.0f - smoothingForwardWeight) * balance[channel];
            }
        }
    }
}

void PanProcessor::setTargetPan(float pan) {
    float reducedGain = 1.0f - 2.0f * std::fabs(pan - 0.5f);

    if (pan > 0.5f) {
        this->targetBalance[LEFT] = reducedGain;
        this->targetBalance[RIGHT] = 1.0f;
        ;
    } else {
        this->targetBalance[LEFT] = 1.0f;
        ;
        this->targetBalance[RIGHT] = reducedGain;
    }
}

void PanProcessor::prepareToPlay(double /*sampleRate*/,
                                 int /*maximumExpectedSamplesPerBlock*/) {
    assert(PanProcessor::smoothingForwardWeight > 0.0f &&
           PanProcessor::smoothingForwardWeight < 1.0f);
}
void PanProcessor::releaseResources() {}
