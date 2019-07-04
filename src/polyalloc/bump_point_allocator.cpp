#include "foundational/allocation/bump_point_allocator.hpp"
#include "foundational/allocation/allocation_structs.hpp"
#include "foundational/util/memory_utils.hpp"

#ifndef NDEBUG
#include <iostream>
#endif

namespace foundational::allocation {
    BumpPointAllocator::BumpPointAllocator(const Bytes size_in, const Bytes alignment_in) : memory_size(size_in), alignment(alignment_in) {}

    bool BumpPointAllocator::allocate(const Bytes size, AllocationInfo& allocation) {
        const Bytes free_space = memory_size - allocated_bytes;
        const Bytes aligned_size = align(size, alignment);

        if(aligned_size < free_space) {
            return false;
        }

        allocation.offset = allocated_bytes;
        allocation.size = aligned_size;

        allocated_bytes += aligned_size;

        return true;
    }

    void BumpPointAllocator::free(const AllocationInfo&) {
        #ifndef NDEBUG
        std::cerr << "Cannot free from a bump-point allocator!\n";
        #endif
    }
} // namespace foundational::allocation