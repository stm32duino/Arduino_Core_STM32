/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

extern "C" {
#include "stdlib.h"
#include "stdint.h"
}

/**
 * @brief Seed the pseudo-random number generator.
 *
 * A seed of 0 is ignored.
 *
 * @param dwSeed Seed value.
 */
void randomSeed(unsigned long dwSeed)
{
  if (dwSeed != 0) {
    srand(dwSeed) ;
  }
}

/**
 * @brief Return a pseudo-random number in the range [0, howbig).
 *
 * @param howbig Upper bound, exclusive. 0 returns 0.
 * @return Pseudo-random number.
 */
long random(long howbig)
{
  if (howbig == 0) {
    return 0 ;
  }

  return rand() % howbig;
}

/**
 * @brief Return a pseudo-random number in the range [howsmall, howbig).
 *
 * @param howsmall Lower bound, inclusive. Returned directly if it is not below howbig.
 * @param howbig Upper bound, exclusive.
 * @return Pseudo-random number.
 */
long random(long howsmall, long howbig)
{
  if (howsmall >= howbig) {
    return howsmall;
  }

  long diff = howbig - howsmall;

  return random(diff) + howsmall;
}
