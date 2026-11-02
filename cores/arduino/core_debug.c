/**
 * @file core_debug.c
 * @brief Out-of-line definitions of the inline core_debug functions, needed
 * for C code.
 */
#include "core_debug.h"

// Ensure inline functions have a definition emitted for when they are
// not inlined (needed for C functions only)
extern void core_debug(const char *format, ...);
extern void vcore_debug(const char *format, va_list args);
