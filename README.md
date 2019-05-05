# eastl-polyalloc

Allocation is a tricky problem. The solution to that problem is almost always polymorphic allocators. That is all fine
until you want to use external libraries that are using a different class for their polymorphic allocator than you are.
This conflict means your containers are incompatible and requires unnecessary copies to happen.

This attempts to solve that issue. By presenting a standard polymorphic allocator that everyone can use, it means everyone
will be using the same polymorphic allocator class and will all be able to use containers passed to and from. You still
have to be mindful of new/deleting across dlls, but you can easily get around this by letting your library consume a
polymorphic allocator to do all its allocation.

**NOTE:** I'm not associated with EA or EASTL in any way, I'm just trying to be helpful :)

## Usage

`allocator_handle` is what you pass between functions or pass around inside containers. These are handles to a child of
`allocator`. The `allocator` is the class that has the heap and does the allocation. The allocator_handle is a nice wrapper
that provides the semantics that EASTL and libraries need. The pointer to an allocator that you hand to the `allocator_handle`
is **non-owning**. You are responsible for ensuring the allocator has a lifetime long enough.

```cpp
#include <EASTL/polyalloc/polyalloc.h> // For allocator_handle
#include <EASTL/vector.h>              // For vector

using eastl::polyalloc::allocator_handle;

void my_func(eastl::vector<int, allocator_handle> vector) {
    // consume vector

    // vector will be destroyed safely because it will call deallocator given to it at construction
}

eastl::vector<int, allocator_handle> my_ret_func(allocator_handle handle) {
    // All memory is allocated using the allocator passed by the callee
    // preventing nasty issues with new/delete across DLLs.
    
    eastl::vector<int, allocator_handle> ret(handle);
    // do something
    return ret;
}
```

### Custom Allocators

To demonstrate how to make your own allocator, the following is an example of a malloc allocator.

```cpp
#include <EASTL/polyalloc/polyalloc.h> // For allocator
#include <cstdlib>                     // For malloc, aligned_alloc, free

using eastl::polyalloc::allocator;

class mallocator : allocator {
  public:
    mallocator() = default;
    mallocator(mallocator const&) = delete;
    mallocator(mallocator&&) = delete;
    mallocator& operator=(mallocator const&) = delete;
    mallocator& operator=(mallocator&&) = delete;

    void* allocate(size_t n, int flags = 0) override {
        return malloc(n);
    }
    void* allocate(size_t n, size_t alignment, size_t offset, int flags = 0) override {
        return aligned_alloc(n, alignment);
    }
    void deallocate(void* p, size_t n) override {
        free(p);
    }
};
```

This Mallocator can then be easily used:

```cpp
#include "mallocator.hpp"              // For mallocator
#include <EASTL/polyalloc/polyalloc.h> // For allocator_handle

static mallocator gMallocator;

eastl::vector<int, allocator_handle> use_malloc() {
    eastl::vector<int, allocator_handle> vector(&gMallocator);
    // do stuff
    return vector;
}
```

## Installation

Library is completely header only, so how you install it is up to you. As long as the single header is available in your
include path as `<EASTL/polyalloc/polyalloc.h>` everything will work as expected.

### vcpkg

There is a vcpkg port available in data/vcpkg that you can add and install. When this is more mature we will publish it
to the default vcpkg repository.

