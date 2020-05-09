#include "WSerial.h"

WEAK void serialEventRun(void)
{
#if defined(HAVE_HWSERIAL1)
  if (serialEvent1 && Serial1.available()) {
    serialEvent1();
  }
#endif
#if defined(HAVE_HWSERIAL2)
  if (serialEvent2 && Serial2.available()) {
    serialEvent2();
  }
#endif
#if defined(HAVE_HWSERIAL3)
  if (serialEvent3 && Serial3.available()) {
    serialEvent3();
  }
#endif
#if defined(HAVE_HWSERIAL4)
  if (serialEvent4 && Serial4.available()) {
    serialEvent4();
  }
#endif
#if defined(HAVE_HWSERIAL5)
  if (serialEvent5 && Serial5.available()) {
    serialEvent5();
  }
#endif
#if defined(HAVE_HWSERIAL6)
  if (serialEvent6 && Serial6.available()) {
    serialEvent6();
  }
#endif
#if defined(HAVE_HWSERIAL7)
  if (serialEvent7 && Serial7.available()) {
    serialEvent7();
  }
#endif
#if defined(HAVE_HWSERIAL8)
  if (serialEvent8 && Serial8.available()) {
    serialEvent8();
  }
#endif
#if defined(HAVE_HWSERIAL9)
  if (serialEvent9 && Serial9.available()) {
    serialEvent9();
  }
#endif
#if defined(HAVE_HWSERIAL10)
  if (serialEventl10 && Serial10.available()) {
    serialEvent10();
  }
#endif
#if defined(HAVE_HWSERIALLP1)
  if (serialEventLP1 && SerialLP1.available()) {
    serialEventLP1();
  }
#endif
#if defined(HAVE_SERIALUSB)
  if (serialEventUSB && SerialUSB.available()) {
    serialEventUSB();
  }
#endif
#if defined(HAVE_SERIALVIRTIO)
  if (serialEventVirtIO && SerialVirtIO.available()) {
    serialEventVirtIO();
  }
#endif
}

