#ifndef __UTILS_H
#define __UTILS_H

#include "avr/dtostrf.h"

// Concatenate 2 strings
#define CONCAT(s1, s2) (s1 s2)
// Concatenate 2 strings separated by space
#define CONCATS(s1, s2) (s1" " s2)

// Stringification
#define xstr(s) str(s)
#define str(s) #s

#endif
