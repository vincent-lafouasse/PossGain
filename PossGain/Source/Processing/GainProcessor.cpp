#include "GainProcessor.hpp"

void GainProcessor::processBlock(Poss::Buffer& buffer) {
    (void)buffer;
}

void GainProcessor::prepareToPlay(double /*sampleRate*/,
                                  int /*maximumExpectedSamplesPerBlock*/) {}
void GainProcessor::releaseResources() {}
