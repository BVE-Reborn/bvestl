#pragma once

#define FOUNDATIONAL_STRINGIFY_IMPL(x) x
/**
 * \addtogroup utilities
 * \{
 */
/**
 * Turn a symbol into a string.
 */
#define FOUNDATIONAL_STRINGIFY(x) FOUNDATIONAL_STRINGIFY_IMPL(#x)
/**
 * \}
 */
