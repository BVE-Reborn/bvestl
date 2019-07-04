#pragma once

#include <cstdint>

#include <EASTL/vector.h>

#include <bvestl/polyalloc/polyalloc.hpp>
#include "foundational/allocation/bytes.hpp"
#include "size_only_allocator.hpp"

namespace foundational::allocation {
    struct AllocationInfo;

    /*!
     * \brief An block allocator for GPU memory
     *
     * This class is meant to exist alongside an actual GPU memory allocation, either a VkMemory or an ID3D12Heap. This class only provides
     * offsets into the actual GPU memory, it doesn't do anything with the GPU memory itself. Therefore it doesn't have any notion of device
     * local or host coherent memory, because that's handled at a higher level
     *
     * There is nothing GPU-specific in this class and perhaps one day it'll have a name to reflect that
     */
    class BlockAllocator final : public SizeOnlyAllocator {
        // Basically the allocator from https://www.fasterthan.life/blog/2017/7/13/i-am-graphics-and-so-can-you-part-4- but I've changed it
        // so my allocator only deals with sizes and offsets, and doesn't care about memory types at all
    public:
        struct Block {
            uint64_t id = 0;

            Bytes size{0};
            Bytes offset{0};

            Block* previous = nullptr;
            Block* next = nullptr;

            bool free = true;
        };

        /*!
         * \brief Initializes this allocator with the total size of the memory it can work with
         *
         * \param allocator_in The allocator to use when allocating internally
         * \param size The size of the memory that this boi can allocate from
         * \param alignment_in The alignment of all allocations from this allocator
         */
        BlockAllocator(bvestl::polyalloc::allocator_handle& allocator_in, Bytes size, Bytes alignment_in = Bytes(0));

        ~BlockAllocator();

        /*!
         * \brief Allocates the specified amount of memory, filling out `allocation` if the allocation is successful
         *
         * This method finds the first free block that's large enough to allocate from. If the block is larger than the requested size, it's
         * shrunk to the requested and a new block is created to represent the free space
         *
         * \param size The size of your allocation
         * \param allocation The struct to fill out with information about the allocation
         * \return True if the allocation succeeds, false otherwise. The allocation can only fail if you're out of memory
         */
        bool allocate(Bytes size, AllocationInfo& allocation) override final;

        void free(const AllocationInfo& alloc) override final;

    private:
        bvestl::polyalloc::allocator_handle& allocator;

        Block* head;

        Bytes memory_size{0};
        Bytes alignment{0};

        Bytes allocated{0};

        uint64_t next_block_id = 0;

        Block* make_new_block(Bytes offset, Bytes size);
    };
} // namespace foundational::allocation
