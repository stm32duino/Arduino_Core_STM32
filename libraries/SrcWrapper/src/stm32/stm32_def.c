#include "stm32_def.h"
#include "core_debug.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(NDEBUG)
__attribute__((noreturn)) WEAK void _Error_Handler(const char *msg, int val)
{
  /* User can add his own implementation to report the HAL error return state */
  core_debug("Error: %s (%i)\n", msg, val);
  while (1) {
  }
}
#endif

#ifdef  USE_FULL_ASSERT
WEAK void assert_failed(uint8_t *file, uint32_t line)
{
  _Error_Handler((const char *)file, line);
}
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif
