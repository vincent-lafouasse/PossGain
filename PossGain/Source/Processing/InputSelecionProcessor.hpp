#pragma once

#include "ProcessorBase/Processor.hpp"

#include <vector>

class InputSelectionProcessor final : public Poss::Processor {
   public:
    InputSelectionProcessor() = default;
    ~InputSelectionProcessor() = default;
    virtual void processBlock(Poss::Buffer&) override;

    virtual void prepareToPlay(double sampleRate,
                               int maximumExpectedSamplesPerBlock) override;
    virtual void releaseResources() override;

    enum Mode {
        Stereo = 1,
        Left = 2,
        Right = 3,
        Swap = 4,
    };

    void setMode(Mode mode);

    static std::vector<const char*> inputModeNames() {
        return {"Stereo", "Left ", "Right ", "Swap"};
    }

   private:
    Mode mode = Mode::Stereo;
};
