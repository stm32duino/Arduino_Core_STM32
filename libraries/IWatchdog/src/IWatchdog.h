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

/** @brief Minimal timeout in microseconds. */
#define IWDG_TIMEOUT_MIN    ((4*1000000)/LSI_VALUE)
/** @brief Maximal timeout in microseconds. */
#define IWDG_TIMEOUT_MAX    (((256*1000000)/LSI_VALUE)*IWDG_RLR_RL)

/**
 * @brief Check that a timeout in microseconds is between IWDG_TIMEOUT_MIN and IWDG_TIMEOUT_MAX.
 * @param X Timeout in microseconds.
 */
#define IS_IWDG_TIMEOUT(X)  (((X) >= IWDG_TIMEOUT_MIN) &&\
                             ((X) <= IWDG_TIMEOUT_MAX))

/**
 * @brief Independent watchdog (IWDG) controller, exposed as the global IWatchdog object.
 */
class IWatchdogClass {

  public:
    /**
     * @brief Construct the controller and enable the watchdog peripheral clock when required.
     */
    IWatchdogClass();
    /**
     * @brief Enable the IWDG. Must be called only once.
     *
     * Once enabled, the watchdog cannot be stopped.
     * @param timeout Timeout in microseconds. Ignored if it is not valid (see IS_IWDG_TIMEOUT()).
     * @param window Optional window in microseconds. Default: IWDG_TIMEOUT_MAX.
     */
    void begin(uint32_t timeout, uint32_t window = IWDG_TIMEOUT_MAX);
    /**
     * @brief Set the timeout and window values of the watchdog and refresh its counter.
     * @param timeout Timeout in microseconds. Ignored if the watchdog is
     *        enabled and the value is not valid.
     * @param window Optional window in microseconds. Default: IWDG_TIMEOUT_MAX.
     */
    void set(uint32_t timeout, uint32_t window = IWDG_TIMEOUT_MAX);
    /**
     * @brief Get the current timeout and window values of the watchdog.
     * @param timeout Pointer where the timeout in microseconds is stored.
     *        Nothing is done if NULL.
     * @param window Optional pointer where the window in microseconds is
     *        stored. Default: NULL.
     */
    void get(uint32_t *timeout, uint32_t *window = NULL);
    /**
     * @brief Reload the counter to prevent a watchdog reset.
     *        Does nothing if the watchdog is not enabled.
     */
    void reload(void);
    /**
     * @brief Check whether the watchdog has been enabled with begin().
     * @return true if the watchdog is enabled, false otherwise.
     */
    bool isEnabled(void)
    {
      return _enabled;
    };
    /**
     * @brief Check if the system has resumed from an IWDG reset.
     * @param clear If true, clear the IWDG reset flag after reading it. Default: false.
     * @return true if the last reset was caused by the IWDG, false otherwise.
     */
    bool isReset(bool clear = false);
    /**
     * @brief Clear the IWDG reset flag.
     */
    void clearReset(void);

  private:
    /** @brief true once the watchdog has been enabled with begin(). */
    static bool _enabled;
};

/** @brief Global IWDG instance. */
extern IWatchdogClass IWatchdog;
#endif /* __IWATCHDOG_H__ */
