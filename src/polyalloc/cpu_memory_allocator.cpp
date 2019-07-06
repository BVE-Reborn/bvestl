#include "bvestl/polyalloc/cpu_memory_allocator.hpp"
#include "bvestl/polyalloc/allocation_strategy.hpp"

namespace bvestl {
	namespace polyalloc {

		void* CpuMemoryAllocator::allocate(const size_t n, const int /* flags */) {
			AllocationInfo alloc_info = {};
			alloc_strategy->allocate(Bytes(n), alloc_info);

			uint8_t* allocated_memory = &memory[alloc_info.offset.b_count()];
			allocation_infos.emplace(allocated_memory, alloc_info);

			return allocated_memory;
		}

        void* CpuMemoryAllocator::allocate(const size_t n, const size_t /* alignment */, const size_t /* offset */, const int flags) {
			return allocate(n, flags);
		}

        void CpuMemoryAllocator::deallocate(void* p, const size_t /* n */) {			
			const AllocationInfo info = allocation_infos.at(p);

			alloc_strategy->free(info);
			
		    allocation_infos.erase(p);
		}
    }
}