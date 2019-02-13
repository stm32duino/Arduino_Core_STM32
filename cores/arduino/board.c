#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

void __libc_init_array(void);

WEAK void init(void)
{
  hw_config_init();
}

#ifdef __cplusplus
}
#endif
