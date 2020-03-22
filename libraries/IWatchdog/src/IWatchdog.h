/*
  Copyright (c) 2018 Frederic Pillon <frederic.pillon@st.com> for
  STMicroelectronics. All right reserved.
  Copyright (c) 2018 Venelin Efremov <ghent360@iqury.us>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
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
    void get(uint32_t *timeout, uint32_t *window = NULL);
    void reload(void);
    bool isEnabled(void)
    {
      return _enabled;
    };
    bool isReset(bool clear = false);
    void clearReset(void);

  private:
    static bool _enabled;
};

extern IWatchdogClass IWatchdog;
#endif /* __IWATCHDOG_H__ */
