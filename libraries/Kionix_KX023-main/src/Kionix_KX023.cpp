#include "Kionix_KX023.h"

KX023::KX023(TwoWire &wire, uint8_t slaveAddress)
    : _wire(&wire), _spi(NULL), _slaveAddress(slaveAddress) {}

KX023::KX023(int csPin, SPIClass &spi)
    : _wire(NULL), _spi(&spi), _csPin(csPin),
      _spiSettings(10E6, MSBFIRST, SPI_MODE0) {}

KX023::~KX023() {}

KX023_Status_t KX023::begin(void)
{
  if (_spi != NULL)
  {
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH);
    _spi->begin();
  }
  else
  {
    _wire->begin();
    _wire->beginTransmission(_slaveAddress);
    if (_wire->endTransmission() != 0)
    {
      return KX023_STATUS_I2C_ADDRESS_NOT_FOUND;
    }
  }

  // Check WHO_AM_I register
  if (readRegister(KX023_Who_AM_I_REG) != 0x15)
  {
    end();
    return KX023_STATUS_DEVICE_NOT_RECOGNIZE;
  }

  // Check COTR register
  uint8_t cotr_reg_val = (uint8_t)readRegister(KX023_COTR_REG);
  if (!((cotr_reg_val == 0x55) || (cotr_reg_val == 0xAA))) // TODO: Actual implementation of self-test function
  {
    end();
    return KX023_STATUS_DEVICE_SELF_TEST_FAIL;
  }

  return KX023_STATUS_OK;
}

void KX023::end(void)
{
  if (_spi != NULL)
  {
    _spi->end();
    digitalWrite(_csPin, LOW);
    pinMode(_csPin, INPUT);
  }
  else
  {
    writeRegister(KX023_CNTL1_REG, 0x18);
    _wire->endTransmission();
  }
}

void KX023::clearInterrupt(void)
{
  readRegister(KX023_INT_REL_REG);
}

void KX023::configPhysicalInterruptPin(int interrupt_number, PhysicalInterruptParameter_t params)
{
  enablePhysicalInterruptPin(interrupt_number, (params.polarity == KX023_INTERRUPT_POLARITY_ACTIVE_HIGH), (params.signal_type == KX023_INTERRUPT_TYPE_PULSE));
  configPhysicalInterruptEvent(interrupt_number, params.events.buffer_full_interrupt, params.events.watermark_interrupt, params.events.data_ready_interrupt, params.events.tap_function_interrupt, params.events.wake_up_function_interrupt, params.events.tilt_position_function_interrupt);
}

int KX023::readRegister(uint8_t address)
{
  uint8_t value;

  if (readRegisters(address, &value, 1) != 1)
  {
    return -1;
  }

  return value;
}

int KX023::readRegisters(uint8_t address, uint8_t *data, size_t length)
{
  if (_spi != NULL)
  {
    _spi->beginTransaction(_spiSettings);
    digitalWrite(_csPin, LOW);
    _spi->transfer(0x80 | address);
    _spi->transfer(data, length);
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();
  }
  else
  {
    _wire->beginTransmission(_slaveAddress);
    _wire->write(address);

    if (_wire->endTransmission(false) != 0)
    {
      return -1;
    }

    if (_wire->requestFrom(_slaveAddress, length) != length)
    {
      return 0;
    }

    for (size_t i = 0; i < length; i++)
    {
      *data++ = _wire->read();
    }
  }
  return 1;
}

int KX023::writeRegister(uint8_t address, uint8_t value)
{
  if (_spi != NULL)
  {
    _spi->beginTransaction(_spiSettings);
    digitalWrite(_csPin, LOW);
    _spi->transfer(address);
    _spi->transfer(value);
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();
  }
  else
  {
    _wire->beginTransmission(_slaveAddress);
    _wire->write(address);
    _wire->write(value);
    if (_wire->endTransmission() != 0)
    {
      return 0;
    }
  }
  return 1;
}

void KX023::softwareReset(void)
{
  setStandbyMode();
  setBit(KX023_CNTL2_REG, KX023_CNTL2_SRST_BIT);
}

void KX023::setStandbyMode(void)
{
  clearBit(KX023_CNTL1_REG, KX023_CNTL1_PC1_BIT);
}

void KX023::setOperatingMode(void)
{
  setBit(KX023_CNTL1_REG, KX023_CNTL1_PC1_BIT);
}

void KX023::setPerformanceLowCurrentMode(void)
{
  clearBit(KX023_CNTL1_REG, KX023_CNTL1_RES_BIT);
}

void KX023::setPerformanceHighResolutionMode(void)
{
  setBit(KX023_CNTL1_REG, KX023_CNTL1_RES_BIT);
}

void KX023::disableNewAccelerationDataInterrupt(void)
{
  clearBit(KX023_CNTL1_REG, KX023_CNTL1_DRDYE_BIT);
}

void KX023::enableNewAccelerationDataInterrupt(void)
{
  setBit(KX023_CNTL1_REG, KX023_CNTL1_DRDYE_BIT);
}

