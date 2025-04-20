#include "gtest/gtest.h"

#include <vector>

#include "Processing/GainProcessor.hpp"

namespace {
constexpr float sampleRate = 1e6f;  // 1 us per sample
constexpr std::size_t nSamplesOneMillisecond =
    static_cast<std::size_t>(1e-3f * sampleRate);
constexpr int ignored = 0;
}  // namespace

TEST(GainProcessor, NewGainProcessorHasZeroGain) {
    GainProcessor processor{};

    ASSERT_FLOAT_EQ(processor.getCurrentGain(), 0.0);
}

TEST(GainProcessor, ReachesThresholdOnTime) {
    GainProcessor processor{};
    processor.setTargetGain(0.0f);
    processor.prepareToPlay(sampleRate, ignored);

    constexpr std::size_t decayMs = 10;

    constexpr std::size_t sz = 1000;
    std::vector left(sz, 1.0f);
    std::vector right(sz, 1.0f);

    Poss::Buffer buffer{&left.front(), &right.front(), sz};

    processor.setTargetGain(0.0f);
    processor.processBlock(buffer);

    ASSERT_FLOAT_EQ(processor.getCurrentGain(), 0.0f);
}
