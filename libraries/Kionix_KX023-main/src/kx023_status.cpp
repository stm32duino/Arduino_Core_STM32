#include "kx023_status.h"

const char *kx023_get_status_string(KX023_Status_t status)
{
  switch (status)
  {
  case KX023_STATUS_OK:
    return "OK (0)"; // Status String + Code
    break;

  case KX023_STATUS_REG_READ_WRITE_ERROR:
  return "Register Read/Write operation FAIL (-1)";
    break;

  case KX023_STATUS_NULL_POINTERS:
  return "Null pointer as parameter (-2)";
    break;

  case KX023_STATUS_I2C_ADDRESS_NOT_FOUND:
  return "I2C address not found (-3)";
    break;

  case KX023_STATUS_DEVICE_NOT_RECOGNIZE:
  return "Device ID (Who Am I) is NOT recognized (-4)";
    break;

  case KX023_STATUS_DEVICE_SELF_TEST_FAIL:
  return "Device Self-test FAIL (-5)";
    break;

  default:
    if (status > 0)
    {
      return "OK (w/ data)";
    }
    else
    {
      return "Unknown";
    }
    break;
  }
}
