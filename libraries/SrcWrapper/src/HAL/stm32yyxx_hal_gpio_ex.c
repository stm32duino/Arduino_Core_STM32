/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32F1xx
  #include "stm32f1xx_hal_gpio_ex.c"
#endif
#pragma GCC diagnostic pop
