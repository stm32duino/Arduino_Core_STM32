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
  /* By using the printf function of the library C this inflates the size of
   * the code, use a lot of stack. An alternative, will be to implement a tiny
   * and limited functionality implementation of printf.
   */
  UNUSED(msg);
  UNUSED(val);
  /*printf("Error: %s (%i)\n", msg, val);*/
  while(1)
  {
  }
}

#ifdef __cplusplus
}
#endif
