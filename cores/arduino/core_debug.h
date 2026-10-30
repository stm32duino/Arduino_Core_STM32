/**
 * @file core_debug.h
 * @brief Debug message output helpers: core_debug() and vcore_debug().
 */
#ifndef _CORE_DEBUG_H
#define _CORE_DEBUG_H

#include <stdarg.h>
#if !defined(NDEBUG)
  #include <stdio.h>
#endif /* NDEBUG */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Output a debug message on stderr. Does nothing when NDEBUG is defined.
 *
 * @note Using the printf function of the C library inflates the size of the
 * code and uses a lot of stack. An alternative would be to implement a tiny
 * and limited functionality implementation of printf.
 *
 * @param format printf-style format string, followed by the variables to print.
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

/**
 * @brief Output a debug message on stderr from a va_list. Does nothing when
 * NDEBUG is defined.
 *
 * @param format printf-style format string.
 * @param args Variable argument list matching format.
 */
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
