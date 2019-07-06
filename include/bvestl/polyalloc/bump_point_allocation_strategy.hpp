#pragma once

#include "bvestl/api.hpp"
#include "bvestl/polyalloc/bytes.hpp"
#include "bvestl/polyalloc/allocation_strategy.hpp"

namespace bvestl {
	namespace polyalloc {
		struct BVESTL_EXPORT AllocationInfo;

		/*!
		 * \brief Allocates memory linearly from a single pool. Memory must be freed all at once, there's no support for freeing individual
		 * allocations
		 */
		class BVESTL_EXPORT BumpPointAllocationStrategy final : public AllocationStrategy {
		public:
			struct Allocation {
				Bytes offset{ 0 };
				Bytes size{ 0 };
			};

			explicit BumpPointAllocationStrategy(Bytes size_in, Bytes alignment_in = Bytes(0));

			bool allocate(Bytes size, AllocationInfo& allocation) override final;

			void free(const AllocationInfo&) override final;

		private:
			Bytes memory_size;
			Bytes alignment;

			Bytes allocated_bytes{ 0 };
		};
	}
}
