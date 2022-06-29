#ifndef _CORE_DEBUG_H
#define _CORE_DEBUG_H

#include <stdarg.h>
#if !defined(NDEBUG)
  #include <stdio.h>
#endif /* NDEBUG */

#ifdef __cplusplus
extern "C" {
#endif

/** Output a debug message
 *
 * @param format printf-style format string, followed by variables
 * Note: By using the printf function of the library C this inflates the size of
 * the code, use a lot of stack. An alternative, will be to implement a tiny
 * and limited functionality implementation of printf.
 */
inline void core_debug(const char *format, ...)
{
#if !defined(NDEBUG)
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
#else
  (void)(format);
#endif /* NDEBUG */
}

inline void vcore_debug(const char *format, va_list args)
{
#if !defined(NDEBUG)
  vfprintf(stderr, format, args);
#else
  (void)(format);
  (void)(args);
#endif /* NDEBUG */
}

#ifdef __cplusplus
}
#endif

#endif /* _CORE_DEBUG_H */
