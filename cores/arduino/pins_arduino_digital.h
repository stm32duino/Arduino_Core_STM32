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
#ifndef _PINS_ARDUINO_DIGITAL_H_
#define _PINS_ARDUINO_DIGITAL_H_
#include "variant.h"

/* GPIO port (A to K + Z) * 16 pins: 192 */
/* Arduino digital pins alias */
enum {
  D0,  D1,  D2,  D3,  D4,  D5,  D6,  D7,  D8,  D9,
  D10, D11, D12, D13, D14, D15, D16, D17, D18, D19,
  D20, D21
#if NUM_DIGITAL_PINS > 22
  , D22
#endif
#if NUM_DIGITAL_PINS > 23
  , D23
#endif
#if NUM_DIGITAL_PINS > 24
  , D24
#endif
#if NUM_DIGITAL_PINS > 25
  , D25
#endif
#if NUM_DIGITAL_PINS > 26
  , D26
#endif
#if NUM_DIGITAL_PINS > 27
  , D27
#endif
#if NUM_DIGITAL_PINS > 28
  , D28
#endif
#if NUM_DIGITAL_PINS > 29
  , D29
#endif
#if NUM_DIGITAL_PINS > 30
  , D30
#endif
#if NUM_DIGITAL_PINS > 31
  , D31
#endif
#if NUM_DIGITAL_PINS > 32
  , D32
#endif
#if NUM_DIGITAL_PINS > 33
  , D33
#endif
#if NUM_DIGITAL_PINS > 34
  , D34
#endif
#if NUM_DIGITAL_PINS > 35
  , D35
#endif
#if NUM_DIGITAL_PINS > 36
  , D36
#endif
#if NUM_DIGITAL_PINS > 37
  , D37
#endif
#if NUM_DIGITAL_PINS > 38
  , D38
#endif
#if NUM_DIGITAL_PINS > 39
  , D39
#endif
#if NUM_DIGITAL_PINS > 40
  , D40
#endif
#if NUM_DIGITAL_PINS > 41
  , D41
#endif
#if NUM_DIGITAL_PINS > 42
  , D42
#endif
#if NUM_DIGITAL_PINS > 43
  , D43
#endif
#if NUM_DIGITAL_PINS > 44
  , D44
#endif
#if NUM_DIGITAL_PINS > 45
  , D45
#endif
#if NUM_DIGITAL_PINS > 46
  , D46
#endif
#if NUM_DIGITAL_PINS > 47
  , D47
#endif
#if NUM_DIGITAL_PINS > 48
  , D48
#endif
#if NUM_DIGITAL_PINS > 49
  , D49
#endif
#if NUM_DIGITAL_PINS > 50
  , D50
#endif
#if NUM_DIGITAL_PINS > 51
  , D51
#endif
#if NUM_DIGITAL_PINS > 52
  , D52
#endif
#if NUM_DIGITAL_PINS > 53
  , D53
#endif
#if NUM_DIGITAL_PINS > 54
  , D54
#endif
#if NUM_DIGITAL_PINS > 55
  , D55
#endif
#if NUM_DIGITAL_PINS > 56
  , D56
#endif
#if NUM_DIGITAL_PINS > 57
  , D57
#endif
#if NUM_DIGITAL_PINS > 58
  , D58
#endif
#if NUM_DIGITAL_PINS > 59
  , D59
#endif
#if NUM_DIGITAL_PINS > 60
  , D60
#endif
#if NUM_DIGITAL_PINS > 61
  , D61
#endif
#if NUM_DIGITAL_PINS > 62
  , D62
#endif
#if NUM_DIGITAL_PINS > 63
  , D63
#endif
#if NUM_DIGITAL_PINS > 64
  , D64
#endif
#if NUM_DIGITAL_PINS > 65
  , D65
#endif
#if NUM_DIGITAL_PINS > 66
  , D66
#endif
#if NUM_DIGITAL_PINS > 67
  , D67
#endif
#if NUM_DIGITAL_PINS > 68
  , D68
#endif
#if NUM_DIGITAL_PINS > 69
  , D69
#endif
#if NUM_DIGITAL_PINS > 70
  , D70
#endif
#if NUM_DIGITAL_PINS > 71
  , D71
#endif
#if NUM_DIGITAL_PINS > 72
  , D72
#endif
#if NUM_DIGITAL_PINS > 73
  , D73
#endif
#if NUM_DIGITAL_PINS > 74
  , D74
#endif
#if NUM_DIGITAL_PINS > 75
  , D75
#endif
#if NUM_DIGITAL_PINS > 76
  , D76
#endif
#if NUM_DIGITAL_PINS > 77
  , D77
#endif
#if NUM_DIGITAL_PINS > 78
  , D78
#endif
#if NUM_DIGITAL_PINS > 79
  , D79
#endif
#if NUM_DIGITAL_PINS > 80
  , D80
#endif
#if NUM_DIGITAL_PINS > 81
  , D81
#endif
#if NUM_DIGITAL_PINS > 82
  , D82
#endif
#if NUM_DIGITAL_PINS > 83
  , D83
#endif
#if NUM_DIGITAL_PINS > 84
  , D84
#endif
#if NUM_DIGITAL_PINS > 85
  , D85
#endif
#if NUM_DIGITAL_PINS > 86
  , D86
#endif
#if NUM_DIGITAL_PINS > 87
  , D87
#endif
#if NUM_DIGITAL_PINS > 88
  , D88
#endif
#if NUM_DIGITAL_PINS > 89
  , D89
#endif
#if NUM_DIGITAL_PINS > 90
  , D90
#endif
#if NUM_DIGITAL_PINS > 91
  , D91
#endif
#if NUM_DIGITAL_PINS > 92
  , D92
#endif
#if NUM_DIGITAL_PINS > 93
  , D93
#endif
#if NUM_DIGITAL_PINS > 94
  , D94
#endif
#if NUM_DIGITAL_PINS > 95
  , D95
#endif
#if NUM_DIGITAL_PINS > 96
  , D96
#endif
#if NUM_DIGITAL_PINS > 97
  , D97
#endif
#if NUM_DIGITAL_PINS > 98
  , D98
#endif
#if NUM_DIGITAL_PINS > 99
  , D99
#endif
#if NUM_DIGITAL_PINS > 100
  , D100
#endif
#if NUM_DIGITAL_PINS > 101
  , D101
#endif
#if NUM_DIGITAL_PINS > 102
  , D102
#endif
#if NUM_DIGITAL_PINS > 103
  , D103
#endif
#if NUM_DIGITAL_PINS > 104
  , D104
#endif
#if NUM_DIGITAL_PINS > 105
  , D105
#endif
#if NUM_DIGITAL_PINS > 106
  , D106
#endif
#if NUM_DIGITAL_PINS > 107
  , D107
#endif
#if NUM_DIGITAL_PINS > 108
  , D108
#endif
#if NUM_DIGITAL_PINS > 109
  , D109
#endif
#if NUM_DIGITAL_PINS > 110
  , D110
#endif
#if NUM_DIGITAL_PINS > 111
  , D111
#endif
#if NUM_DIGITAL_PINS > 112
  , D112
#endif
#if NUM_DIGITAL_PINS > 113
  , D113
#endif
#if NUM_DIGITAL_PINS > 114
  , D114
#endif
#if NUM_DIGITAL_PINS > 115
  , D115
#endif
#if NUM_DIGITAL_PINS > 116
  , D116
#endif
#if NUM_DIGITAL_PINS > 117
  , D117
#endif
#if NUM_DIGITAL_PINS > 118
  , D118
#endif
#if NUM_DIGITAL_PINS > 119
  , D119
#endif
#if NUM_DIGITAL_PINS > 120
  , D120
#endif
#if NUM_DIGITAL_PINS > 121
  , D121
#endif
#if NUM_DIGITAL_PINS > 122
  , D122
#endif
#if NUM_DIGITAL_PINS > 123
  , D123
#endif
#if NUM_DIGITAL_PINS > 124
  , D124
#endif
#if NUM_DIGITAL_PINS > 125
  , D125
#endif
#if NUM_DIGITAL_PINS > 126
  , D126
#endif
#if NUM_DIGITAL_PINS > 127
  , D127
#endif
#if NUM_DIGITAL_PINS > 128
  , D128
#endif
#if NUM_DIGITAL_PINS > 129
  , D129
#endif
#if NUM_DIGITAL_PINS > 130
  , D130
#endif
#if NUM_DIGITAL_PINS > 131
  , D131
#endif
#if NUM_DIGITAL_PINS > 132
  , D132
#endif
#if NUM_DIGITAL_PINS > 133
  , D133
#endif
#if NUM_DIGITAL_PINS > 134
  , D134
#endif
#if NUM_DIGITAL_PINS > 135
  , D135
#endif
#if NUM_DIGITAL_PINS > 136
  , D136
#endif
#if NUM_DIGITAL_PINS > 137
  , D137
#endif
#if NUM_DIGITAL_PINS > 138
  , D138
#endif
#if NUM_DIGITAL_PINS > 139
  , D139
#endif
#if NUM_DIGITAL_PINS > 140
  , D140
#endif
#if NUM_DIGITAL_PINS > 141
  , D141
#endif
#if NUM_DIGITAL_PINS > 142
  , D142
#endif
#if NUM_DIGITAL_PINS > 143
  , D143
#endif
#if NUM_DIGITAL_PINS > 144
  , D144
#endif
#if NUM_DIGITAL_PINS > 145
  , D145
#endif
#if NUM_DIGITAL_PINS > 146
  , D146
#endif
#if NUM_DIGITAL_PINS > 147
  , D147
#endif
#if NUM_DIGITAL_PINS > 148
  , D148
#endif
#if NUM_DIGITAL_PINS > 149
  , D149
#endif
#if NUM_DIGITAL_PINS > 150
  , D150
#endif
#if NUM_DIGITAL_PINS > 151
  , D151
#endif
#if NUM_DIGITAL_PINS > 152
  , D152
#endif
#if NUM_DIGITAL_PINS > 153
  , D153
#endif
#if NUM_DIGITAL_PINS > 154
  , D154
#endif
#if NUM_DIGITAL_PINS > 155
  , D155
#endif
#if NUM_DIGITAL_PINS > 156
  , D156
#endif
#if NUM_DIGITAL_PINS > 157
  , D157
#endif
#if NUM_DIGITAL_PINS > 158
  , D158
#endif
#if NUM_DIGITAL_PINS > 159
  , D159
#endif
#if NUM_DIGITAL_PINS > 160
  , D160
#endif
#if NUM_DIGITAL_PINS > 161
  , D161
#endif
#if NUM_DIGITAL_PINS > 162
  , D162
#endif
#if NUM_DIGITAL_PINS > 163
  , D163
#endif
#if NUM_DIGITAL_PINS > 164
  , D164
#endif
#if NUM_DIGITAL_PINS > 165
  , D165
#endif
#if NUM_DIGITAL_PINS > 166
  , D166
#endif
#if NUM_DIGITAL_PINS > 167
  , D167
#endif
#if NUM_DIGITAL_PINS > 168
  , D168
#endif
#if NUM_DIGITAL_PINS > 169
  , D169
#endif
#if NUM_DIGITAL_PINS > 170
  , D170
#endif
#if NUM_DIGITAL_PINS > 171
  , D171
#endif
#if NUM_DIGITAL_PINS > 172
  , D172
#endif
#if NUM_DIGITAL_PINS > 173
  , D173
#endif
#if NUM_DIGITAL_PINS > 174
  , D174
#endif
#if NUM_DIGITAL_PINS > 175
  , D175
#endif
#if NUM_DIGITAL_PINS > 176
  , D176
#endif
#if NUM_DIGITAL_PINS > 177
  , D177
#endif
#if NUM_DIGITAL_PINS > 178
  , D178
#endif
#if NUM_DIGITAL_PINS > 179
  , D179
#endif
#if NUM_DIGITAL_PINS > 180
  , D180
#endif
#if NUM_DIGITAL_PINS > 181
  , D181
#endif
#if NUM_DIGITAL_PINS > 182
  , D182
#endif
#if NUM_DIGITAL_PINS > 183
  , D183
#endif
#if NUM_DIGITAL_PINS > 184
  , D184
#endif
#if NUM_DIGITAL_PINS > 185
  , D185
#endif
#if NUM_DIGITAL_PINS > 186
  , D186
#endif
#if NUM_DIGITAL_PINS > 187
  , D187
#endif
#if NUM_DIGITAL_PINS > 188
  , D188
#endif
#if NUM_DIGITAL_PINS > 189
  , D189
#endif
#if NUM_DIGITAL_PINS > 190
  , D190
#endif
#if NUM_DIGITAL_PINS > 191
  , D191
#endif
};
#if NUM_DIGITAL_PINS > 192
  #error "Core NUM_DIGITAL_PINS limited to 192"
