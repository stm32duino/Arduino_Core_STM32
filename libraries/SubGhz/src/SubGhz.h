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

/**
 * @file    SubGhz.h
 * @brief   Access to the SubGHz radio module: radio IRQ, internal
 *          NSS/RESET/BUSY signals and SPI.
 */

#ifndef __SUBGHZ_H
#define __SUBGHZ_H

#include <functional>
#include <stdint.h>
#include <SPI.h>

#if !defined(SUBGHZSPI_BASE)
  #error "This board does not seem to have a SubGhz radio module, cannot use this library."
#endif

/**
 * @brief ISR entry point for the SubGHz radio IRQ.
 *        Forwards the event to the attached callback.
 */
extern "C" void SUBGHZ_Radio_IRQHandler();

/**
 * @brief Singleton class to manage the SubGHZ ISR and internal signals.
 */
class SubGhzClass {
  public:
    /**
     * @brief Type of the callback called from ISR context when the radio IRQ triggers.
     */
    using callback_function_t = std::function<void(void)>;

    /**
     * @brief Attach the handler called from ISR context when the radio IRQ
     *        triggers, then clear any pending IRQs and enable the IRQ.
     *
     * The radio IRQ is *level* triggered, so the callback must either process
     * the IRQ and clear the IRQ flags in the radio (so the radio clears its
     * DIO lines before the ISR returns), or disable the IRQ to prevent it from
     * being triggered over and over again.
     * @param callback Function called from ISR context when the radio IRQ triggers.
     */
    void attachInterrupt(callback_function_t callback);

    /**
     * @brief Detach the interrupt handler, disabling the IRQ too.
     */
    void detachInterrupt();

    /**
     * @brief Check whether an interrupt callback is attached, regardless of
     *        whether it is enabled.
     * @return true if a callback is attached, false otherwise.
     */
    bool hasInterrupt();

    /**
     * @brief Enable the interrupt again if it was previously disabled using disableInterrupt().
     *
     * This does *not* clear pending interrupts: if the IRQ triggered while it
     * was disabled, the callback registered with attachInterrupt() fires directly.
     */
    void enableInterrupt();

    /**
     * @brief Temporarily disable interrupt processing by disabling the IRQ in the NVIC.
     */
    void disableInterrupt();

    /**
     * @brief Clear the interrupt pending flag, suppressing IRQs that happened
     *        while the interrupt was disabled.
     */
    void clearPendingInterrupt();

    /**
     * @brief Check whether the interrupt is pending.
     *
     * Only really useful when the interrupt is disabled, or while a higher
     * priority interrupt is running.
     * @return true if the interrupt is pending, false otherwise.
     */
    bool isInterruptPending();

    /**
     * @brief Update the NSS signal internally connected to the radio SPI block.
     *
     * The NSS signal is active-low: passing true activates the block (NSS
     * driven LOW), passing false deactivates it (NSS HIGH).
     * @param value true to activate the NSS signal, false to deactivate it.
     */
    void setNssActive(bool value);

    /**
     * @brief Read back the value written to NSS with setNssActive().
     * @return true if the NSS signal is active, false otherwise.
     */
    bool isNssActive();

    /**
     * @brief Update the RESET signal internally connected to the radio.
     * @param value true to put the module in reset, false to enable the module.
     */
    void setResetActive(bool value);

    /**
     * @brief Read back the value written to RESET with setResetActive().
     * @return true if the module is in reset, false otherwise.
     */
    bool isResetActive();

    /**
     * @brief Get the busy signal exported by the radio module.
     *
     * Uses the RFBUSYS flag, which returns the radio busy signal directly,
     * not the RFBUSYMS flag that also returns an extra busy period after
     * every SPI transaction.
     * @return true if the radio is busy, false otherwise.
     */
    bool isBusy();

    /**
     * @brief SPI object used to talk to the radio.
     *
     * Works like a regular SPI object, except that setNssActive() must be used
     * to control the (internal) NSS signal.
     */
    SUBGHZSPIClass SPI;

    /**
     * @brief SPI settings to use for the radio, at the maximum speed
     *        supported by the radio.
     *
     * Pass this value to SubGhz.SPI.beginTransaction().
     */
    static constexpr SPISettings spi_settings = {16000000, MSBFIRST, SPI_MODE0};

  protected:
    // To access handleIrq()
    friend void SUBGHZ_Radio_IRQHandler();
    /**
     * @brief Call the attached callback. Invoked from the ISR, not meant to
     *        be called directly.
     */
    void handleIrq();

  private:
    /**
     * @brief Handler called by handleIrq(), empty if none is attached.
     */
    callback_function_t callback;
};

/**
 * @brief Singleton instance of SubGhzClass. No other instances should be created.
 */
extern SubGhzClass SubGhz;

/**
 * @example ReadRegister.ino
 * Start up the radio module and read a register through it with an SPI command.
 */

#endif // __SUBGHZ_H
