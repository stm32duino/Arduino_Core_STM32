/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32C0xx
  #include "stm32c0xx_hal_rtc_ex.c"
#elif STM32F0xx
  #include "stm32f0xx_hal_rtc_ex.c"
#elif STM32F1xx
  #include "stm32f1xx_hal_rtc_ex.c"
#elif STM32F2xx
  #include "stm32f2xx_hal_rtc_ex.c"
#elif STM32F3xx
  #include "stm32f3xx_hal_rtc_ex.c"
#elif STM32F4xx
  #include "stm32f4xx_hal_rtc_ex.c"
#elif STM32F7xx
  #include "stm32f7xx_hal_rtc_ex.c"
#elif STM32G0xx
  #include "stm32g0xx_hal_rtc_ex.c"
#elif STM32G4xx
  #include "stm32g4xx_hal_rtc_ex.c"
#elif STM32H5xx
  #include "stm32h5xx_hal_rtc_ex.c"
#elif STM32H7xx
  #include "stm32h7xx_hal_rtc_ex.c"
#elif STM32L0xx
  #include "stm32l0xx_hal_rtc_ex.c"
#elif STM32L1xx
  #include "stm32l1xx_hal_rtc_ex.c"
#elif STM32L4xx
  #include "stm32l4xx_hal_rtc_ex.c"
#elif STM32L5xx
  #include "stm32l5xx_hal_rtc_ex.c"
#elif STM32MP1xx
  #include "stm32mp1xx_hal_rtc_ex.c"
#elif STM32U0xx
  #include "stm32u0xx_hal_rtc_ex.c"
#elif STM32U3xx
  #include "stm32u3xx_hal_rtc_ex.c"
#elif STM32U5xx
  #include "stm32u5xx_hal_rtc_ex.c"
#elif STM32WBxx
  #include "stm32wbxx_hal_rtc_ex.c"
#elif STM32WB0x
  #include "stm32wb0x_hal_rtc_ex.c"
#elif STM32WBAxx
  #include "stm32wbaxx_hal_rtc_ex.c"
#elif STM32WLxx
  #include "stm32wlxx_hal_rtc_ex.c"
#endif
#pragma GCC diagnostic pop