void KX023::setAccelerationDataRange(AccelerationRange_t range)
{
  uint8_t cntl1_reg_value = readRegister(KX023_CNTL1_REG);

  cntl1_reg_value &= ~KX023_CNTL1_GSEL_MASK;
  switch (range)
  {
  case KX023_ACCLERATION_RANGE_2G:
    // Do nothing
    _accelerationRange = KX023_ACCLERATION_RANGE_2G;
    break;
  case KX023_ACCLERATION_RANGE_4G:
    cntl1_reg_value |= (1 << KX023_CNTL1_GSEL0_BIT);
    _accelerationRange = KX023_ACCLERATION_RANGE_4G;
    break;
  case KX023_ACCLERATION_RANGE_8G:
    cntl1_reg_value |= (1 << KX023_CNTL1_GSEL1_BIT);
    _accelerationRange = KX023_ACCLERATION_RANGE_8G;
    break;
  default:
    // Do nothing
    _accelerationRange = KX023_ACCLERATION_RANGE_2G;
    break;
  }

  writeRegister(KX023_CNTL1_REG, cntl1_reg_value);
}

void KX023::disableTapFunction(void)
{
  clearBit(KX023_CNTL1_REG, KX023_CNTL1_TDTE_BIT);
}

void KX023::enableTapFunction(void)
{
  setBit(KX023_CNTL1_REG, KX023_CNTL1_TDTE_BIT);
}

void KX023::disableWakeUpFunction(void)
{
  clearBit(KX023_CNTL1_REG, KX023_CNTL1_WUFE_BIT);
}

void KX023::enableWakeUpFunction(void)
{
  setBit(KX023_CNTL1_REG, KX023_CNTL1_WUFE_BIT);
}

void KX023::disableTiltPositionFunction(void)
{
  clearBit(KX023_CNTL1_REG, KX023_CNTL1_TPE_BIT);
}

void KX023::enableTiltPositionFunction(void)
{
  setBit(KX023_CNTL1_REG, KX023_CNTL1_TPE_BIT);
}

void KX023::enableFiltering(void)
{
  clearBit(KX023_ODCNTL_REG, KX023_ODCNTL_IIR_BYPASS_BIT);
}

void KX023::disableFiltering(void)
{
  setBit(KX023_ODCNTL_REG, KX023_ODCNTL_IIR_BYPASS_BIT);
}

void KX023::setFilterCornerFrequency(FilterCornerFrequency_t frequency)
{
  uint8_t reg_value = readRegister(KX023_ODCNTL_REG);
  if (frequency == FILTER_CORNER_FREQ_ODR_1_2)
  {
    reg_value |= (1 << KX023_ODCNTL_LPRO_BIT);
  }
  else
  {
    reg_value &= ~(1 << KX023_ODCNTL_LPRO_BIT);
  }
  writeRegister(KX023_ODCNTL_REG, reg_value);
}

void KX023::setAccelerationDataRate(AccelerationOutputDataRate_t odr)
{
  uint8_t reg_value = readRegister(KX023_ODCNTL_REG);
  reg_value &= ~KX023_ODCNTL_OSA_MASK;
  reg_value |= (((uint8_t)odr << KX023_ODCNTL_OSA0_BIT) & KX023_ODCNTL_OSA_MASK);
  writeRegister(KX023_ODCNTL_REG, reg_value);

  // TODO: Verify ODR that supported by Low Power and High Resolution Mode
}

void KX023::disablePhysicalInterruptPin(int interrupt_number)
{
  switch (interrupt_number)
  {
  case 0: // Disable all
    clearBit(KX023_INC1_REG, KX023_INC1_IEN1_BIT);
    clearBit(KX023_INC5_REG, KX023_INC5_IEN2_BIT);
    break;
  case 1: // Disable Interrupt 1
    clearBit(KX023_INC1_REG, KX023_INC1_IEN1_BIT);
    break;
  case 2: // Disable Interrupt 2
    clearBit(KX023_INC5_REG, KX023_INC5_IEN2_BIT);
    break;
  default:
    break;
  }
}

void KX023::enablePhysicalInterruptPin(int interrupt_number, bool interrupt_polarity_active_high, bool interrupt_by_pulse)
{
  switch (interrupt_number)
  {
  case 1: // Enable Interrupt 1
    setBit(KX023_INC1_REG, KX023_INC1_IEN1_BIT);

    if (interrupt_polarity_active_high)
    {
      setBit(KX023_INC1_REG, KX023_INC1_IEA1_BIT);
    }
    else
    {
      clearBit(KX023_INC1_REG, KX023_INC1_IEA1_BIT);
    }

    if (interrupt_by_pulse)
    {
      setBit(KX023_INC1_REG, KX023_INC1_IEL1_BIT);
    }
    else
    {
      clearBit(KX023_INC1_REG, KX023_INC1_IEL1_BIT);
    }
    break;
  case 2: // Enable Interrupt 2
    setBit(KX023_INC5_REG, KX023_INC5_IEN2_BIT);

    if (interrupt_polarity_active_high)
    {
      setBit(KX023_INC5_REG, KX023_INC5_IEA2_BIT);
    }
    else
    {
      clearBit(KX023_INC5_REG, KX023_INC5_IEA2_BIT);
    }

    if (interrupt_by_pulse)
    {
      setBit(KX023_INC5_REG, KX023_INC5_IEL2_BIT);
    }
    else
    {
      clearBit(KX023_INC5_REG, KX023_INC5_IEL2_BIT);
    }
    break;
  default:
    break;
  }
}