#endif

/*
 * Each STM32 pin number PYn defined in the variant.h
 * is also the alternate pin number PYn_ALT0
 */
#ifdef PA0
  #define PA0_ALT0       (PA0  | ALT0)
#endif
#ifdef PA1
  #define PA1_ALT0       (PA1  | ALT0)
#endif
#ifdef PA2
  #define PA2_ALT0       (PA2  | ALT0)
#endif
#ifdef PA3
  #define PA3_ALT0       (PA3  | ALT0)
#endif
#ifdef PA4
  #define PA4_ALT0       (PA4  | ALT0)
#endif
#ifdef PA5
  #define PA5_ALT0       (PA5  | ALT0)
#endif
#ifdef PA6
  #define PA6_ALT0       (PA6  | ALT0)
#endif
#ifdef PA7
  #define PA7_ALT0       (PA7  | ALT0)
#endif
#ifdef PA8
  #define PA8_ALT0       (PA8  | ALT0)
#endif
#ifdef PA9
  #define PA9_ALT0       (PA9  | ALT0)
#endif
#ifdef PA10
  #define PA10_ALT0      (PA10 | ALT0)
#endif
#ifdef PA11
  #define PA11_ALT0      (PA11 | ALT0)
#endif
#ifdef PA12
  #define PA12_ALT0      (PA12 | ALT0)
