#pragma once

#include "Processor.hpp"

class GainProcessor final : public Poss::Processor {
   public:
    virtual void processBlock(Poss::Buffer&) override;

    virtual void prepareToPlay(double sampleRate,
                               int maximumExpectedSamplesPerBlock) override;
    virtual void releaseResources() override;
};
