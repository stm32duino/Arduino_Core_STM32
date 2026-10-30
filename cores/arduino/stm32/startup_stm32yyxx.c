/**
 * @file startup_stm32yyxx.c
 * @brief Includes the CMSIS startup file of the selected device when using the
 * HAL v2 driver.
 */
#ifndef _STARTUP_STM32YYXX_C_
#define _STARTUP_STM32YYXX_C_

#if defined(USE_HALV2_DRIVER)
  #if defined(STM32C531xx)
    #include "startup_stm32c531xx.c"
  #elif defined(STM32C532xx)
    #include "startup_stm32c532xx.c"
  #elif defined(STM32C542xx)
    #include "startup_stm32c542xx.c"
  #elif defined(STM32C551xx)
    #include "startup_stm32c551xx.c"
  #elif defined(STM32C552xx)
    #include "startup_stm32c552xx.c"
  #elif defined(STM32C562xx)
    #include "startup_stm32c562xx.c"
  #elif defined(STM32C591xx)
    #include "startup_stm32c591xx.c"
  #elif defined(STM32C593xx)
    #include "startup_stm32c593xx.c"
  #elif defined(STM32C5A3xx)
    #include "startup_stm32c5a3xx.c"
  #else
    #if !defined(CUSTOM_STARTUP_FILE)
      #error "No CMSIS startup file defined, custom one should be used"
    #else
      #include CUSTOM_STARTUP_FILE
    #endif
  #endif
#endif /* USE_HALV2_DRIVER */
#endif /* _STARTUP_STM32YYXX_C_ */