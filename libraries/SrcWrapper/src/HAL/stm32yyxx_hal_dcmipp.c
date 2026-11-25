/* HAL raised several warnings, ignore them */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifdef STM32H7RSxx
  #include "stm32h7rsxx_hal_dcmipp.c"
#endif
#pragma GCC diagnostic pop
