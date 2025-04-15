#include "GainProcessor.hpp"

#include <cassert>

#include "JuceHeader.h"

void GainProcessor::processBlock(Poss::Buffer& buffer) {
    for (std::size_t sample = 0; sample < buffer.sz; ++sample) {
        buffer.left[sample] = this->gain * buffer.left[sample];
        buffer.right[sample] = this->gain * buffer.right[sample];

        if (!juce::approximatelyEqual(this->gain, this->targetGain)) {
            this->gain =
                GainProcessor::smoothingForwardWeight * this->targetGain +
                (1.0f - GainProcessor::smoothingForwardWeight) * this->gain;
        }
    }
}

void GainProcessor::setTargetGain(float target) {
    this->targetGain = target;
}

float GainProcessor::getCurrentGain() const {
    return this->gain;
}

void GainProcessor::prepareToPlay(double /*sampleRate*/,
                                  int /*maximumExpectedSamplesPerBlock*/) {
    assert(GainProcessor::smoothingForwardWeight > 0.0f &&
           GainProcessor::smoothingForwardWeight < 1.0f);
}
void GainProcessor::releaseResources() {}
