#include "stm32_def.h"
#include "core_debug.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
#if !defined(NDEBUG)
WEAK void _Error_Handler(const char *msg, int val)
{
  /* User can add his own implementation to report the HAL error return state */
  core_debug("Error: %s (%i)\n", msg, val);
  while (1) {
  }
}
#endif

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
WEAK void assert_failed(uint8_t *file, uint32_t line)
{
  _Error_Handler((const char *)file, line);
}
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif
