#ifndef WIRING_SERIAL_H
#define WIRING_SERIAL_H

#include "variant.h"
#include "HardwareSerial.h"
#include "USBSerial.h"
#include "VirtIOSerial.h"

#if defined (USBCON) && defined(USBD_USE_CDC)
  #ifndef DISABLE_GENERIC_SERIALUSB
    #define ENABLE_SERIALUSB
    #if !defined(Serial)
      #define Serial SerialUSB
      #define serialEvent serialEventUSB
    #endif
  #endif

  #if defined(ENABLE_SERIALUSB)
    #define HAVE_SERIALUSB
  #endif

  extern void serialEventUSB(void) __attribute__((weak));
#endif /* USBCON && USBD_USE_CDC */

#if defined(VIRTIOCON)
  #ifndef DISABLE_GENERIC_SERIALVIRTIO
    #define ENABLE_SERIALVIRTIO
    #if !defined(Serial)
      #define Serial SerialVirtIO
      #define serialEvent serialEventVirtIO
    #endif
  #endif

  #if defined(ENABLE_SERIALVIRTIO)
    #define HAVE_SERIALVIRTIO
  #endif

  extern void serialEventVirtIO(void) __attribute__((weak));
#endif /* VIRTIOCON */

#if defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
  #if !defined(HWSERIAL_NONE) && defined(SERIAL_UART_INSTANCE)
    #if SERIAL_UART_INSTANCE == 0
      #define ENABLE_HWSERIALLP1
      #if !defined(Serial)
        #define Serial SerialLP1
        #define serialEvent serialEventLP1
      #endif
    #elif SERIAL_UART_INSTANCE == 1
      #define ENABLE_HWSERIAL1
      #if !defined(Serial)
        #define Serial Serial1
        #define serialEvent serialEvent1
      #endif
    #elif SERIAL_UART_INSTANCE == 2
      #define ENABLE_HWSERIAL2
      #if !defined(Serial)
        #define Serial Serial2
        #define serialEvent serialEvent2
      #endif
    #elif SERIAL_UART_INSTANCE == 3
      #define ENABLE_HWSERIAL3
      #if !defined(Serial)
        #define Serial Serial3
        #define serialEvent serialEvent3
      #endif
    #elif SERIAL_UART_INSTANCE == 4
      #define ENABLE_HWSERIAL4
      #if !defined(Serial)
        #define Serial Serial4
        #define serialEvent serialEvent4
      #endif
    #elif SERIAL_UART_INSTANCE == 5
      #define ENABLE_HWSERIAL5
      #if !defined(Serial)
        #define Serial Serial5
        #define serialEvent serialEvent5
      #endif
    #elif SERIAL_UART_INSTANCE == 6
      #define ENABLE_HWSERIAL6
      #if !defined(Serial)
        #define Serial Serial6
        #define serialEvent serialEvent6
      #endif
    #elif SERIAL_UART_INSTANCE == 7
      #define ENABLE_HWSERIAL7
      #if !defined(Serial)
        #define Serial Serial7
        #define serialEvent serialEvent7
      #endif
    #elif SERIAL_UART_INSTANCE == 8
      #define ENABLE_HWSERIAL8
      #if !defined(Serial)
        #define Serial Serial8
        #define serialEvent serialEvent8
      #endif
    #elif SERIAL_UART_INSTANCE == 9
      #define ENABLE_HWSERIAL9
      #if !defined(Serial)
        #define Serial Serial9
        #define serialEvent serialEvent9
      #endif
    #elif SERIAL_UART_INSTANCE == 10
      #define ENABLE_HWSERIAL10
      #if !defined(Serial)
        #define Serial Serial10
        #define serialEvent serialEvent10
      #endif
    #else
      #if !defined(Serial)
        #warning "No generic 'Serial' defined!"
      #endif
    #endif /* SERIAL_UART_INSTANCE == x */
  #endif /* !HWSERIAL_NONE && SERIAL_UART_INSTANCE */

  #if defined(ENABLE_HWSERIALLP1)
    #if defined(LPUART1_BASE)
      #define HAVE_HWSERIALLP1
    #endif
  #endif
  #if defined(ENABLE_HWSERIAL1)
    #if defined(USART1_BASE)
      #define HAVE_HWSERIAL1
    #endif
  #endif
  #if defined(ENABLE_HWSERIAL2)
    #if defined(USART2_BASE)
      #define HAVE_HWSERIAL2
    #endif
  #endif
  #if defined(ENABLE_HWSERIAL3)
    #if defined(USART3_BASE)
      #define HAVE_HWSERIAL3
    #endif
  #endif
  #if defined(ENABLE_HWSERIAL4)
    #if defined(USART4_BASE) || defined(UART4_BASE)
      #define HAVE_HWSERIAL4
    #endif
  #endif
  #if defined(ENABLE_HWSERIAL5)
    #if defined(USART5_BASE) || defined(UART5_BASE)
      #define HAVE_HWSERIAL5
    #endif
  #endif
  #if defined(ENABLE_HWSERIAL6)
    #if defined(USART6_BASE)
      #define HAVE_HWSERIAL6
    #endif
  #endif
  #if defined(ENABLE_HWSERIAL7)
    #if defined(USART7_BASE) || defined(UART7_BASE)
      #define HAVE_HWSERIAL7
    #endif
  #endif
  #if defined(ENABLE_HWSERIAL8)
    #if defined(USART8_BASE) || defined(UART8_BASE)
      #define HAVE_HWSERIAL8
    #endif
  #endif
  #if defined(ENABLE_HWSERIAL9)
    #if defined(UART9_BASE)
      #define HAVE_HWSERIAL9
    #endif
  #endif
  #if defined(ENABLE_HWSERIAL10)
    #if defined(UART10_BASE)
      #define HAVE_HWSERIAL10
    #endif
  #endif

  extern void serialEvent1(void) __attribute__((weak));
  extern void serialEvent2(void) __attribute__((weak));
  extern void serialEvent3(void) __attribute__((weak));
  extern void serialEvent4(void) __attribute__((weak));
  extern void serialEvent5(void) __attribute__((weak));
  extern void serialEvent6(void) __attribute__((weak));
  extern void serialEvent7(void) __attribute__((weak));
  extern void serialEvent8(void) __attribute__((weak));
  extern void serialEvent9(void) __attribute__((weak));
  extern void serialEvent10(void) __attribute__((weak));
  extern void serialEventLP1(void) __attribute__((weak));
#endif /* HAL_UART_MODULE_ENABLED  && !HAL_UART_MODULE_ONLY */

extern void serialEventRun(void);

#endif /* WIRING_SERIAL_H */
