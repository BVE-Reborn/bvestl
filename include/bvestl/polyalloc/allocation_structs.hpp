#pragma once

#include "foundational/allocation/bytes.hpp"

namespace foundational::allocation {
    /*!
     * Information about an allocation from an allocation strategy
     */
    struct AllocationInfo {
        /*!
         * \brief The size of the allocation, in bytes
         */
        Bytes size{0};

        /*!
         * The offset of the allocation, in bytes
         */
        Bytes offset{0};

        /*!
         * Data internal to the allocation strategy. For instance, a block allocator might store the block that this allocation corresponds
         * to
         */
        void* internal_data;
    };
} // namespace foundational::allocation