void KX023::configPhysicalInterruptEvent(int interrupt_number, bool buffer_full_interrupt, bool watermark_interrupt, bool data_ready_interrupt, bool tap_function_interrupt, bool wake_up_function_interrupt, bool tilt_position_function_interrupt)
{
  uint8_t regAddress, regValue;
  switch (interrupt_number)
  {
  case 1:
    regAddress = KX023_INC4_REG;
    break;
  case 2:
    regAddress = KX023_INC6_REG;
    break;
  default:
    return; // Invalid interrupt number
    break;
  }

  regValue = 0;
  if (buffer_full_interrupt)
  {
    regValue |= (1 << KX023_INC4_6_BFI_BIT);
  }
  if (watermark_interrupt)
  {
    regValue |= (1 << KX023_INC4_6_WMI_BIT);
  }
  if (data_ready_interrupt)
  {
    regValue |= (1 << KX023_INC4_6_DRDYI_BIT);
  }
  if (tap_function_interrupt)
  {
    regValue |= (1 << KX023_INC4_6_TDTI_BIT);
  }
  if (wake_up_function_interrupt)
  {
    regValue |= (1 << KX023_INC4_6_WUFI_BIT);
  }
  if (tilt_position_function_interrupt)
  {
    regValue |= (1 << KX023_INC4_6_TPI_BIT);
  }
  writeRegister(regAddress, regValue);
}

void KX023::disableSampleBuffer(void)
{
  clearBit(KX023_BUF_CNTL2_REG, KX023_BUF_CNTL2_BUFE_BIT);
}

void KX023::enableSampleBuffer(void)
{
  setBit(KX023_BUF_CNTL2_REG, KX023_BUF_CNTL2_BUFE_BIT);
}

void KX023::setSampleBufferResolution(bool use_16_bit_res)
{
  if (use_16_bit_res)
  {
    setBit(KX023_BUF_CNTL2_REG, KX023_BUF_CNTL2_BRES_BIT);
  }
  else
  {
    clearBit(KX023_BUF_CNTL2_REG, KX023_BUF_CNTL2_BRES_BIT);
  }
}

void KX023::disableBufferFullInterrupt(void)
{
  clearBit(KX023_BUF_CNTL2_REG, KX023_BUF_CNTL2_BFIE_BIT);
}

void KX023::enableBufferFullInterrupt(void)
{
  setBit(KX023_BUF_CNTL2_REG, KX023_BUF_CNTL2_BFIE_BIT);
}

void KX023::setTiltPositionFunctionOutputDataRate(TiltPositionOutputDataRate_t odr)
{
  uint8_t reg_value = readRegister(KX023_CNTL3_REG);
  reg_value &= ~KX023_CNTL3_OTP_MASK;
  reg_value |= (((uint8_t)odr << KX023_CNTL3_OTP0_BIT) & KX023_CNTL3_OTP_MASK);
  writeRegister(KX023_CNTL3_REG, reg_value);
}

void KX023::setDirectionalTapFunctionOutputDataRate(DirectionalTapOutputDataRate_t odr)
{
  uint8_t reg_value = readRegister(KX023_CNTL3_REG);
  reg_value &= ~KX023_CNTL3_OTDT_MASK;
  reg_value |= (((uint8_t)odr << KX023_CNTL3_OTDT0_BIT) & KX023_CNTL3_OTDT_MASK);
  writeRegister(KX023_CNTL3_REG, reg_value);
}

void KX023::setMotionWakeUpFunctionOutputDataRate(MotionWakeUpOutputDataRate_t odr)
{
  uint8_t reg_value = readRegister(KX023_CNTL3_REG);
  reg_value &= ~KX023_CNTL3_OWUF_MASK;
  reg_value |= (((uint8_t)odr << KX023_CNTL3_OWUF0_BIT) & KX023_CNTL3_OWUF_MASK);
  writeRegister(KX023_CNTL3_REG, reg_value);
}

void KX023::setMotionWakeUpInterruptDirection(bool x_negative, bool x_positive, bool y_negative, bool y_positive, bool z_negative, bool z_positive)
{
  uint8_t regValue = 0;
  if (x_negative)
  {
    regValue |= (1 << KX023_INC2_XNWUE_BIT);
  }
  if (x_positive)
  {
    regValue |= (1 << KX023_INC2_XPWUE_BIT);
  }
  if (y_negative)
  {
    regValue |= (1 << KX023_INC2_YNWUE_BIT);
  }
  if (y_positive)
  {
    regValue |= (1 << KX023_INC2_YPWUE_BIT);
  }
  if (z_negative)
  {
    regValue |= (1 << KX023_INC2_ZNWUE_BIT);
  }
  if (z_positive)
  {
    regValue |= (1 << KX023_INC2_ZPWUE_BIT);
  }
  writeRegister(KX023_INC2_REG, regValue);
}

void KX023::setInterruptMotionWakeUpTimer(MotionWakeUpOutputDataRate_t odr, float desired_delay_time_sec)
{
  uint8_t count = 0;
  float odr_value = 0;

  switch (odr)
  {
  case (KX023_MWUODR_0_781HZ):
    odr_value = 0.781;
    break;
  case (KX023_MWUODR_1_563HZ):
    odr_value = 1.563;
    break;
  case (KX023_MWUODR_3_125HZ):
    odr_value = 3.125;
    break;
  case (KX023_MWUODR_6_25HZ):
    odr_value = 6.25;
    break;
  case (KX023_MWUODR_12_5HZ):
    odr_value = 12.5;
    break;
  case (KX023_MWUODR_25HZ):
    odr_value = 25;
    break;
  case (KX023_MWUODR_50HZ):
    odr_value = 50;
    break;
  case (KX023_MWUODR_100HZ):
    odr_value = 100;
    break;
  default:
    return;
    break;
  }

  count = desired_delay_time_sec * odr_value;

  writeRegister(KX023_WUFC_REG, count);
}

