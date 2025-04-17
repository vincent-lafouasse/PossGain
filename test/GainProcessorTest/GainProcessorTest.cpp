#include "gtest/gtest.h"

#include <vector>

#include "Processing/GainProcessor.hpp"

TEST(GainProcessor, NewGainProcessorHasZeroGain) {
    GainProcessor processor{};

    ASSERT_FLOAT_EQ(processor.getCurrentGain(), 0.0);
}

TEST(GainProcessor, NullsASignalWithin1000Samples) {
    GainProcessor processor{};

    constexpr std::size_t sz = 1000;
    std::vector left(sz, 1.0f);
    std::vector right(sz, 1.0f);

    Poss::Buffer buffer{&left.front(), &right.front(), sz};

    processor.setTargetGain(0.0f);
    processor.processBlock(buffer);

    ASSERT_FLOAT_EQ(processor.getCurrentGain(), 0.0f);
}
