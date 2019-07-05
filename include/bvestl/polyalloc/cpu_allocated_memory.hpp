#pragma once

#include "bvestl/polyalloc/polyalloc.hpp"

namespace bvestl {
	namespace polyalloc {
		/*!
		 * \brief A coupling of a memory resource and a allocator. Allows all the fun of allocating memory _and_ the fun of
		 * not understanding how this system works
		 */
		class CpuAllocatedMemory : public allocator {
		public:
			CpuAllocatedMemory(size_t)

				~CpuAllocatedMemory() override;

			void* allocate(size_t n, int flags) override;

			void* allocate(size_t n, size_t alignment, size_t offset, int flags) override;

			void deallocate(void* p, size_t n) override;
		};
	}
}