void KX023::setInterruptMotionWakeUpThreshold(float desired_threshold)
{
  uint8_t count = 0;

  count = desired_threshold * 16;

  writeRegister(KX023_ATH_REG, count);
}

void KX023::setTiltPositionInterruptDirection(bool x_negative, bool x_positive, bool y_negative, bool y_positive, bool z_negative, bool z_positive)
{
  uint8_t regValue = 0;
  if (x_negative)
  {
    regValue |= (1 << KX023_CNTL2_LEM_BIT);
  }
  if (x_positive)
  {
    regValue |= (1 << KX023_CNTL2_RIM_BIT);
  }
  if (y_negative)
  {
    regValue |= (1 << KX023_CNTL2_DOM_BIT);
  }
  if (y_positive)
  {
    regValue |= (1 << KX023_CNTL2_UPM_BIT);
  }
  if (z_negative)
  {
    regValue |= (1 << KX023_CNTL2_FDM_BIT);
  }
  if (z_positive)
  {
    regValue |= (1 << KX023_CNTL2_FUM_BIT);
  }
  writeRegister(KX023_CNTL2_REG, regValue);
}

void KX023::configTiltPositionTimer(TiltPositionOutputDataRate_t odr, float desired_delay_time_msec)
{
  float ms_time_per_cycle = 0;
  switch (odr)
  {
  case KX023_TPODR_1_563HZ:
    ms_time_per_cycle = 639.795; // 1/1.563Hz
    break;
  case KX023_TPODR_6_25HZ:
    ms_time_per_cycle = 160; // 1/6.25Hz
    break;
  case KX023_TPODR_12_5HZ:
    ms_time_per_cycle = 80; // 1/12.5Hz
    break;
  case KX023_TPODR_50HZ:
    ms_time_per_cycle = 20; // 1/50Hz
    break;
  default:
    return;
    break;
  }

  uint8_t desired_delay_cycle = desired_delay_time_msec / ms_time_per_cycle;
  writeRegister(KX023_TILT_TIMER_REG, desired_delay_cycle);
}

void KX023::setTiltPositionAngleLowLimit(uint8_t expected_angle)
{
  uint8_t expected_angle_step = sin(expected_angle * 0.0174533) * 32;
  writeRegister(KX023_TILT_ANGLE_LL_REG, (expected_angle_step & 0xFF));
}

void KX023::setTiltPositionAngleHighLimit(uint8_t expected_angle)
{
  uint8_t expected_angle_step = sin(expected_angle * 0.0174533) * 32;
  writeRegister(KX023_TILT_ANGLE_HL_REG, (expected_angle_step & 0xFF));
}

void KX023::setTiltPositionHysteresisAngle(void)
{
  writeRegister(KX023_HYST_SET_REG, 0x14); // Default value -> ±15º
}

void KX023::setDirectionalTapInterruptDirection(bool x_negative, bool x_positive, bool y_negative, bool y_positive, bool z_negative, bool z_positive)
{
  uint8_t regValue = 0;
  if (x_negative)
  {
    regValue |= (1 << KX023_INC3_TLEM_BIT);
  }
  if (x_positive)
  {
    regValue |= (1 << KX023_INC3_TRIM_BIT);
  }
  if (y_negative)
  {
    regValue |= (1 << KX023_INC3_TDOM_BIT);
  }
  if (y_positive)
  {
    regValue |= (1 << KX023_INC3_TUPM_BIT);
  }
  if (z_negative)
  {
    regValue |= (1 << KX023_INC3_TFDM_BIT);
  }
  if (z_positive)
  {
    regValue |= (1 << KX023_INC3_TFUM_BIT);
  }
  writeRegister(KX023_INC3_REG, regValue);
}

void KX023::disableSingleTap(void)
{
  clearBit(KX023_TDTRC_REG, KX023_TDTRC_STRE_BIT);
}

void KX023::enableSingleTap(void)
{
  setBit(KX023_TDTRC_REG, KX023_TDTRC_STRE_BIT);
}

void KX023::disableDoubleTap(void)
{
  clearBit(KX023_TDTRC_REG, KX023_TDTRC_DTRE_BIT);
}

void KX023::enableDoubleTap(void)
{
  setBit(KX023_TDTRC_REG, KX023_TDTRC_DTRE_BIT);
}

