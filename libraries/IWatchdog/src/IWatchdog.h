#ifndef __IWATCHDOG_H__
#define __IWATCHDOG_H__

#include "Arduino.h"

#if !defined(IWDG) && defined(IWDG1)
#define IWDG IWDG1
#endif

// Minimal timeout in microseconds
#define IWDG_TIMEOUT_MIN    ((4*1000000)/LSI_VALUE)
// Maximal timeout in microseconds
#define IWDG_TIMEOUT_MAX    (((256*1000000)/LSI_VALUE)*IWDG_RLR_RL)

#define IS_IWDG_TIMEOUT(X)  (((X) >= IWDG_TIMEOUT_MIN) &&\
                             ((X) <= IWDG_TIMEOUT_MAX))

class IWatchdogClass {

public:
  void begin(uint32_t timeout, uint32_t window = IWDG_TIMEOUT_MAX);
  void set(uint32_t timeout, uint32_t window = IWDG_TIMEOUT_MAX);
  void get(uint32_t* timeout, uint32_t* window = NULL);
  void reload(void);
  bool isEnabled(void) {return _enabled;};
  bool isReset(bool clear = false);
  void clearReset(void);

private:
  static bool _enabled;
};

extern IWatchdogClass IWatchdog;
#endif /* __IWATCHDOG_H__ */
