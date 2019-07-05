#pragma once

#include "foundational/allocation/bytes.hpp"

/*!
 * \brief Some useful utilities
 */

namespace foundational::allocation {
    constexpr EA_FORCE_INLINE Bytes align(const Bytes value, const Bytes alignment) noexcept {
        return ((value + (alignment - 1)) & ~(alignment - 1));
    }
} // namespace foundational::allocation