#endif
#ifdef PA13
  #define PA13_ALT0      (PA13 | ALT0)
#endif
#ifdef PA14
  #define PA14_ALT0      (PA14 | ALT0)
#endif
#ifdef PA15
  #define PA15_ALT0      (PA15 | ALT0)
#endif
#ifdef PB0
  #define PB0_ALT0       (PB0  | ALT0)
#endif
#ifdef PB1
  #define PB1_ALT0       (PB1  | ALT0)
#endif
#ifdef PB2
  #define PB2_ALT0       (PB2  | ALT0)
#endif
#ifdef PB3
  #define PB3_ALT0       (PB3  | ALT0)
#endif
#ifdef PB4
  #define PB4_ALT0       (PB4  | ALT0)
#endif
#ifdef PB5
  #define PB5_ALT0       (PB5  | ALT0)
#endif
#ifdef PB6
  #define PB6_ALT0       (PB6  | ALT0)
#endif
#ifdef PB7
  #define PB7_ALT0       (PB7  | ALT0)
#endif
#ifdef PB8
  #define PB8_ALT0       (PB8  | ALT0)
#endif
#ifdef PB9
  #define PB9_ALT0       (PB9  | ALT0)
#endif
#ifdef PB10
  #define PB10_ALT0      (PB10 | ALT0)
