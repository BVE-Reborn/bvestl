#pragma once

#include "foundational/allocation/bytes.hpp"

namespace foundational::allocation {
    struct AllocationInfo;

    class SizeOnlyAllocator {
    public:
        virtual ~SizeOnlyAllocator() = default;

        virtual bool allocate(Bytes size, AllocationInfo& allocation) = 0;

        virtual void free(const AllocationInfo& alloc) = 0;
    };
}
