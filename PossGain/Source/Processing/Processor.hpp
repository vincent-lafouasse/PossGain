#pragma once

#include "Buffer.hpp"

namespace Poss {
class Processor {
   public:
    virtual void processBlock(Buffer&) = 0;

    virtual void prepareToPlay(double sampleRate,
                               int maximumExpectedSamplesPerBlock) = 0;
    virtual void releaseResources() = 0;
};
}  // namespace Poss