#endif
#ifdef PB11
  #define PB11_ALT0      (PB11 | ALT0)
#endif
#ifdef PB12
  #define PB12_ALT0      (PB12 | ALT0)
#endif
#ifdef PB13
  #define PB13_ALT0      (PB13 | ALT0)
#endif
#ifdef PB14
  #define PB14_ALT0      (PB14 | ALT0)
#endif
#ifdef PB15
  #define PB15_ALT0      (PB15 | ALT0)
#endif
#ifdef PC0
  #define PC0_ALT0       (PC0  | ALT0)
#endif
#ifdef PC1
  #define PC1_ALT0       (PC1  | ALT0)
#endif
#ifdef PC2
  #define PC2_ALT0       (PC2  | ALT0)
#endif
#ifdef PC3
  #define PC3_ALT0       (PC3  | ALT0)
#endif
#ifdef PC4
  #define PC4_ALT0       (PC4  | ALT0)
#endif
#ifdef PC5
  #define PC5_ALT0       (PC5  | ALT0)
#endif
#ifdef PC6
  #define PC6_ALT0       (PC6  | ALT0)
#endif
#ifdef PC7
  #define PC7_ALT0       (PC7  | ALT0)
#endif
#ifdef PC8
  #define PC8_ALT0       (PC8  | ALT0)
