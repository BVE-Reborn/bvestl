#pragma once

#include <cstdlib>
#include <EABase/config/eacompilertraits.h>
#include <EASTL/internal/config.h>

namespace eastl::polyalloc {
	class allocator {
	  public:
		allocator() = default;
		allocator(allocator const&) = delete;
		allocator(allocator&&) = delete;
		allocator& operator=(allocator const&) = delete;
		allocator& operator=(allocator&&) = delete;

		virtual void* allocate(size_t n, int flags = 0) = 0;
		virtual void* allocate(size_t n, size_t alignment, size_t offset, int flags = 0) = 0;
		virtual void deallocate(void* p, size_t n) = 0;
	};

	class allocator_handle {
	  public:
		EA_FORCE_INLINE allocator_handle(Allocator* allocator, char const* = nullptr) : allocator_(allocator) {}

		EA_FORCE_INLINE allocator_handle(const allocator_handle& x, char const* = nullptr) : allocator_(x.allocator_) {}

		EA_FORCE_INLINE ~allocator_handle() = default;

		EA_FORCE_INLINE allocator_handle& operator=(const allocator_handle& x) = default;

		EA_FORCE_INLINE void* allocate(size_t n, int flags = 0) {
			return allocator_->allocate(n, flags);
		}

		EA_FORCE_INLINE void* allocate(size_t n, size_t alignment, size_t offset, int flags = 0) {
			return allocator_->allocate(n, alignment, offset, flags);
		}

		EA_FORCE_INLINE void deallocate(void* p, size_t n) {
			allocator_->deallocate(p, n);
		}

		EA_FORCE_INLINE char const* get_name() const {
			return "EASTL Polyalloc Allocator Handle";
		}

		EA_FORCE_INLINE void set_name(char const*) {}

		EA_FORCE_INLINE bool operator==(allocator_handle const& rhs) const {
			return allocator_ == rhs.allocator_;
		}

		EA_FORCE_INLINE bool operator!=(allocator_handle const& rhs) const {
			return !(rhs == *this);
		}

	  private:
		allocator* allocator_;
	};
}
