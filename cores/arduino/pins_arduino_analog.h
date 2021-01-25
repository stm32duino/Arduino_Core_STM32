/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef _PINS_ARDUINO_ANALOG_H_
#define _PINS_ARDUINO_ANALOG_H_
#include "variant.h"
#include "PinNames.h"

/*
 * Pin number Analog base
 * To check if a pin number is an analog pin:
 * ((p & PNUM_ANALOG_BASE) == PNUM_ANALOG_BASE)
 * if true then p is an analog pin number
 * else not
 */
#define PNUM_ANALOG_BASE    0xC0
/*
 * Pin number Analog index
 * allows to retrieve the pin number index of an analog pin
 * in the analogInputPin[] array:
 * analogInputPin[p & PNUM_ANALOG_INDEX]
 */
#define PNUM_ANALOG_INDEX   0x3F

/* Arduino analog pins */
#ifndef NUM_ANALOG_INPUTS
  #define NUM_ANALOG_INPUTS 0
#endif

/* Analog internal pin numbers follow the analog pin number */
#define NUM_ANALOG_INTERNAL_FIRST (PNUM_ANALOG_BASE + NUM_ANALOG_INPUTS)

/* ADC internal channels (not a pins) */
/* Only used for analogRead() */
#if defined(ADC_CHANNEL_TEMPSENSOR) || defined(ADC_CHANNEL_TEMPSENSOR_ADC1)
  #define ATEMP        (NUM_ANALOG_INTERNAL_FIRST)
#endif
#ifdef ADC_CHANNEL_VREFINT
  #define AVREF        (NUM_ANALOG_INTERNAL_FIRST + 1)
#endif
#ifdef ADC_CHANNEL_VBAT
  #define AVBAT        (NUM_ANALOG_INTERNAL_FIRST + 2)
#endif
#if defined(ADC5) && defined(ADC_CHANNEL_TEMPSENSOR_ADC5)
  #define ATEMP_ADC5   (NUM_ANALOG_INTERNAL_FIRST + 3)
#endif

/* If NUM_ANALOG_INPUTS is not defined there is no analog pins defined. */
/* Anyway ADC internal channels are always available. */
#if NUM_ANALOG_INPUTS > 0
#define PIN_A0       PNUM_ANALOG_BASE
#if NUM_ANALOG_INPUTS > 1
  #define PIN_A1      (PIN_A0 + 1)
#endif
#if NUM_ANALOG_INPUTS > 2
  #define PIN_A2      (PIN_A1 + 1)
#endif
#if NUM_ANALOG_INPUTS > 3
  #define PIN_A3      (PIN_A2 + 1)
#endif
#if NUM_ANALOG_INPUTS > 4
  #define PIN_A4      (PIN_A3 + 1)
#endif
#if NUM_ANALOG_INPUTS > 5
  #define PIN_A5      (PIN_A4 + 1)
#endif
#if NUM_ANALOG_INPUTS > 6
  #define PIN_A6      (PIN_A5 + 1)
#endif
#if NUM_ANALOG_INPUTS > 7
  #define PIN_A7      (PIN_A6 + 1)
#endif
#if NUM_ANALOG_INPUTS > 8
  #define PIN_A8      (PIN_A7 + 1)
#endif
#if NUM_ANALOG_INPUTS > 9
  #define PIN_A9      (PIN_A8 + 1)
#endif
#if NUM_ANALOG_INPUTS > 10
  #define PIN_A10      (PIN_A9 + 1)
#endif
#if NUM_ANALOG_INPUTS > 11
  #define PIN_A11      (PIN_A10 + 1)
#endif
#if NUM_ANALOG_INPUTS > 12
  #define PIN_A12      (PIN_A11 + 1)
#endif
#if NUM_ANALOG_INPUTS > 13
  #define PIN_A13      (PIN_A12 + 1)
#endif
#if NUM_ANALOG_INPUTS > 14
  #define PIN_A14      (PIN_A13 + 1)
#endif
#if NUM_ANALOG_INPUTS > 15
  #define PIN_A15      (PIN_A14 + 1)
