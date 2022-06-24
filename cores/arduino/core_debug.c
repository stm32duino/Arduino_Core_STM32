#include "core_debug.h"

// Ensure inline functions have a definition emitted for when they are
// not inlined (needed for C functions only)
extern void core_debug(const char *format, ...);
extern void vcore_debug(const char *format, va_list args);
