/**
 * @file utils.h
 * @brief Preprocessor helpers: string concatenation and stringification.
 */
#ifndef __UTILS_H
#define __UTILS_H

/** Concatenate 2 string literals. */
#define CONCAT(s1, s2) (s1 s2)
/** Concatenate 2 string literals separated by a space. */
#define CONCATS(s1, s2) (s1" " s2)

/** Stringification of a macro argument, after macro expansion. */
#define XSTR(s) STR(s)
/** Stringification of a macro argument, without macro expansion. */
#define STR(s) #s

#endif