#endif
#if NUM_ANALOG_INPUTS > 16
  #define PIN_A16      (PIN_A15 + 1)
#endif
#if NUM_ANALOG_INPUTS > 17
  #define PIN_A17      (PIN_A16 + 1)
#endif
#if NUM_ANALOG_INPUTS > 18
  #define PIN_A18      (PIN_A17 + 1)
#endif
#if NUM_ANALOG_INPUTS > 19
  #define PIN_A19      (PIN_A18 + 1)
#endif
#if NUM_ANALOG_INPUTS > 20
  #define PIN_A20      (PIN_A19 + 1)
#endif
#if NUM_ANALOG_INPUTS > 21
  #define PIN_A21      (PIN_A20 + 1)
#endif
#if NUM_ANALOG_INPUTS > 22
  #define PIN_A22      (PIN_A21 + 1)
#endif
#if NUM_ANALOG_INPUTS > 23
  #define PIN_A23      (PIN_A22 + 1)
#endif
#if NUM_ANALOG_INPUTS > 24
  #define PIN_A24      (PIN_A23 + 1)
#endif
#if NUM_ANALOG_INPUTS > 25
  #define PIN_A25      (PIN_A24 + 1)
#endif
#if NUM_ANALOG_INPUTS > 26
  #define PIN_A26      (PIN_A25 + 1)
#endif
#if NUM_ANALOG_INPUTS > 27
  #define PIN_A27      (PIN_A26 + 1)
#endif
#if NUM_ANALOG_INPUTS > 28
  #define PIN_A28      (PIN_A27 + 1)
#endif
#if NUM_ANALOG_INPUTS > 29
  #define PIN_A29      (PIN_A28 + 1)
#endif
#if NUM_ANALOG_INPUTS > 30
  #define PIN_A30      (PIN_A29 + 1)
#endif
#if NUM_ANALOG_INPUTS > 31
  #define PIN_A31      (PIN_A30 + 1)
#endif
#if NUM_ANALOG_INPUTS > 32
  #define PIN_A32      (PIN_A31 + 1)
#endif
#if NUM_ANALOG_INPUTS > 33
  #define PIN_A33      (PIN_A32 + 1)
#endif
#if NUM_ANALOG_INPUTS > 34
  #define PIN_A34      (PIN_A33 + 1)
#endif
#if NUM_ANALOG_INPUTS > 35
  #define PIN_A35      (PIN_A34 + 1)
#endif
#if NUM_ANALOG_INPUTS > 36
  #define PIN_A36      (PIN_A35 + 1)
#endif
#if NUM_ANALOG_INPUTS > 37
  #define PIN_A37      (PIN_A36 + 1)
#endif
#if NUM_ANALOG_INPUTS > 38
  #define PIN_A38      (PIN_A37 + 1)
#endif
#if NUM_ANALOG_INPUTS > 39
  #define PIN_A39      (PIN_A38 + 1)
#endif
#if NUM_ANALOG_INPUTS > 40
  #define PIN_A40      (PIN_A39 + 1)
#endif
#if NUM_ANALOG_INPUTS > 41
  #define PIN_A41      (PIN_A40 + 1)
#endif
#if NUM_ANALOG_INPUTS > 42
  #define PIN_A42      (PIN_A41 + 1)
#endif
#if NUM_ANALOG_INPUTS > 43
  #define PIN_A43      (PIN_A42 + 1)
#endif
#if NUM_ANALOG_INPUTS > 44
  #define PIN_A44      (PIN_A43 + 1)
#endif
#if NUM_ANALOG_INPUTS > 45
  #define PIN_A45      (PIN_A44 + 1)
#endif
#if NUM_ANALOG_INPUTS > 46
  #define PIN_A46      (PIN_A45 + 1)
#endif
#if NUM_ANALOG_INPUTS > 47
  #define PIN_A47      (PIN_A46 + 1)
#endif
#if NUM_ANALOG_INPUTS > 48
  #define PIN_A48      (PIN_A47 + 1)