void KX023::setDoubleTapMinimumTimeSeparation(DirectionalTapOutputDataRate_t odr, float desired_minimum_time_separation_between_taps)
{
  float num_of_cycle = 0;
  switch (odr)
  {
  case KX023_DTODR_12_5HZ:
    num_of_cycle = desired_minimum_time_separation_between_taps * 12.5;
    break;
  case KX023_DTODR_25HZ:
    num_of_cycle = desired_minimum_time_separation_between_taps * 25.0;
    break;
  case KX023_DTODR_50HZ:
    num_of_cycle = desired_minimum_time_separation_between_taps * 50.0;
    break;
  case KX023_DTODR_100HZ:
    num_of_cycle = desired_minimum_time_separation_between_taps * 100.0;
    break;
  case KX023_DTODR_200HZ:
    num_of_cycle = desired_minimum_time_separation_between_taps * 200.0;
    break;
  case KX023_DTODR_400HZ:
  case KX023_DTODR_800HZ:
  case KX023_DTODR_1600HZ:
    num_of_cycle = desired_minimum_time_separation_between_taps * 400.0;
    break;
  default:
    return; // Unsupported ODR
    break;
  }

  uint8_t regValue = num_of_cycle; // Floor number
  writeRegister(KX023_TDTC_REG, regValue);
}

void KX023::setTapHighThresholdValue(uint8_t value)
{
  writeRegister(KX023_TTH_REG, value);
}

void KX023::setTapLowThresholdValue(uint8_t value)
{
  writeRegister(KX023_TTL_REG, value);
}

KX023_Interrupt_Type_t KX023::getInterruptType(void)
{
  uint8_t regValue = readRegister(KX023_INS2_REG);

  if (regValue & (1 << KX023_INS2_BFI_BIT))
  {
    return KX023_INTERRUPT_BUFFER_FULL;
  }

  if (regValue & (1 << KX023_INS2_WMI_BIT))
  {
    return KX023_INTERRUPT_WATERMARK;
  }

  if (regValue & (1 << KX023_INS2_DRDY_BIT))
  {
    return KX023_INTERRUPT_NEW_ACCELERATION_DATA_AVAILABLE;
  }

  switch (regValue & KX023_INS2_TDTS_MASK)
  {
  case 0x00:
    return KX023_INTERRUPT_NO_INTERRUPT;
    break;
  case 0x04:
    return KX023_INTERRUPT_SINGLE_TAP;
    break;
  case 0x08:
    return KX023_INTERRUPT_DOUBLE_TAP;
    break;
  default:
    return KX023_INTERRUPT_UNKNOWN_ERROR;
    break;
  }

  if (regValue & (1 << KX023_INS2_WUFS_BIT))
  {
    return KX023_INTERRUPT_WAKE_UP;
  }

  if (regValue & (1 << KX023_INS2_TPS_BIT))
  {
    return KX023_INTERRUPT_TILT_POSITION;
  }

  return KX023_INTERRUPT_NO_INTERRUPT;
}

KX023_Status_t KX023::configAsynchronousReadBackAccelerationData(AccelerationRange_t range, AccelerationOutputDataRate_t odr)
{
  softwareReset();
  delay(50);

  setStandbyMode();

  // Write 0x40 to Control Register 1 (CNTL1)
  setPerformanceHighResolutionMode();
  setAccelerationDataRange(range);
  // disableNewAccelerationDataInterrupt();
  // disableTapFunction();
  // disableWakeUpFunction();
  // disableTiltPositionFunction();

  // Write 0x02 to Data Control Register (ODCNTL)
  setAccelerationDataRate(odr);

  // Write 0xC0 to Control Register 1 (CNTL1)
  // setOperatingMode();

  return KX023_STATUS_OK;
}

KX023_Status_t KX023::readAsynchronousReadBackAccelerationData(float *x, float *y, float *z)
{
  if ((x == NULL) || (y == NULL) || (z == NULL))
  {
    return KX023_STATUS_NULL_POINTERS;
  }

  int16_t data_buffer[3];

  if (!readRegisters(KX023_XOUTL_REG, (uint8_t *)data_buffer,
                     sizeof(data_buffer)))
  {
    x = 0;
    y = 0;
    z = 0;

    return KX023_STATUS_REG_READ_WRITE_ERROR;
  }

  *x = data_buffer[0] * ((int)(this->_accelerationRange)) / 32768.0;
  *y = data_buffer[1] * ((int)(this->_accelerationRange)) / 32768.0;
  *z = data_buffer[2] * ((int)(this->_accelerationRange)) / 32768.0;

  return KX023_STATUS_OK;
}

KX023_Status_t KX023::configSynchronousHardwareInterruptReadBackAccelerationData(AccelerationRange_t range, AccelerationOutputDataRate_t odr)
{
  softwareReset();
  delay(50);

  /**
   * Write 0x60 to Control Register 1 (CNTL1) to set the accelerometer in
   * stand-by mode, to set the performance mode to High Resolution (full power),
   * G-range to ±2g, and enable the availability of new data as an interrupt.
   */
  setStandbyMode();
  setPerformanceHighResolutionMode();
  setAccelerationDataRange(range);
  enableNewAccelerationDataInterrupt();

  /**
   * Write 0x38 to Interrupt Control Register (INC1) to enable physical
   * interrupt pin INT1, to set the polarity of the physical interrupt to active
   * high and to transmit interrupt pulses with a period of 0.03 ms to 0.05 ms
   * in pin (5).
   */
  // enablePhysicalInterruptPin(1, true, true);

  /**
   * Write 0x10 to Interrupt Control Register 4 (INC4) to set the Data Ready
   * interrupt to be reported on physical interrupt pin INT1.
   */
  // configPhysicalInterruptEvent(1, false, false, true, false, false, false);

  /**
   * Write 0x02 to Data Control Register (ODCNTL) to set the Output Data Rate
   * (ODR) of the accelerometer to 50 Hz.
   */
  setAccelerationDataRate(odr);

  /**
   * Write 0xE0 to Control Register 1 (CNTL1) to set the accelerometer into
   * operating mode (PC1 = 1)
   */
  // setOperatingMode();

  return KX023_STATUS_OK;
}

