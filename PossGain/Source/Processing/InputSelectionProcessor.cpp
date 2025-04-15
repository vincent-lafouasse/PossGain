#include "InputSelectionProcessor.hpp"

#include <utility>
#include <algorithm>

#include "JuceHeader.h"

void InputSelectionProcessor::processBlock(Poss::Buffer& buffer) {
    if (this->mode == Mode::Swap) {
        std::swap_ranges(buffer.left, buffer.left + buffer.sz, buffer.right);
    } else if (this->mode == Mode::Left) {
        std::memcpy(buffer.right, buffer.left, buffer.sz * sizeof(float));
    } else if (this->mode == Mode::Right) {
        std::memcpy(buffer.left, buffer.right, buffer.sz * sizeof(float));
    }
    // do nothing if input mode is stereo
}

void InputSelectionProcessor::prepareToPlay(
    double /*sampleRate*/,
    int /*maximumExpectedSamplesPerBlock*/) {}
void InputSelectionProcessor::releaseResources() {}
