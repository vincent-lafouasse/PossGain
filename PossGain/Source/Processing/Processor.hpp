#pragma once

#include "Buffer.hpp"

namespace Poss {
class Processor {
public:
    virtual void processBlock(Buffer&) = 0;
};
}
