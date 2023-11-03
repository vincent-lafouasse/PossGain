#pragma once

#include <array>

class StereoSignalSmoother
{
public:
    StereoSignalSmoother()
        : target(0)
        , forwardWeight(0.9f)
        , inertiaWeight(0.1f)
        , memory({0, 0})
    {
    }
    void setTarget(float newTarget) { this->target = newTarget; }
    void advance(size_t channel)
    {
        memory[channel] = forwardWeight * target + inertiaWeight * memory[channel];
    }
    float get(size_t channel)
    {
        advance(channel);
        return memory[channel];
    }

private:
    float target;
    float forwardWeight;
    float inertiaWeight;
    std::array<float, 2> memory;
};
