/* Simple compatibility headers for AVR code used with ARM chips
 * Copyright (c) 2015 Paul Stoffregen <paul@pjrc.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __PGMSPACE_H_
#define __PGMSPACE_H_ 1

#include <inttypes.h>

#define PROGMEM
#define PGM_P  const char *
#define PSTR(str) (str)

#define _SFR_BYTE(n) (n)

typedef void prog_void;
typedef char prog_char;
typedef unsigned char prog_uchar;
typedef int8_t prog_int8_t;
typedef uint8_t prog_uint8_t;
typedef int16_t prog_int16_t;
typedef uint16_t prog_uint16_t;
typedef int32_t prog_int32_t;
typedef uint32_t prog_uint32_t;
typedef int64_t prog_int64_t;
typedef uint64_t prog_uint64_t;

#define memchr_P(str, c, len) memchr((str), (c), (len))
#define memcmp_P(a, b, n) memcmp((a), (b), (n))
#define memcpy_P(dest, src, num) memcpy((dest), (src), (num))
#define memmem_P(a, alen, b, blen) memmem((a), (alen), (b), (blen))
#define memrchr_P(str, val, len) memrchr((str), (val), (len))
#define strcat_P(dest, src) strcat((dest), (src))
#define strchr_P(str, c) strchr((str), (c))
#define strchrnul_P(str, c) strchrnul((str), (c))
#define strcmp_P(a, b) strcmp((a), (b))
#define strcpy_P(dest, src) strcpy((dest), (src))
#define strcasecmp_P(a, b) strcasecmp((a), (b))
#define strcasestr_P(a, b) strcasestr((a), (b))
#define strlcat_P(dest, src, len) strlcat((dest), (src), (len))
#define strlcpy_P(dest, src, len) strlcpy((dest), (src), (len))
#define strlen_P(s) strlen((const char *)(s))
#define strnlen_P(str, len) strnlen((str), (len))
#define strncmp_P(a, b, n) strncmp((a), (b), (n))
#define strncasecmp_P(a, b, n) strncasecmp((a), (b), (n))
#define strncat_P(a, b, n) strncat((a), (b), (n))
#define strncpy_P(a, b, n) strncpy((a), (b), (n))
#define strpbrk_P(str, chrs) strpbrk((str), (chrs))
#define strrchr_P(str, c) strrchr((str), (c))
#define strsep_P(strp, delim) strsep((strp), (delim))
#define strspn_P(str, chrs) strspn((str), (chrs))
#define strstr_P(a, b) strstr((a), (b))
#define sprintf_P(s, ...) sprintf((s), __VA_ARGS__)
#define vfprintf_P(fp, s, ...) vfprintf((fp), (s), __VA_ARGS__)
#define printf_P(...) printf(__VA_ARGS__)
#define snprintf_P(s, n, ...) snprintf((s), (n), __VA_ARGS__)
#define vsprintf_P(s, ...) vsprintf((s), __VA_ARGS__)
#define vsnprintf_P(s, n, ...) vsnprintf((s), (n), __VA_ARGS__)
#define fprintf_P(fp, ...) fprintf((fp), __VA_ARGS__)
#define strlen_PF(a) strlen((a))
#define strnlen_PF(src, len) strnlen((src), (len))
#define memcpy_PF(dest, src, len) memcpy((dest), (src), (len))
#define strcpy_PF(dest, src) strcpy((dest), (src))
#define strncpy_PF(dest, src, len) strncpy((dest), (src), (len))
#define strcat_PF(dest, src) strcat((dest), (src))
#define strlcat_PF(dest, src, len) strlcat((dest), (src), (len))
#define strncat_PF(dest, src, len) strncat((dest), (src), (len))
#define strcmp_PF(s1, s2) strcmp((s1), (s2))
#define strncmp_PF(s1, s2, n) strncmp((s1), (s2), (n))
#define strcasecmp_PF(s1, s2) strcasecmp((s1), (s2))
#define strncasecmp_PF(s1, s2, n) strncasecmp((s1), (s2), (n))
#define strstr_PF(s1, s2) strstr((s1), (s2))
#define strlcpy_PF(dest, src, n) strlcpy((dest), (src), (n))
#define memcmp_PF(s1, s2, n) memcmp((s1), (s2), (n))


#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#if 0
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#define pgm_read_float(addr) (*(const float *)(addr))
#else
#define pgm_read_word(addr) ({ \
  typeof(addr) _addr = (addr); \
  *(const unsigned short *)(_addr); \
})
#define pgm_read_dword(addr) ({ \
  typeof(addr) _addr = (addr); \
  *(const unsigned long *)(_addr); \
})
#define pgm_read_float(addr) ({ \
  typeof(addr) _addr = (addr); \
  *(const float *)(_addr); \
})
#define pgm_read_ptr(addr) ({ \
  typeof(addr) _addr = (addr); \
  *(void * const *)(_addr); \
})
#endif

#define pgm_read_byte_near(addr) pgm_read_byte(addr)
#define pgm_read_word_near(addr) pgm_read_word(addr)
#define pgm_read_dword_near(addr) pgm_read_dword(addr)
#define pgm_read_float_near(addr) pgm_read_float(addr)
#define pgm_read_ptr_near(addr) pgm_read_ptr(addr)
#define pgm_read_byte_far(addr) pgm_read_byte(addr)
#define pgm_read_word_far(addr) pgm_read_word(addr)
#define pgm_read_dword_far(addr) pgm_read_dword(addr)
#define pgm_read_float_far(addr) pgm_read_float(addr)
#define pgm_read_ptr_far(addr) pgm_read_ptr(addr)

#endif
