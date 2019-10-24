#ifdef VIRTIOCON


// #include "openamp/open_amp.h"

/* Configurable parameters */
#ifndef RPMSG_BUFFER_SIZE
#define RPMSG_BUFFER_SIZE	(512)
#endif

#include "virtual_driver/virt_uart.c"

#endif /* VIRTIOCON */
