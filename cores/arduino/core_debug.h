#ifndef _CORE_DEBUG_H
#define _CORE_DEBUG_H
#ifdef CORE_DEBUG
  #include <stdio.h>
  #include <stdarg.h>
#endif /* CORE_DEBUG */

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
static inline void core_debug(const char *format, ...)
{
#ifdef CORE_DEBUG
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
#else
  (void)(format);
#endif /* CORE_DEBUG */
}

#ifdef __cplusplus
}
#endif

#endif /* _CORE_DEBUG_H */
