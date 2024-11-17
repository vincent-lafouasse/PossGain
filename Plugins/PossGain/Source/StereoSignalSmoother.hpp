#pragma once

#include <array>

template <typename T>
class StereoSignalSmoother {
   public:
    StereoSignalSmoother()
        : target(0), forwardWeight(0.9f), inertiaWeight(0.1f), memory({0, 0}) {}
    void setTarget(T newTarget) { this->target = newTarget; }
    void advance(size_t channel) {
        memory[channel] =
            forwardWeight * target + inertiaWeight * memory[channel];
    }
    float get(size_t channel) {
        advance(channel);
        return memory[channel];
    }

   private:
    T target;
    T forwardWeight;
    T inertiaWeight;
    std::array<T, 2> memory;
};
