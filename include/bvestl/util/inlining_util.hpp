#pragma once

#ifdef _MSC_VER
#define FOUNDATIONAL_FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define FOUNDATIONAL_FORCE_INLINE __attribute__((always_inline)) inline
#else
/**
 * \ingroup utilities
 *
 * Attribute that forces the inliner to inline the function.
 */
#define FOUNDATIONAL_FORCE_INLINE inline
#endif
