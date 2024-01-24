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
 *
 * This example shows how to use the SubGhz library to start up the
 * radio module and read a register through it using an SPI command.
 * This reads the sync word MSB register, since that has a specific
 * reset value.
 */
#include <SubGhz.h>


void setup() {
  Serial.begin(115200);

  // initialize SPI:
  SubGhz.SPI.begin();

  // clear reset to
  SubGhz.setResetActive(false);

  // Start SPI transaction and wait for the radio to wake up (it starts
  // in sleep mode with its busy signal active).
  SubGhz.SPI.beginTransaction(SubGhz.spi_settings);
  SubGhz.setNssActive(true);
  while (SubGhz.isBusy()) /* wait */;

  // Write a command and read the result
  SubGhz.SPI.transfer(0x1D); // Write command: Read_Register()
  SubGhz.SPI.transfer(0x07); // Write MSB of register address: SUBGHZ_LSYNCRH
  SubGhz.SPI.transfer(0x40); // Write LSB of register address: SUBGHZ_LSYNCRH
  uint8_t status = SubGhz.SPI.transfer(0x0);  // Read status
  uint8_t value = SubGhz.SPI.transfer(0x0);  // Read register value

  // End transaction
  SubGhz.setNssActive(false);
  SubGhz.SPI.endTransaction();

  // This should print a register value 0x14 (reset value of the LoRa sync word MSB)
  Serial.print("Status: 0x");
  Serial.println(status, HEX);
  Serial.print("Register value: 0x");
  Serial.println(value, HEX);
}

void loop() {
  /* Nothing to do */
}
