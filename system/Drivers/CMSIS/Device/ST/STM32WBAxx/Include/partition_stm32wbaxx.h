/**
  ******************************************************************************
  * @file    partition_stm32wbaxx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32WBAxx Device Initial Setup for Secure / Non-Secure Zones
  *          based on CMSIS CORE V5.4.0 partition_ARMCM33.h Template.
  *
  *          The file is included in system_stm32wbaxx_s.c in secure application.
  *          It includes the configuration section that allows to select the
  *          STM32WBAxx device partitioning file for system core secure attributes
  *          and interrupt secure and non-secure assignment.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32wbaxx
  * @{
  */

#ifndef PARTITION_STM32WBAXX_H
#define PARTITION_STM32WBAXX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Secure_configuration_section
  * @{
  */

#if defined(STM32WBA52xx)
  #include "partition_stm32wba52xx.h"
#elif defined(STM32WBA54xx)
  #include "partition_stm32wba54xx.h"
#elif defined(STM32WBA55xx)
  #include "partition_stm32wba55xx.h"
#else
  #error "Please select first the target STM32WBAxx device used in your application (in stm32wbaxx.h file)"
#endif

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PARTITION_STM32WBAXX_H */
/**
  * @}
  */

/**
  * @}
  */