#endif
#if NUM_ANALOG_INPUTS > 49
  #define PIN_A49      (PIN_A48 + 1)
#endif
#if NUM_ANALOG_INPUTS > 50
  #define PIN_A50      (PIN_A49 + 1)
#endif
#if NUM_ANALOG_INPUTS > 51
  #define PIN_A51      (PIN_A50 + 1)
#endif
#if NUM_ANALOG_INPUTS > 52
  #define PIN_A52      (PIN_A51 + 1)
#endif
#if NUM_ANALOG_INPUTS > 53
  #define PIN_A53      (PIN_A52 + 1)
#endif
#if NUM_ANALOG_INPUTS > 54
  #define PIN_A54      (PIN_A53 + 1)
#endif
#if NUM_ANALOG_INPUTS > 55
  #define PIN_A55      (PIN_A54 + 1)
#endif
#if NUM_ANALOG_INPUTS > 56
  #define PIN_A56      (PIN_A55 + 1)
#endif
#if NUM_ANALOG_INPUTS > 57
  #define PIN_A57      (PIN_A56 + 1)
#endif
#if NUM_ANALOG_INPUTS > 58
  #define PIN_A58      (PIN_A57 + 1)
#endif
#if NUM_ANALOG_INPUTS > 59
  #define PIN_A59      (PIN_A58 + 1)
#endif
#if NUM_ANALOG_INPUTS > 60
  #define PIN_A60      (PIN_A59 + 1)
#endif
#if NUM_ANALOG_INPUTS > 61
  #define PIN_A61      (PIN_A60 + 1)
#endif
#if NUM_ANALOG_INPUTS > 62
  #define PIN_A62      (PIN_A61 + 1)
#endif
#if NUM_ANALOG_INPUTS > 63
  #define PIN_A63      (PIN_A62 + 1)
#endif


