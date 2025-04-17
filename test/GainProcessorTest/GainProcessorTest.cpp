#include "gtest/gtest.h"

#include "Processing/GainProcessor.hpp"

TEST(GainProcessor, Dummy)
{
    GainProcessor processor {};
    (void)processor;
    SUCCEED();
}
