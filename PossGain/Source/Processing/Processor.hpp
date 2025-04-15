#pragma once

#include "JuceHeader.h"

namespace Poss {
class Processor {
public:
    virtual void processBlock(juce::AudioBuffer<float>&) = 0;
};
}