#endif
#ifdef PC9
  #define PC9_ALT0       (PC9  | ALT0)
#endif
#ifdef PC10
  #define PC10_ALT0      (PC10 | ALT0)
#endif
#ifdef PC11
  #define PC11_ALT0      (PC11 | ALT0)
#endif
#ifdef PC12
  #define PC12_ALT0      (PC12 | ALT0)
#endif
#ifdef PC13
  #define PC13_ALT0      (PC13 | ALT0)
#endif
#ifdef PC14
  #define PC14_ALT0      (PC14 | ALT0)
#endif
#ifdef PC15
  #define PC15_ALT0      (PC15 | ALT0)
#endif
#ifdef PD0
  #define PD0_ALT0       (PD0  | ALT0)
#endif
#ifdef PD1
  #define PD1_ALT0       (PD1  | ALT0)
#endif
#ifdef PD2
  #define PD2_ALT0       (PD2  | ALT0)
#endif
#ifdef PD3
  #define PD3_ALT0       (PD3  | ALT0)
#endif
#ifdef PD4
  #define PD4_ALT0       (PD4  | ALT0)
#endif
#ifdef PD5
  #define PD5_ALT0       (PD5  | ALT0)
#endif
#ifdef PD6
  #define PD6_ALT0       (PD6  | ALT0)
#endif
#ifdef PD7
  #define PD7_ALT0       (PD7  | ALT0)
#endif
#ifdef PD8
  #define PD8_ALT0       (PD8  | ALT0)
#endif
#ifdef PD9
  #define PD9_ALT0       (PD9  | ALT0)
#endif
#ifdef PD10
  #define PD10_ALT0      (PD10 | ALT0)
#endif
#ifdef PD11
  #define PD11_ALT0      (PD11 | ALT0)
#endif
#ifdef PD12
  #define PD12_ALT0      (PD12 | ALT0)
#endif
#ifdef PD13
  #define PD13_ALT0      (PD13 | ALT0)
#endif
#ifdef PD14
  #define PD14_ALT0      (PD14 | ALT0)
#endif
#ifdef PD15
  #define PD15_ALT0      (PD15 | ALT0)
#endif
#ifdef PE0
  #define PE0_ALT0       (PE0  | ALT0)
#endif
#ifdef PE1
  #define PE1_ALT0       (PE1  | ALT0)
#endif
#ifdef PE2
  #define PE2_ALT0       (PE2  | ALT0)
#endif
#ifdef PE3
  #define PE3_ALT0       (PE3  | ALT0)
#endif
#ifdef PE4
  #define PE4_ALT0       (PE4  | ALT0)
