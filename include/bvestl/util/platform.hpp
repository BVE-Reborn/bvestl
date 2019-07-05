#pragma once

/**
 * \addtogroup utilities
 * \{
 */

#if defined(_WIN32)
#define FOUNDATIONAL_WINDOWS 1
#elif defined(__APPLE__) && defined(__MACH__)
#define FOUNDATIONAL_OSX 1
#elif defined(__linux__)
#define FOUNDATIONAL_LINUX 1
#else
#error "Unknown platform"
/**
 * Defined when targeting windows
 */
#define FOUNDATIONAL_WINDOWS 0
/**
 * Defined when targeting OSX
 */
#define FOUNDATIONAL_OSX 0
/**
 * Defined when targeting linux
 */
#define FOUNDATIONAL_LINUX 0
#endif

// All the compilers that pretend to be others first
#if defined(__clang__)
#define FOUNDATIONAL_CLANG 1
#elif defined(__INTEL_COMPILER)
#define FOUNDATIONAL_ICC 1
#elif defined(__MINGW32__)
#define FOUNDATIONAL_MINGW 1
#elif defined(_MSC_VER)
#define FOUNDATIONAL_MSVC 1
#elif defined(__GNUC__)
#define FOUNDATIONAL_GCC 1
#else
#error "Unknown compiler"
/**
 * Defined when compiling using clang
 */
#define FOUNDATIONAL_CLANG 0
/**
 * Defined when compiling using icc
 */
#define FOUNDATIONAL_ICC 0
/**
 * Defined when compiling using MinGW
 */
#define FOUNDATIONAL_MINGW 0
/**
 * Defined when compiling on MSVC _only_ (not icc-cl or clang-cl)
 */
#define FOUNDATIONAL_MSVC 0
/**
 * Defined when compiling on gcc _only_ (not icc or clang)
 */
#define FOUNDATIONAL_GCC 0
#endif

#if defined(FOUNDATIONAL_WINDOWS)
#if defined(FOUNDATIONAL_DLLEXPORT)
/**
 * \internal
 */
#define FOUNDATIONAL_DLL_INTERNAL __declspec(dllexport)
#else
/**
 * \internal
 */
#define FOUNDATIONAL_DLL_INTERNAL __declspec(dllimport)
#endif
#else
#define FOUNDATIONAL_DLL_INTERNAL
#endif

/**
 * \}
 */
