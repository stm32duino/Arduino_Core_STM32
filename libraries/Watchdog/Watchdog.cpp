#include "Watchdog.h"

static IWDG_HandleTypeDef hiwdg;

void watchdog_init(uint16_t timeout_ms) {
    if (timeout_ms == 0 || timeout_ms > 32768) {
        return;
    }
    hiwdg.Instance = IWDG;
    // Compute the prescaler value. Start with 32 which gives 1ms precision.
    hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
    timeout_ms--;
    if (timeout_ms > 4095) {
        // 2ms precision
        hiwdg.Init.Prescaler = IWDG_PRESCALER_64;
        timeout_ms >>= 1;
    }
    if (timeout_ms > 4095) {
        // 4ms precision
        hiwdg.Init.Prescaler = IWDG_PRESCALER_128;
        timeout_ms >>= 1;
    }
    if (timeout_ms > 4095) {
        // 8ms precision
        hiwdg.Init.Prescaler = IWDG_PRESCALER_256;
        timeout_ms >>= 1;
    }
    hiwdg.Init.Reload = timeout_ms;
    HAL_IWDG_Init(&hiwdg);
}

void watchdog_reset() {
    HAL_IWDG_Refresh(&hiwdg);
}
