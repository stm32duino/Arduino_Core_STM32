#include "stm32_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
WEAK void _Error_Handler(const char * msg, int val)
{
  /* User can add his own implementation to report the HAL error return state */
  printf("Error: %s (%i)\n", msg, val);
  while(1)
  {
  }
}

#ifdef __cplusplus
}
#endif
