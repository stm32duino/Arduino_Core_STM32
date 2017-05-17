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

#include <Arduino.h>
#include "Sd2Card.h"

uint8_t Sd2Card::init(void) {
	if (BSP_SD_Init() == MSD_OK) {
		BSP_SD_GetCardInfo(&_SdCardInfo);
		return TRUE;
	} else {
		return FALSE;
	}
}

uint8_t Sd2Card::init(uint8_t cspin) {
	if (BSP_SD_CSInit() == MSD_OK) {
		BSP_SD_GetCardInfo(&_SdCardInfo);
		return TRUE;
	} else {
		return FALSE;
	}
}

uint8_t Sd2Card::type(void) const {
  uint8_t cardType = SD_CARD_TYPE_UKN;
#if defined (STM32F4xx) || defined(STM32F7xx) || defined(STM32L4xx)
  switch (_SdCardInfo.CardType) {
    case CARD_SDSC:
      switch (_SdCardInfo.CardVersion) {
        case CARD_V1_X:
          cardType = SD_CARD_TYPE_SD1;
        break;
        case CARD_V2_X:
          cardType = SD_CARD_TYPE_SD2;
        break;
        default:
          cardType = SD_CARD_TYPE_UKN;
      }
    break;
    case CARD_SDHC_SDXC:
      cardType = SD_CARD_TYPE_SDHC;
    break;
    case CARD_SECURED:
      cardType = SD_CARD_TYPE_SECURED;
    break;
    default:
      cardType = SD_CARD_TYPE_UKN;
  }
#else /* (STM32F1xx) || defined(STM32F2xx) || defined(STM32L1xx) */
  switch (_SdCardInfo.CardType) {
    case STD_CAPACITY_SD_CARD_V1_1:
      cardType = SD_CARD_TYPE_SD1;
    break;
    case STD_CAPACITY_SD_CARD_V2_0:
      cardType = SD_CARD_TYPE_SD2;
    break;
    case HIGH_CAPACITY_SD_CARD:
      cardType = SD_CARD_TYPE_SDHC;
    break;
    default:
      cardType = SD_CARD_TYPE_UKN;
  }
#endif
  return cardType;
}