#endif
#ifdef PE5
  #define PE5_ALT0       (PE5  | ALT0)
#endif
#ifdef PE6
  #define PE6_ALT0       (PE6  | ALT0)
#endif
#ifdef PE7
  #define PE7_ALT0       (PE7  | ALT0)
#endif
#ifdef PE8
  #define PE8_ALT0       (PE8  | ALT0)
#endif
#ifdef PE9
  #define PE9_ALT0       (PE9  | ALT0)
#endif
#ifdef PE10
  #define PE10_ALT0      (PE10 | ALT0)
#endif
#ifdef PE11
  #define PE11_ALT0      (PE11 | ALT0)
#endif
#ifdef PE12
  #define PE12_ALT0      (PE12 | ALT0)
#endif
#ifdef PE13
  #define PE13_ALT0      (PE13 | ALT0)
#endif
#ifdef PE14
  #define PE14_ALT0      (PE14 | ALT0)
#endif
#ifdef PE15
  #define PE15_ALT0      (PE15 | ALT0)
#endif
#ifdef PF0
  #define PF0_ALT0       (PF0  | ALT0)
#endif
#ifdef PF1
  #define PF1_ALT0       (PF1  | ALT0)
#endif
#ifdef PF2
  #define PF2_ALT0       (PF2  | ALT0)
#endif
#ifdef PF3
  #define PF3_ALT0       (PF3  | ALT0)
#endif
#ifdef PF4
  #define PF4_ALT0       (PF4  | ALT0)
#endif
#ifdef PF5
  #define PF5_ALT0       (PF5  | ALT0)
#endif
#ifdef PF6
  #define PF6_ALT0       (PF6  | ALT0)
#endif
#ifdef PF7
  #define PF7_ALT0       (PF7  | ALT0)
#endif
#ifdef PF8
  #define PF8_ALT0       (PF8  | ALT0)
#endif
#ifdef PF9
  #define PF9_ALT0       (PF9  | ALT0)
#endif
#ifdef PF10
  #define PF10_ALT0      (PF10 | ALT0)
#endif
#ifdef PF11
  #define PF11_ALT0      (PF11 | ALT0)
#endif
#ifdef PF12
  #define PF12_ALT0      (PF12 | ALT0)
#endif
#ifdef PF13
  #define PF13_ALT0      (PF13 | ALT0)
#endif
#ifdef PF14
  #define PF14_ALT0      (PF14 | ALT0)
#endif
#ifdef PF15
  #define PF15_ALT0      (PF15 | ALT0)
#endif
#ifdef PG0
  #define PG0_ALT0       (PG0  | ALT0)
#endif
#ifdef PG1
  #define PG1_ALT0       (PG1  | ALT0)
#endif
#ifdef PG2
  #define PG2_ALT0       (PG2  | ALT0)
#endif
#ifdef PG3
  #define PG3_ALT0       (PG3  | ALT0)
#endif
#ifdef PG4
  #define PG4_ALT0       (PG4  | ALT0)
#endif
#ifdef PG5
  #define PG5_ALT0       (PG5  | ALT0)
#endif
#ifdef PG6
  #define PG6_ALT0       (PG6  | ALT0)
#endif
#ifdef PG7
  #define PG7_ALT0       (PG7  | ALT0)
#endif
#ifdef PG8
  #define PG8_ALT0       (PG8  | ALT0)
#endif
#ifdef PG9
  #define PG9_ALT0       (PG9  | ALT0)
#endif
#ifdef PG10
  #define PG10_ALT0      (PG10 | ALT0)
#endif
#ifdef PG11
  #define PG11_ALT0      (PG11 | ALT0)
#endif
#ifdef PG12
  #define PG12_ALT0      (PG12 | ALT0)
#endif
#ifdef PG13
  #define PG13_ALT0      (PG13 | ALT0)
#endif
#ifdef PG14
  #define PG14_ALT0      (PG14 | ALT0)
