/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32H5xx
  #include "stm32h5xx_ll_pka.c"
#elif STM32L4xx
  #include "stm32l4xx_ll_pka.c"
#elif STM32L5xx
  #include "stm32l5xx_ll_pka.c"
#elif STM32U3xx
  #include "stm32u3xx_ll_pka.c"
#elif STM32U5xx
  #include "stm32u5xx_ll_pka.c"
#elif STM32WBxx
  #include "stm32wbxx_ll_pka.c"
#elif STM32WB0x
  #include "stm32wb0x_ll_pka.c"
#elif STM32WBAxx
  #include "stm32wbaxx_ll_pka.c"
#elif STM32WLxx
  #include "stm32wlxx_ll_pka.c"
#endif
#pragma GCC diagnostic pop
