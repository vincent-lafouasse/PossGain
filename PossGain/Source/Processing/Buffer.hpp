#pragma once

#include <cstddef>

namespace Poss {
struct Buffer {
    float* left;
    float* right;
    std::size_t sz;
};
}  // namespace Poss