#endif
#ifdef PG15
  #define PG15_ALT0      (PG15 | ALT0)
#endif
#ifdef PH0
  #define PH0_ALT0       (PH0  | ALT0)
#endif
#ifdef PH1
  #define PH1_ALT0       (PH1  | ALT0)
#endif
#ifdef PH2
  #define PH2_ALT0       (PH2  | ALT0)
#endif
#ifdef PH3
  #define PH3_ALT0       (PH3  | ALT0)
#endif
#ifdef PH4
  #define PH4_ALT0       (PH4  | ALT0)
#endif
#ifdef PH5
  #define PH5_ALT0       (PH5  | ALT0)
#endif
#ifdef PH6
  #define PH6_ALT0       (PH6  | ALT0)
#endif
#ifdef PH7
  #define PH7_ALT0       (PH7  | ALT0)
#endif
#ifdef PH8
  #define PH8_ALT0       (PH8  | ALT0)
#endif
#ifdef PH9
  #define PH9_ALT0       (PH9  | ALT0)
#endif
#ifdef PH10
  #define PH10_ALT0      (PH10 | ALT0)
#endif
#ifdef PH11
  #define PH11_ALT0      (PH11 | ALT0)
#endif
#ifdef PH12
  #define PH12_ALT0      (PH12 | ALT0)
#endif
#ifdef PH13
  #define PH13_ALT0      (PH13 | ALT0)
#endif
#ifdef PH14
  #define PH14_ALT0      (PH14 | ALT0)
#endif
#ifdef PH15
  #define PH15_ALT0      (PH15 | ALT0)
#endif
#ifdef PI0
  #define PI0_ALT0       (PI0  | ALT0)
#endif
#ifdef PI1
  #define PI1_ALT0       (PI1  | ALT0)
#endif
#ifdef PI2
  #define PI2_ALT0       (PI2  | ALT0)
#endif
#ifdef PI3
  #define PI3_ALT0       (PI3  | ALT0)
#endif
#ifdef PI4
  #define PI4_ALT0       (PI4  | ALT0)
#endif
#ifdef PI5
  #define PI5_ALT0       (PI5  | ALT0)
#endif
#ifdef PI6
  #define PI6_ALT0       (PI6  | ALT0)
#endif
#ifdef PI7
  #define PI7_ALT0       (PI7  | ALT0)
#endif
#ifdef PI8
  #define PI8_ALT0       (PI8  | ALT0)
#endif
#ifdef PI9
  #define PI9_ALT0       (PI9  | ALT0)
#endif
#ifdef PI10
  #define PI10_ALT0      (PI10 | ALT0)
#endif
#ifdef PI11
  #define PI11_ALT0      (PI11 | ALT0)
#endif
#ifdef PI12
  #define PI12_ALT0      (PI12 | ALT0)
#endif
#ifdef PI13
  #define PI13_ALT0      (PI13 | ALT0)
#endif
#ifdef PI14
  #define PI14_ALT0      (PI14 | ALT0)
#endif
#ifdef PI15
  #define PI15_ALT0      (PI15 | ALT0)
#endif
#ifdef PJ0
  #define PJ0_ALT0       (PJ0  | ALT0)
#endif
#ifdef PJ1
  #define PJ1_ALT0       (PJ1  | ALT0)
#endif
#ifdef PJ2
  #define PJ2_ALT0       (PJ2  | ALT0)
#endif
#ifdef PJ3
  #define PJ3_ALT0       (PJ3  | ALT0)
#endif
#ifdef PJ4
  #define PJ4_ALT0       (PJ4  | ALT0)
#endif
#ifdef PJ5
  #define PJ5_ALT0       (PJ5  | ALT0)
#endif
#ifdef PJ6
  #define PJ6_ALT0       (PJ6  | ALT0)
#endif
#ifdef PJ7
  #define PJ7_ALT0       (PJ7  | ALT0)
#endif
#ifdef PJ8
  #define PJ8_ALT0       (PJ8  | ALT0)