enum {
  A0 = PIN_A0
#if NUM_ANALOG_INPUTS > 1
  , A1 = PIN_A1
#endif
#if NUM_ANALOG_INPUTS > 2
  , A2 = PIN_A2
#endif
#if NUM_ANALOG_INPUTS > 3
  , A3 = PIN_A3
#endif
#if NUM_ANALOG_INPUTS > 4
  , A4 = PIN_A4
#endif
#if NUM_ANALOG_INPUTS > 5
  , A5 = PIN_A5
#endif
#if NUM_ANALOG_INPUTS > 6
  , A6 = PIN_A6
#endif
#if NUM_ANALOG_INPUTS > 7
  , A7 = PIN_A7
#endif
#if NUM_ANALOG_INPUTS > 8
  , A8 = PIN_A8
#endif
#if NUM_ANALOG_INPUTS > 9
  , A9 = PIN_A9
#endif
#if NUM_ANALOG_INPUTS > 10
  , A10 = PIN_A10
#endif
#if NUM_ANALOG_INPUTS > 11
  , A11 = PIN_A11
#endif
#if NUM_ANALOG_INPUTS > 12
  , A12 = PIN_A12
#endif
#if NUM_ANALOG_INPUTS > 13
  , A13 = PIN_A13
#endif
#if NUM_ANALOG_INPUTS > 14
  , A14 = PIN_A14
#endif
#if NUM_ANALOG_INPUTS > 15
  , A15 = PIN_A15
#endif
#if NUM_ANALOG_INPUTS > 16
  , A16 = PIN_A16
#endif
#if NUM_ANALOG_INPUTS > 17
  , A17 = PIN_A17
#endif
#if NUM_ANALOG_INPUTS > 18
  , A18 = PIN_A18
#endif
#if NUM_ANALOG_INPUTS > 19
  , A19 = PIN_A19
#endif
#if NUM_ANALOG_INPUTS > 20
  , A20 = PIN_A20
#endif
#if NUM_ANALOG_INPUTS > 21
  , A21 = PIN_A21
#endif
#if NUM_ANALOG_INPUTS > 22
  , A22 = PIN_A22
#endif
#if NUM_ANALOG_INPUTS > 23
  , A23 = PIN_A23
#endif
#if NUM_ANALOG_INPUTS > 24
  , A24 = PIN_A24
#endif
#if NUM_ANALOG_INPUTS > 25
  , A25 = PIN_A25
#endif
#if NUM_ANALOG_INPUTS > 26
  , A26 = PIN_A26
#endif
#if NUM_ANALOG_INPUTS > 27
  , A27 = PIN_A27
#endif
#if NUM_ANALOG_INPUTS > 28
  , A28 = PIN_A28
#endif
#if NUM_ANALOG_INPUTS > 29
  , A29 = PIN_A29
#endif
#if NUM_ANALOG_INPUTS > 30
  , A30 = PIN_A30
#endif
#if NUM_ANALOG_INPUTS > 31
  , A31 = PIN_A31
#endif
#if NUM_ANALOG_INPUTS > 32
  , A32 = PIN_A32
#endif
#if NUM_ANALOG_INPUTS > 33
  , A33 = PIN_A33
#endif
#if NUM_ANALOG_INPUTS > 34
  , A34 = PIN_A34
#endif
#if NUM_ANALOG_INPUTS > 35
  , A35 = PIN_A35
#endif
#if NUM_ANALOG_INPUTS > 36
  , A36 = PIN_A36
#endif
#if NUM_ANALOG_INPUTS > 37
  , A37 = PIN_A37
#endif
#if NUM_ANALOG_INPUTS > 38
  , A38 = PIN_A38
#endif
#if NUM_ANALOG_INPUTS > 39
  , A39 = PIN_A39
#endif
#if NUM_ANALOG_INPUTS > 40
  , A40 = PIN_A40
#endif
#if NUM_ANALOG_INPUTS > 41
  , A41 = PIN_A41
#endif
#if NUM_ANALOG_INPUTS > 42
  , A42 = PIN_A42
#endif
#if NUM_ANALOG_INPUTS > 43
  , A43 = PIN_A43
#endif
#if NUM_ANALOG_INPUTS > 44
  , A44 = PIN_A44
#endif
#if NUM_ANALOG_INPUTS > 45
  , A45 = PIN_A45
#endif
#if NUM_ANALOG_INPUTS > 46
  , A46 = PIN_A46
#endif
#if NUM_ANALOG_INPUTS > 47
  , A47 = PIN_A47
#endif
#if NUM_ANALOG_INPUTS > 48
  , A48 = PIN_A48
#endif
#if NUM_ANALOG_INPUTS > 49
  , A49 = PIN_A49
#endif
#if NUM_ANALOG_INPUTS > 50
  , A50 = PIN_A50
#endif
#if NUM_ANALOG_INPUTS > 51
  , A51 = PIN_A51
#endif
#if NUM_ANALOG_INPUTS > 52
  , A52 = PIN_A52
#endif
#if NUM_ANALOG_INPUTS > 53
  , A53 = PIN_A53
#endif
#if NUM_ANALOG_INPUTS > 54
  , A54 = PIN_A54
#endif
#if NUM_ANALOG_INPUTS > 55
  , A55 = PIN_A55
#endif
#if NUM_ANALOG_INPUTS > 56
  , A56 = PIN_A56
#endif
#if NUM_ANALOG_INPUTS > 57
  , A57 = PIN_A57
#endif
#if NUM_ANALOG_INPUTS > 58
  , A58 = PIN_A58
#endif
#if NUM_ANALOG_INPUTS > 59
  , A59 = PIN_A59
#endif
#if NUM_ANALOG_INPUTS > 60
  , A60 = PIN_A60
#endif
#if NUM_ANALOG_INPUTS > 61
  , A61 = PIN_A61
#endif
#if NUM_ANALOG_INPUTS > 62
  , A62 = PIN_A62
#endif
#if NUM_ANALOG_INPUTS > 63
  , A63 = PIN_A63
#endif
};
#define MAX_ANALOG_INPUTS 64
#else
#define MAX_ANALOG_INPUTS 0
#endif /* NUM_ANALOG_INPUTS > 0 */

#endif /*_PINS_ARDUINO_ANALOG_H_*/
