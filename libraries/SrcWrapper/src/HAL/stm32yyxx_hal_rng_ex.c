/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32H5xx
  #include "stm32h5xx_hal_rng_ex.c"
#elif STM32H7xx
  #include "stm32h7xx_hal_rng_ex.c"
#elif STM32L4xx
  #include "stm32l4xx_hal_rng_ex.c"
#elif STM32L5xx
  #include "stm32l5xx_hal_rng_ex.c"
#elif STM32U0xx
  #include "stm32u0xx_hal_rng_ex.c"
#elif STM32U3xx
  #include "stm32u3xx_hal_rng_ex.c"
#elif STM32U5xx
  #include "stm32u5xx_hal_rng_ex.c"
#elif STM32WBAxx
  #include "stm32wbaxx_hal_rng_ex.c"
#elif STM32WLxx
  #include "stm32wlxx_hal_rng_ex.c"
#endif
#pragma GCC diagnostic pop
