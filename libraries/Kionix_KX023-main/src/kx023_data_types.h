#ifndef __KX023_DATA_TYPES_H__
#define __KX023_DATA_TYPES_H__

typedef enum
{
  KX023_STATUS_OK = 0,
  KX023_STATUS_REG_READ_WRITE_ERROR = -1,
  KX023_STATUS_NULL_POINTERS = -2,
  KX023_STATUS_I2C_ADDRESS_NOT_FOUND = -3,
  KX023_STATUS_DEVICE_NOT_RECOGNIZE = -4,
  KX023_STATUS_DEVICE_SELF_TEST_FAIL = -5,
} KX023_Status_t;

typedef enum
{
  KX023_INTERRUPT_UNKNOWN_ERROR = -1,
  KX023_INTERRUPT_NO_INTERRUPT = 0,
  KX023_INTERRUPT_BUFFER_FULL,
  KX023_INTERRUPT_WATERMARK,
  KX023_INTERRUPT_NEW_ACCELERATION_DATA_AVAILABLE,
  KX023_INTERRUPT_SINGLE_TAP,
  KX023_INTERRUPT_DOUBLE_TAP,
  KX023_INTERRUPT_WAKE_UP,
  KX023_INTERRUPT_TILT_POSITION,
} KX023_Interrupt_Type_t;

typedef enum
{
  KX023_ACCLERATION_RANGE_2G = 2,
  KX023_ACCLERATION_RANGE_4G = 4,
  KX023_ACCLERATION_RANGE_8G = 8,
} AccelerationRange_t;

typedef enum
{
  KX023_ODR_12_5HZ = 0,   // 12.5 Hz
  KX023_ODR_25HZ = 1,     // 25 Hz
  KX023_ODR_50HZ = 2,     // 50 Hz
  KX023_ODR_100HZ = 3,    // 100 Hz
  KX023_ODR_200HZ = 4,    // 200 Hz
  KX023_ODR_400HZ = 5,    // 400 Hz
  KX023_ODR_800HZ = 6,    // 800 Hz
  KX023_ODR_1600HZ = 7,   // 1600 Hz
  KX023_ODR_0_781HZ = 8,  // 0.781 Hz
  KX023_ODR_1_563HZ = 9,  // 1.563 Hz
  KX023_ODR_3_125HZ = 10, // 3.125 Hz
  KX023_ODR_6_25HZ = 11,  // 6.25 Hz
} AccelerationOutputDataRate_t;

typedef enum
{
  KX023_TPODR_1_563HZ = 0, // 1.563 Hz
  KX023_TPODR_6_25HZ = 1,  // 6.25 Hz
  KX023_TPODR_12_5HZ = 2,  // 12.5 Hz
  KX023_TPODR_50HZ = 3,    // 50 Hz
} TiltPositionOutputDataRate_t;

typedef enum
{
  KX023_DTODR_50HZ = 0,   // 50 Hz
  KX023_DTODR_100HZ = 1,  // 100 Hz
  KX023_DTODR_200HZ = 2,  // 200 Hz
  KX023_DTODR_400HZ = 3,  // 400 Hz
  KX023_DTODR_12_5HZ = 4, // 12.5 Hz
  KX023_DTODR_25HZ = 5,   // 25 Hz
  KX023_DTODR_800HZ = 6,  // 800 Hz
  KX023_DTODR_1600HZ = 7, // 1600 Hz
} DirectionalTapOutputDataRate_t;

typedef enum
{
  KX023_MWUODR_0_781HZ = 0, // 0.781 Hz
  KX023_MWUODR_1_563HZ = 1, // 1.563 Hz
  KX023_MWUODR_3_125HZ = 2, // 3.125 Hz
  KX023_MWUODR_6_25HZ = 3,  // 6.25 Hz
  KX023_MWUODR_12_5HZ = 4,  // 12.5 Hz
  KX023_MWUODR_25HZ = 5,    // 25 Hz
  KX023_MWUODR_50HZ = 6,    // 50 Hz
  KX023_MWUODR_100HZ = 7,   // 100 Hz
} MotionWakeUpOutputDataRate_t;

typedef enum
{
  FILTER_CORNER_FREQ_ODR_1_9 = 0, // ODR/9
  FILTER_CORNER_FREQ_ODR_1_2 = 1, // ODR/2
} FilterCornerFrequency_t;

typedef struct
{
  bool x_negative;
  bool x_positive;
  bool y_negative;
  bool y_positive;
  bool z_negative;
  bool z_positive;
} DirectionInfoParams_t;

typedef enum
{
  KX023_TAP_MODE_SINGLE_TAP = 1,
  KX023_TAP_MODE_DOUBLE_TAP,
  KX023_TAP_MODE_BOTH,
} TapMode_t;

typedef enum
{
  KX023_INTERRUPT_POLARITY_ACTIVE_LOW = 0,
  KX023_INTERRUPT_POLARITY_ACTIVE_HIGH
} InterruptPolarity_t;

typedef enum
{
  KX023_INTERRUPT_TYPE_LATCH = 0,
  KX023_INTERRUPT_TYPE_PULSE
} InterruptSignalType_t;

typedef struct
{
  bool buffer_full_interrupt : 1;
  bool watermark_interrupt : 1;
  bool data_ready_interrupt : 1;
  bool tap_function_interrupt : 1;
  bool wake_up_function_interrupt : 1;
  bool tilt_position_function_interrupt : 1;
} InterruptEventParams_t;

typedef struct
{
  InterruptPolarity_t polarity;
  InterruptSignalType_t signal_type;
  InterruptEventParams_t events;
} PhysicalInterruptParameter_t;

#endif /* __KX023_DATA_TYPES_H__ */
