#ifndef __UTILS_H
#define __UTILS_H

/* Concatenate 2 strings */
#define CONCAT(s1, s2) (s1 s2)
/* Concatenate 2 strings separated by space */
#define CONCATS(s1, s2) (s1" " s2)

/* Stringification */
#define XSTR(s) STR(s)
#define STR(s) #s

#endif
