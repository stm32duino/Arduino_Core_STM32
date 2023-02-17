/*
 *******************************************************************************
 * Copyright (c) 2022, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#ifndef __SUBGHZ_H
#define __SUBGHZ_H

#include <functional>
#include <stdint.h>
#include <SPI.h>

#if !defined(SUBGHZSPI_BASE)
  #error "This board does not seem to have a SubGhz radio module, cannot use this library."
#endif

extern "C" void SUBGHZ_Radio_IRQHandler();

/**
 * Singleton class to manage the SubGHZ ISR and internal signals
 */
class SubGhzClass {
  public:
    using callback_function_t = std::function<void(void)>;

    // Attach the passed handler to be called (from ISR context) when
    // the radio IRQ triggers, then clear any pending IRQs and enable
    // it.
    //
    // Note that the radio IRQ is *level* triggered, so the callback
    // should either disable directly process the IRQ and clear the IRQ
    // flags in the radio (so the radio module clears its DIO lines
    // before the ISR returns), or the callback should disable the IRQ
    // to prevent it from being triggered over and over again.
    void attachInterrupt(callback_function_t callback);

    // Detach the interrupt handler, disabling the IRQ too.
    void detachInterrupt();

    // Return whether an interrupt callback is currently attached
    // (regardless of whether it is enabled or not).
    bool hasInterrupt();

    // Enable the interrupt again if it was previously disabled using
    // disableInterrupt(). This does *not* clear any pending interrupts,
    // so if the IRQ was triggered while it was disabled, this will
    // cause the callback (previously registered with attachInterrupt)
    // to fire directly.
    void enableInterrupt();

    // Temporarily disable interrupt processing by disabling the IRQ in
    // the NVIC.
    void disableInterrupt();

    // Clear the interrupt pending flag (to suppress an IRQs that
    // happened while the interrupt was disabled).
    void clearPendingInterrupt();

    // Returns whether the interrupt is currently pending (only really
    // useful when the interrupt is disabled, or while some higher
    // priority interrupt is currently running).
    bool isInterruptPending();

    // Update the NSS signal that is internally connected to the radio
    // SPI block.
    // This signal is active-low, so passing LOW activates the block,
    // HIGH deactivates it.
    void setNssActive(bool value);

    // Read back the value written to NSS
    bool isNssActive();

    // Update the RESET signal that is internally connected to the
    // radio. Pass true to put the module in reset, or false to enable
    // the module.
    void setResetActive(bool value);

    // Read back the value written to RESET
    bool isResetActive();

    // Return the state of busy signal exported by the radio module.
    // Note that this uses the RFBUSYS flag that returns the radio busy
    // signal directly, not the RFBUSYMS flag that also returns an extra
    // busy period after every SPI transaction.
    bool isBusy();

    // The SPI object that can be used to talk to the radio. Works
    // like regular SPI objects, except that writeNSS() above must be
    // used to control the (internal) NSS "pin".
    SUBGHZSPIClass SPI;

    // SPI settings to use for the radio. This uses the maximum speed
    // supported by the radio, which should always work (no chance of
    // bad wiring that requires reducing the speed).
    // This value should be passed to `SubGhz.SPI.beginTransaction()`.
    static constexpr SPISettings spi_settings = {16000000, MSBFIRST, SPI_MODE_0};

  protected:
    // To access handleIrq()
    friend void SUBGHZ_Radio_IRQHandler();
    void handleIrq();

  private:
    callback_function_t callback;
};

// Singleton instance, no other instances should be created
extern SubGhzClass SubGhz;

#endif // __SUBGHZ_H
