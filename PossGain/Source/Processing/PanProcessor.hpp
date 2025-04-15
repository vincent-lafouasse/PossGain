#pragma once

#include "ProcessorBase/Processor.hpp"

#include <array>

class PanProcessor final : public Poss::Processor {
   public:
    PanProcessor() = default;
    ~PanProcessor() = default;
    virtual void processBlock(Poss::Buffer&) override;

    virtual void prepareToPlay(double sampleRate,
                               int maximumExpectedSamplesPerBlock) override;
    virtual void releaseResources() override;

    void setTargetPan(float);

   private:
    std::array<float, 2> balance{};
    std::array<float, 2> targetBalance{};

    static constexpr float smoothingForwardWeight = 0.05f;
};
