#pragma once

#include "bvestl/polyalloc/bytes.hpp"
#include "size_only_allocator.hpp"

namespace bvestl {
	namespace polyalloc {
		struct AllocationInfo;

		/*!
		 * \brief Allocated memory linearly from a single pool. Memory must be freed all at once, there's no support for freeing individual
		 * allocations
		 */
		class BumpPointAllocator final : public SizeOnlyAllocator {
		public:
			struct Allocation {
				Bytes offset{ 0 };
				Bytes size{ 0 };
			};

			explicit BumpPointAllocator(Bytes size_in, Bytes alignment_in = Bytes(0));

			bool allocate(Bytes size, AllocationInfo& allocation) override final;

			void free(const AllocationInfo&) override final;

		private:
			Bytes memory_size;
			Bytes alignment;

			Bytes allocated_bytes{ 0 };
		};
	}
}
