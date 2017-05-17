/*
 * <Description>
 *
 * Copyright (C) 2016, STMicroelectronics - All Rights Reserved
 * Author: YOUR NAME <> for STMicroelectronics.
 *
 * License type: GPLv2
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef Sd2Card_h
#define Sd2Card_h

#include "bsp_sd.h"

#define   FALSE      ((uint8_t)0x00)
#define   TRUE       ((uint8_t)0x01)

// card types to match Arduino definition
#define SD_CARD_TYPE_UKN      0
/** Standard capacity V1 SD card */
#define SD_CARD_TYPE_SD1      1
/** Standard capacity V2 SD card */
#define SD_CARD_TYPE_SD2      2
/** High Capacity SD card */
#define SD_CARD_TYPE_SDHC     3
/** High Capacity SD card */
#define SD_CARD_TYPE_SECURED  4

class Sd2Card {
 public:

  uint8_t init(void);
  uint8_t init(uint8_t cspin);

  /** Return the card type: SD V1, SD V2 or SDHC */
  uint8_t type(void) const;

private:
  SD_CardInfo _SdCardInfo;

};
#endif  // sd2Card_h