#endif
#ifdef PJ9
  #define PJ9_ALT0       (PJ9  | ALT0)
#endif
#ifdef PJ10
  #define PJ10_ALT0      (PJ10 | ALT0)
#endif
#ifdef PJ11
  #define PJ11_ALT0      (PJ11 | ALT0)
#endif
#ifdef PJ12
  #define PJ12_ALT0      (PJ12 | ALT0)
#endif
#ifdef PJ13
  #define PJ13_ALT0      (PJ13 | ALT0)
#endif
#ifdef PJ14
  #define PJ14_ALT0      (PJ14 | ALT0)
#endif
#ifdef PJ15
  #define PJ15_ALT0      (PJ15 | ALT0)
#endif
#ifdef PK0
  #define PK0_ALT0       (PK0  | ALT0)
#endif
#ifdef PK1
  #define PK1_ALT0       (PK1  | ALT0)
#endif
#ifdef PK2
  #define PK2_ALT0       (PK2  | ALT0)
#endif
#ifdef PK3
  #define PK3_ALT0       (PK3  | ALT0)
#endif
#ifdef PK4
  #define PK4_ALT0       (PK4  | ALT0)
#endif
#ifdef PK5
  #define PK5_ALT0       (PK5  | ALT0)
#endif
#ifdef PK6
  #define PK6_ALT0       (PK6  | ALT0)
#endif
#ifdef PK7
  #define PK7_ALT0       (PK7  | ALT0)
#endif
#ifdef PK8
  #define PK8_ALT0       (PK8  | ALT0)
#endif
#ifdef PK9
  #define PK9_ALT0       (PK9  | ALT0)
#endif
#ifdef PK10
  #define PK10_ALT0      (PK10 | ALT0)
#endif
#ifdef PK11
  #define PK11_ALT0      (PK11 | ALT0)
#endif
#ifdef PK12
  #define PK12_ALT0      (PK12 | ALT0)
#endif
#ifdef PK13
  #define PK13_ALT0      (PK13 | ALT0)
#endif
#ifdef PK14
  #define PK14_ALT0      (PK14 | ALT0)
#endif
#ifdef PK15
  #define PK15_ALT0      (PK15 | ALT0)
#endif
#ifdef PZ0
  #define PZ0_ALT0       (PZ0  | ALT0)
#endif
#ifdef PZ1
  #define PZ1_ALT0       (PZ1  | ALT0)
#endif
#ifdef PZ2
  #define PZ2_ALT0       (PZ2  | ALT0)
#endif
#ifdef PZ3
  #define PZ3_ALT0       (PZ3  | ALT0)
#endif
#ifdef PZ4
  #define PZ4_ALT0       (PZ4  | ALT0)
#endif
#ifdef PZ5
  #define PZ5_ALT0       (PZ5  | ALT0)
#endif
#ifdef PZ6
  #define PZ6_ALT0       (PZ6  | ALT0)
#endif
#ifdef PZ7
  #define PZ7_ALT0       (PZ7  | ALT0)
#endif
#ifdef PZ8
  #define PZ8_ALT0       (PZ8  | ALT0)
#endif
#ifdef PZ9
  #define PZ9_ALT0       (PZ9  | ALT0)
#endif
#ifdef PZ10
  #define PZ10_ALT0      (PZ10 | ALT0)
#endif
#ifdef PZ11
  #define PZ11_ALT0      (PZ11 | ALT0)
#endif
#ifdef PZ12
  #define PZ12_ALT0      (PZ12 | ALT0)
#endif
#ifdef PZ13
  #define PZ13_ALT0      (PZ13 | ALT0)
#endif
#ifdef PZ14
  #define PZ14_ALT0      (PZ14 | ALT0)
#endif
#ifdef PZ15
  #define PZ15_ALT0      (PZ15 | ALT0)
#endif

#endif /*_PINS_ARDUINO_DIGITAL_H_*/