KX023_Status_t KX023::configBufferFullInterrupt(AccelerationRange_t range, AccelerationOutputDataRate_t odr)
{
  softwareReset();
  delay(50);

  /**
   * Write 0x00 to Control Register 1 (CNTL1) to set the accelerometer in
   * stand-by mode, to set the performance mode to Low Current mode, and G-range
   * to ±2g.
   */
  setStandbyMode();
  setPerformanceLowCurrentMode();
  setAccelerationDataRange(range);

  /**
   * Write 0x38 to Interrupt Control Register (INC1) to enable physical
   * interrupt pin INT1, to set the polarity of the physical interrupt to active
   * high and to transmit interrupt pulses with a period of 0.03 ms to 0.05 ms
   * in pin (5).
   */
  // enablePhysicalInterruptPin(1, true, true);

  /**
   * Write 0x40 to Interrupt Control Register 4 (INC4) to set the Buffer Full
   * interrupt to be reported on physical interrupt pin INT1.
   */
  // configPhysicalInterruptEvent(1, true, false, false, false, false, false);

  /**
   * Write 0x02 to Data Control Register (ODCNTL) to set the Output Data Rate
   * (ODR) of the accelerometer to 50 Hz.
   */
  setAccelerationDataRate(odr);

  /**
   * Write 0xA0 to Buffer Control Register 2 (BUF_CTL2) to activate the sample
   * buffer, to set the resolution of the acceleration data samples collected to
   * 8 bits, to enable report of the interrupt status in INS2, and set the
   * operating mode of the sample buffer to FIFO.
   */
  enableSampleBuffer();
  setSampleBufferResolution(false);
  enableBufferFullInterrupt();

  /**
   * Write 0x80 to Control Register 1 (CNTL1) to set the accelerometer into
   * operating mode (PC1 = 1)
   */
  // setOperatingMode();

  return KX023_STATUS_OK;
}

KX023_Status_t KX023::readBuffer(uint8_t *buffer)
{
  readRegisters(KX023_BUF_READ_REG, buffer, 252);

  return KX023_STATUS_OK;
}

KX023_Status_t KX023::configWakeUpFunction(AccelerationRange_t range, MotionWakeUpOutputDataRate_t odr, float desired_delay_time_sec, float desired_threshold, DirectionInfoParams_t direction)
{
  softwareReset();
  delay(50);

  /**
   * Write 0x42 to Control Register 1 (CNTL1) to set the accelerometer in stand-by mode,
   * to set the performance mode to High Resolution (full power), G-range to ±2g, and enable
   * the Wake Up (motion detect) function.
   */
  setStandbyMode();
  setPerformanceHighResolutionMode();
  enableWakeUpFunction();
  setAccelerationDataRange(range);

  /**
   * Write 0x06 to Control Register 3 (CNTL3) to set the Output Data Rate of the Wake Up
   * function (motion detection) (OWUF) to 50 Hz.
   */
  setMotionWakeUpFunctionOutputDataRate(odr);

  /**
   * Write 0x7F to Interrupt Control Register 2 (INC2) to define the direction of detected
   * motion for all positive and negative directions: x positive (x+), x negative (x-), y
   * positive (y+), y negative (y-), z positive (z+), z negative (z-) directions.
   */
  setMotionWakeUpInterruptDirection(direction.x_negative, direction.x_positive, direction.y_negative, direction.y_positive, direction.z_negative, direction.z_positive);

  /**
   * Write 0x05 to Interrupt Wake-Up Timer (WUFC) to set the time motion must be
   * present before a wake-up interrupt is set to 0.1 second. The following formula is used:
   *
   * WUFC (counts) = Desired Delay Time (sec) x OWUF (Hz)
   * WUFC (counts) = 0.1 x 50 = 5 counts
   *
   * Since the desired delay time is 0.1 second and the OWUF was previously set to 50
   * Hz, then the Wake-Up Timer is 5 counts (0000 0101).
   */
  setInterruptMotionWakeUpTimer(odr, desired_delay_time_sec);

  /**
   * Write 0x08 to Interrupt Wake-Up Threshold (ATH) to set the level to 0.5g. The
   * following formula is used:
   *
   * WAKEUP_THREHOLD (counts) = Desired Threshold (g) x 16 (counts/g)
   * WAKEUP_THREHOLD (counts) = 0.5 x 16 = 8 counts
   * Note that this threshold is differential with respect to the previous reading.
   */
  setInterruptMotionWakeUpThreshold(desired_threshold);

  /**
   * Write 0x30 to Interrupt Control Register (INC1) to output the physical interrupt of the
   * previously defined Wake-Up detect function. This value will create an active high and
   * latched interrupt.
   */
  // enablePhysicalInterruptPin(1, true, true);

  /**
   * Write 0x02 to Interrupt Control Register 4 (INC4) to set the WUF interrupt to be
   * reported on physical interrupt pin INT1.
   */
  // configPhysicalInterruptEvent(1, false, false, false, false, true, false);

  /**
   * Write 0xC2 to Control Register 1 (CNTL1) to set the accelerometer in operating mode
   * with the previously defined settings.
   */
  // setOperatingMode();

  return KX023_STATUS_OK;
}

