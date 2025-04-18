#include "GainProcessor.hpp"

void GainProcessor::processBlock(Poss::Buffer& buffer) {
    float actual_gain;

    for (std::size_t sample = 0; sample < buffer.sz; ++sample) {
        actual_gain = gain.get();
        buffer.left[sample] = actual_gain * buffer.left[sample];
        buffer.right[sample] = actual_gain * buffer.right[sample];
    }
}

void GainProcessor::setTargetGain(float target) {
    gain.setTarget(target);
}

float GainProcessor::getCurrentGain() const {
    return gain.peek();
}

void GainProcessor::prepareToPlay(double sampleRate,
                                  int /*maximumExpectedSamplesPerBlock*/) {
    gain.setSampleRate(static_cast<float>(sampleRate));
    gain.setDecayUs(10000);
    gain.setTarget(0.0f);
}
void GainProcessor::releaseResources() {}
