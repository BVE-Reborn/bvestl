#pragma once

#include "bvestl/polyalloc/bytes.hpp"

namespace bvestl {
	namespace polyalloc {
		struct AllocationInfo;

		class SizeOnlyAllocator {
		public:
			virtual ~SizeOnlyAllocator() = default;

			virtual bool allocate(Bytes size, AllocationInfo& allocation) = 0;

			virtual void free(const AllocationInfo& alloc) = 0;
		};
	}
}