KX023_Status_t KX023::configActivateTiltPosition(AccelerationRange_t range, TiltPositionOutputDataRate_t odr, float desired_delay_time_msec, DirectionInfoParams_t direction)
{
  softwareReset();
  delay(50);

  /**
   * Write 0x41 to Control Register 1 (CNTL1) to set the accelerometer in stand-by mode,
   * to set the performance mode to High Resolution (full power), G-range to ±2g, and
   * enable the Tilt Position function.
   */
  setStandbyMode();
  setPerformanceHighResolutionMode();
  setAccelerationDataRange(range);
  enableTiltPositionFunction();

  /**
   * Write 0x3F to Control 2 register (CNTL2) to enable Tilt detection from positive and
   * negative directions of all three axes (+x, -x, +y, -y, +z, -z). This step is optional as this
   * is also a default setting.
   */
  setTiltPositionInterruptDirection(direction.x_negative, direction.x_positive, direction.y_negative, direction.y_positive, direction.z_negative, direction.z_positive);

  /*
   * Write 0x98 to Control 3 register (CNTL3) to set the output data rate for the Tilt Position
   * function to 12.5Hz. This step is optional as this is also a default setting.
   */
  setTiltPositionFunctionOutputDataRate(odr);

  /*
   * Write 0x01 to TILT_TIMER register. Here we assume an 80 msec timer will be
   * sufficient. Note that each count value written to this register is calculated as 1/(Tilt
   * Position ODR) = 1/12.5Hz = 80 msec.
   */
  configTiltPositionTimer(odr, desired_delay_time_msec);

  /*
   * Write 0x0C to Tilt Angle Low Limit (TILT_ANGLE_LL) register to set the low threshold
   * to 22º from Horizontal. The value is calculated using the following equations:
   * TILT_ANGLE_LL (counts) = sin θ * (32 (counts/g)). This step is optional as this is also
   * a default setting.
   */
  // setTiltPositionAngleLowLimit(22);

  /*
   * Write 0x2A to Tilt Angle High Limit (TILT_ANGLE_HL) register to set the High
   * threshold. This step is optional as this is also a default setting.
   */
  // setTiltPositionAngleHighLimit(112);

  /*
   * Write 0x14 to HYST_SET register to set the hysteresis that is placed between the
   * screen rotation states to ±15º. This step is optional as this is also a default setting.
   */
  setTiltPositionHysteresisAngle();

  /*
   * Write 0x30 to Interrupt Control Register (INC1) to output the physical interrupt of the
   * previously defined Tap/Double-Tap function. This value will create an active high and
   * latched interrupt.
   */
  // enablePhysicalInterruptPin(1, true, true);

  /*
   * Write 0x01 to Interrupt Control Register 4 (INC4) to set the Tilt Position interrupt
   * (TPI1) to be reported on physical interrupt pin INT1.
   */
  // configPhysicalInterruptEvent(1, false, false, false, false, false, true);

  /*
   * Write 0xC1 to Control Register 1 (CNTL1) to set the accelerometer in operating mode
   * with the previously defined settings.
   */
  // setOperatingMode();

  return KX023_STATUS_OK;
}

