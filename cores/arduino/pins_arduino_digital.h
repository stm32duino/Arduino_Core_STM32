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

#endif /*_PINS_ARDUINO_DIGITAL_H_*/
