#pragma once

#include "ProcessorBase/Processor.hpp"

class GainProcessor final : public Poss::Processor {
   public:
    GainProcessor() = default;
    ~GainProcessor() = default;
    virtual void processBlock(Poss::Buffer&) override;

    virtual void prepareToPlay(double sampleRate,
                               int maximumExpectedSamplesPerBlock) override;
    virtual void releaseResources() override;

    void setTargetGain(float);
    float getCurrentGain() const;

   private:
    float targetGain{};
    float gain{};
    static constexpr float smoothingForwardWeight = 0.05f;
};
