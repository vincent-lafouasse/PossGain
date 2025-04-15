#include "GainProcessor.hpp"

#include <cassert>

void GainProcessor::processBlock(Poss::Buffer& buffer) {
    (void)buffer;
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
