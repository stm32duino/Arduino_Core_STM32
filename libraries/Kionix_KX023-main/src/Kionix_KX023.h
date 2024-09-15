#ifndef __KIONIX_KX023_h__
#define __KIONIX_KX023_h__

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "kx023_data_types.h"
#include "kx023_reg_map.h"
#include "kx023_status.h"

#define KX023_DEFAULT_ADDR 0x1E

class KX023
{
public:
	KX023(TwoWire &wire = Wire, uint8_t slaveAddress = KX023_DEFAULT_ADDR);
	KX023(int csPin, SPIClass &spi = SPI);
	virtual ~KX023();

	KX023_Status_t begin(void);
	void end(void);

	KX023_Interrupt_Type_t getInterruptType(void);
	void clearInterrupt(void);
	void configPhysicalInterruptPin(int interrupt_number, PhysicalInterruptParameter_t params);

	void softwareReset(void);
	void setStandbyMode(void);
	void setOperatingMode(void);

	// ==================================
	// =     NEW DEVELOPING SECTION     =
	// ==================================

	// E1. Asynchronous Read Back Acceleration Data
	KX023_Status_t configAsynchronousReadBackAccelerationData(AccelerationRange_t range, AccelerationOutputDataRate_t odr);
	KX023_Status_t readAsynchronousReadBackAccelerationData(float *x, float *y, float *z);

	// E2. Synchronous Hardware Interrupt Read Back Acceleration Data
	KX023_Status_t configSynchronousHardwareInterruptReadBackAccelerationData(AccelerationRange_t range, AccelerationOutputDataRate_t odr);

	// E3. Sample Buffer-Full Interrupt via physical hardware interrupt
	KX023_Status_t configBufferFullInterrupt(AccelerationRange_t range, AccelerationOutputDataRate_t odr);
	KX023_Status_t readBuffer(uint8_t *buffer);

	// E4. Wake-Up Function via latched physical hardware interrupt
	KX023_Status_t configWakeUpFunction(AccelerationRange_t range, MotionWakeUpOutputDataRate_t odr, float desired_delay_time_sec, float desired_threshold, DirectionInfoParams_t direction);

	// E5. Activate Tilt Position Function
	KX023_Status_t configActivateTiltPosition(AccelerationRange_t range, TiltPositionOutputDataRate_t odr, float desired_delay_time_msec, DirectionInfoParams_t direction);

	// E6. Activate Tap/Double Tap Function
	KX023_Status_t configActivateTapFunction(AccelerationRange_t range, DirectionalTapOutputDataRate_t odr, DirectionInfoParams_t direction, TapMode_t tap_mode);

protected:
	int readRegister(uint8_t address);
	int readRegisters(uint8_t address, uint8_t *data, size_t length);
	int writeRegister(uint8_t address, uint8_t value);

	void setPerformanceLowCurrentMode(void);
	void setPerformanceHighResolutionMode(void);

	void disableNewAccelerationDataInterrupt(void);
	void enableNewAccelerationDataInterrupt(void);

	void setAccelerationDataRange(AccelerationRange_t range);

	void disableTapFunction(void);
	void enableTapFunction(void);

	void disableWakeUpFunction(void);
	void enableWakeUpFunction(void);

	void disableTiltPositionFunction(void);
	void enableTiltPositionFunction(void);

	void enableFiltering(void);
	void disableFiltering(void);

	void setFilterCornerFrequency(FilterCornerFrequency_t frequency);

	void setAccelerationDataRate(AccelerationOutputDataRate_t odr);

	void disablePhysicalInterruptPin(int interrupt_number);
	void enablePhysicalInterruptPin(int interrupt_number, bool interrupt_polarity_active_high, bool interrupt_by_pulse);
	void configPhysicalInterruptEvent(int interrupt_number, bool buffer_full_interrupt, bool watermark_interrupt, bool data_ready_interrupt, bool tap_function_interrupt, bool wake_up_function_interrupt, bool tilt_position_function_interrupt);

	void disableSampleBuffer(void);
	void enableSampleBuffer(void);

	void setSampleBufferResolution(bool use_16_bit_res);

	void disableBufferFullInterrupt(void);
	void enableBufferFullInterrupt(void);

	void setTiltPositionFunctionOutputDataRate(TiltPositionOutputDataRate_t odr);
	void setDirectionalTapFunctionOutputDataRate(DirectionalTapOutputDataRate_t odr);
	void setMotionWakeUpFunctionOutputDataRate(MotionWakeUpOutputDataRate_t odr);

	void setMotionWakeUpInterruptDirection(bool x_negative, bool x_positive, bool y_negative, bool y_positive, bool z_negative, bool z_positive);
	void setInterruptMotionWakeUpTimer(MotionWakeUpOutputDataRate_t odr, float desired_delay_time_sec);
	void setInterruptMotionWakeUpThreshold(float desired_threshold);

	void setTiltPositionInterruptDirection(bool x_negative, bool x_positive, bool y_negative, bool y_positive, bool z_negative, bool z_positive);
	void configTiltPositionTimer(TiltPositionOutputDataRate_t odr, float desired_delay_time_msec);
	void setTiltPositionAngleLowLimit(uint8_t expected_angle);
	void setTiltPositionAngleHighLimit(uint8_t expected_angle);
	void setTiltPositionHysteresisAngle(void);

	void setDirectionalTapInterruptDirection(bool x_negative, bool x_positive, bool y_negative, bool y_positive, bool z_negative, bool z_positive);
	void disableSingleTap(void);
	void enableSingleTap(void);
	void disableDoubleTap(void);
	void enableDoubleTap(void);
	void setDoubleTapMinimumTimeSeparation(DirectionalTapOutputDataRate_t odr, float desired_minimum_time_separation_between_taps);
	void setTapHighThresholdValue(uint8_t value);
	void setTapLowThresholdValue(uint8_t value);

private:
	TwoWire *_wire;
	SPIClass *_spi;
	uint8_t _slaveAddress;
	int _csPin;
	AccelerationRange_t _accelerationRange;

	SPISettings _spiSettings;

	void setBit(uint8_t register_address, uint8_t bit_index);
	void clearBit(uint8_t register_address, uint8_t bit_index);
};

#endif /* __KIONIX_KX023_h__ */
