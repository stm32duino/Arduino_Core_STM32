#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief C library initialization. Calls the constructors of static objects.
 */
void __libc_init_array(void);

/**
 * @brief Board-level initialization, called once before setup().
 *
 * Weak, so a variant or sketch can override it. Calls hw_config_init().
 */
WEAK void init(void)
{
  hw_config_init();
}

#ifdef __cplusplus
}
#endif
