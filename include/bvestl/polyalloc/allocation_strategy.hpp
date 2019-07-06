#pragma once

#include "bvestl/api.hpp"
#include "bvestl/polyalloc/bytes.hpp"

namespace bvestl {
	namespace polyalloc {
		struct BVESTL_EXPORT AllocationInfo;

        /*!
         * \brief Interface for an allocation strategy
         */
		class BVESTL_EXPORT AllocationStrategy {
		public:
			virtual ~AllocationStrategy() = default;

			virtual bool allocate(Bytes size, AllocationInfo& allocation) = 0;

			virtual void free(const AllocationInfo& alloc) = 0;
		};
	}
}