KX023_Status_t KX023::configActivateTapFunction(AccelerationRange_t range, DirectionalTapOutputDataRate_t odr, DirectionInfoParams_t direction, TapMode_t tap_mode)
{
  softwareReset();
  delay(50);

  /*
   * Write 0x44 to Control Register 1 (CNTL1) to set the accelerometer in stand-by mode,
   * to set the performance mode to High Resolution (full power), G-range to ±2g, and
   * enable the Directional Tap function.
   */
  setStandbyMode();
  setPerformanceHighResolutionMode();
  setAccelerationDataRange(range);
  enableTapFunction();

  /*
   * Write 0x3F to Interrupt Control 3 register (INC3) to enable tap/double tap from positive
   * and negative directions of all three axes (+x, -x, +y, -y, +z, -z). This step is optional as
   * this is also a default setting.
   */
  setDirectionalTapInterruptDirection(direction.x_negative, direction.x_positive, direction.y_negative, direction.y_positive, direction.z_negative, direction.z_positive);

  /*
   * Write 0x98 to Control 3 register (CNTL3) to set the output data rate for the Directional
   * Tap function to 400Hz. This step is optional as this is also a default setting.
   */
  setDirectionalTapFunctionOutputDataRate(odr);

  /*
   * Write 0x03 to Tap / Double-Tap Register Control register (TDTRC) to enable interrupt
   * on single tap and double tap. This step is optional as this is also a default setting. This
   * setting can be adjusted as needed.
   */
  if ((tap_mode & KX023_TAP_MODE_SINGLE_TAP) == KX023_TAP_MODE_SINGLE_TAP)
  {
    enableSingleTap();
  }
  if ((tap_mode & KX023_TAP_MODE_DOUBLE_TAP) == KX023_TAP_MODE_DOUBLE_TAP)
  {
    enableDoubleTap();
  }

  /*
   * Write 0x78 to Tap / Double-Tap Counter register (TDTC) to set the counter to 0.3 sec.
   * The TDTC counts starts at the beginning of the fist tap and it represents the minimum
   * time separation between the first tap and the second tap in a double tap event. More
   * specifically, the second tap event must end outside of the TDTC. This step is optional
   * as this is also a default setting. This setting can be adjusted as needed.
   */
  setDoubleTapMinimumTimeSeparation(odr, 0.3);

  /*
   * Write 0xCB (203d) to Tap Threshold High register (TTH). This register represents the
   * 8-bit jerk high threshold to determine if a tap is detected. Though this is an 8-bit
   * register, the register value is internally multiplied by two in order to set the high
   * threshold. This multiplication results in a range of 0d to 510d with a resolution of two
   * counts. The Performance Index (PI) is the jerk signal that is expected to be less than
   * this threshold, but greater than the TTL threshold during single and double tap events.
   * This step is optional as this is also a default setting. This setting can be adjusted as
   * needed.
   */
  setTapHighThresholdValue(0xCB);

  /*
   * Write 0x1A (26d) to Tap Threshold Low register (TTL). This register represents the 8-
   * bit (0d–255d) jerk low threshold to determine if a tap is detected. The Performance
   * Index (PI) is the jerk signal that is expected to be greater than this threshold and less
   * than the TTH threshold during single and double tap events. This step is optional as
   * this is also a default setting. This setting can be adjusted as needed.
   */
  setTapLowThresholdValue(0x1A);

  /*
   * Write 0xA2 (162d) to set the FTD counter register to 0.005 seconds. This register
   * contains counter information for the detection of any tap event. A tap event must be
   * above the performance index threshold for at least the low limit (FTDL0 – FTDL2) and
   * no more than the high limit (FTDH0 – FTDH4). This step is optional as this is also a
   * default setting. This setting can be adjusted as needed.
   */
  writeRegister(KX023_FTD_REG, 0xA2); // TODO: Implement a function upon this

  /*
   * Write 0x24 (36d) to set the STD counter register to 0.09 seconds. This register
   * contains counter information for the detection of a double tap event. This register sets
   * the total amount of time that the two taps in a double tap event can be above the PI
   * threshold (TTL). This step is optional as this is also a default setting. This setting can
   * be adjusted as needed.
   */
  writeRegister(KX023_STD_REG, 0xA2); // TODO: Implement a function upon this

  /*
   * Write 0x28 (40d) to set the TLT counter register to 0.1 seconds. This register contains
   * counter information for the detection of a tap event. This register sets the total amount
   * of time that the tap algorithm will count samples that are above the PI threshold (TTL)
   * during a potential tap event. It is used during both single and double tap events.
   * However, reporting of single taps on the physical interrupt pin INT1 or INT2 will occur
   * at the end of the TWS. This step is optional as this is also a default setting. This
   * setting can be adjusted as needed.
   */
  writeRegister(KX023_TLT_REG, 0x28); // TODO: Implement a function upon this

  /*
   * Write 0xA0 (160d) to set the TWS counter register to 0.4 seconds. This register
   * contains counter information for the detection of single and double taps. This counter
   * defines the time window for the entire tap event, single or double, to occur. Reporting
   * of single taps on the physical interrupt pin INT1 or INT2 will occur at the end of this tap
   * window. This step is optional as this is also a default setting. This setting can be
   * adjusted as needed.
   */
  writeRegister(KX023_TWS_REG, 0xA0); // TODO: Implement a function upon this

  /*
   * Write 0x30 to Interrupt Control Register (INC1) to output the physical interrupt of the
   * previously defined Tap/Double-Tap function. This value will create an active high and
   * latched interrupt.
   */
  // enablePhysicalInterruptPin(1, true, true);

  /*
   * Write 0x04 to Interrupt Control Register 4 (INC4) to set the Tap/Double-Tap interrupt
   * (TDTI) to be reported on physical interrupt pin INT1.
   */
  // configPhysicalInterruptEvent(1, false, false, false, true, false, false);

  /*
   * Write 0xC4 to Control Register 1 (CNTL1) to set the accelerometer in operating mode
   * with the previously defined settings.
   */
  // setOperatingMode();

  /*
   * Monitor the physical interrupt INT1 of the accelerometer, if the acceleration input
   * profile satisfies the criteria previously established for Tap/Double-Tap, then there
   * should be a positive latched interrupt present. Also, the interrupt would be reflected in
   * bit 4 of STATUS_REG (INT bit), and bit 3 and bit 2 of INS2 registers. To distinguish
   * between a single and double-tap events, monitor INS2 register bits <TDTS1:TDTS0>.
   * TDTS1 bit3 would be set for Double-tap event, and TDTS0 bit2 for Single-tap event.
   * Also, INS1 register can be monitored to identify the direction the tap came from.
   */

  /*
   * Read Interrupt Release (INT_REL) register to unlatch (clear) the output interrupt
   * created by the Tap/Double-Tap detection function. The read value is dummy.
   */

  return KX023_STATUS_OK;
}

void KX023::setBit(uint8_t register_address, uint8_t bit_index)
{
  if (bit_index > 7)
  {
    return; // Invalid input
  }

  uint8_t reg_value = readRegister(register_address);
  reg_value |= (1 << bit_index);
  writeRegister(register_address, reg_value);
}

void KX023::clearBit(uint8_t register_address, uint8_t bit_index)
{
  if (bit_index > 7)
  {
    return; // Invalid input
  }

  uint8_t reg_value = readRegister(register_address);
  reg_value &= ~(1 << bit_index);
  writeRegister(register_address, reg_value);
}