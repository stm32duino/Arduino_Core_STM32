#include "stm32_def.h"
#include "core_debug.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(NDEBUG)
// Weak: user can override it, see Error_Handler() documentation in stm32_def.h
__attribute__((noreturn)) WEAK void _Error_Handler(const char *msg, int val)
{
  /* User can add his own implementation to report the HAL error return state */
  core_debug("Error: %s (%i)\n", msg, val);
  while (1) {
  }
}
#endif

#ifdef  USE_FULL_ASSERT
// Weak: called by the assert_param() macro when a HAL parameter check fails:
// report the source file name and line number where the error has occurred
WEAK void assert_failed(uint8_t *file, uint32_t line)
{
  _Error_Handler((const char *)file, line);
}
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif
