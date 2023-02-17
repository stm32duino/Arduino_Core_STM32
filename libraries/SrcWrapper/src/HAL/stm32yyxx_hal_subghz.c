/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32WLxx
  #include "stm32wlxx_hal_subghz.c"
#endif
#pragma GCC diagnostic pop
