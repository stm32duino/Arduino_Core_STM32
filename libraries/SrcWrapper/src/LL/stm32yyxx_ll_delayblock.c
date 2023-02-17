/* LL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32H7xx
  #include "stm32h7xx_ll_delayblock.c"
#elif STM32MP1xx
  #include "stm32mp1xx_ll_delayblock.c"
#endif
#pragma GCC diagnostic pop
