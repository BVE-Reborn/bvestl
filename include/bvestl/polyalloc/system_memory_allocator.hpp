#pragma once

#include "bvestl/api.hpp"
#include "bvestl/polyalloc/polyalloc.hpp"
#include <EASTL/unique_ptr.h>
#include "bytes.hpp"
#include <EASTL/unordered_map.h>
#include "bvestl/polyalloc/allocation_structs.hpp"

namespace bvestl {
	namespace polyalloc {
		class BVESTL_EXPORT AllocationStrategy;

		/*!
		 * \brief A coupling of a memory resource and a allocator. Allows all the fun of allocating memory _and_ the fun of
		 * not understanding how this system works
		 */
		class BVESTL_EXPORT SystemMemoryAllocator : public Allocator {
		public:
			/*!
			 * \brief Constructs a CPU Allocated memory object with a region of memory and the allocation strategy to use
			 *
			 * \param memory A pointer to the region of memory to allocate from
			 * \param size The size of the region of memory region
			 * \param alloc_strategy The allocation strategy to use when allocating memory
			 */
			SystemMemoryAllocator(uint8_t* memory, const Bytes size, eastl::unique_ptr<AllocationStrategy> alloc_strategy) : memory(memory), memory_size(size), alloc_strategy(std::move(alloc_strategy)) {}

			~SystemMemoryAllocator() override = default;

			void* allocate(size_t n, int flags) override;

			void* allocate(size_t n, size_t alignment, size_t offset, int flags) override;

			void deallocate(void* p, size_t n) override;

		private:
			uint8_t* memory;
			const Bytes memory_size;
			eastl::unique_ptr<AllocationStrategy> alloc_strategy;
			eastl::unordered_map<void*, AllocationInfo> allocation_infos;
		};
	}
}
