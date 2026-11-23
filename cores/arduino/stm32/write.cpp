/**
  * \file write.cpp
  *
  * Implementation of the newlib _write() syscall, used by the printf() family,
  * by Print::printf() and by core_debug().
  *
  */

#include <unistd.h>
#include "Arduino.h"
#include "uart.h"
#if defined(VIRTIO_LOG)
  #include "virtio_log.h"
#endif

extern "C" {
  /**
   * @brief Write to a file descriptor, called by the C library.
   *
   * The output of stdout and stderr (printf(), core_debug()...) is sent to the
   * debug UART by uart_debug_write(), which initializes it when it is not
   * already used by a Serial instance.
   *
   * @note The UART driver is linked as soon as this function is requested
   * by the C library: using printf() or enabling the core logs (NDEBUG not
   * defined) links it, with its strong USARTx_IRQHandler().
   * @note Weak, a sketch can provide its own.
   *
   * @param file STDOUT_FILENO and STDERR_FILENO for the debug output, STDIN_FILENO
   *             is ignored, otherwise a pointer to a Print object (Print::printf()).
   * @param ptr  Data to write.
   * @param len  Number of bytes to write.
   * @return len.
   */
  __attribute__((weak))
  int _write(int file, char *ptr, int len)
  {
    switch (file) {
      case STDOUT_FILENO:
      case STDERR_FILENO:
#if defined(VIRTIO_LOG)
        virtio_log((uint8_t *)ptr, (uint32_t)len);
#elif defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
        uart_debug_write((uint8_t *)ptr, (uint32_t)len);
#endif
        break;
      case STDIN_FILENO:
        break;
      default:
        ((class Print *)file)->write((uint8_t *)ptr, len);
        break;
    }
    return len;
  }
}
