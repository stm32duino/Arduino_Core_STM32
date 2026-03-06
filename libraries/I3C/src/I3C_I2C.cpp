#include "I3C.h"
#include <cstring>

#if defined(I3C1_BASE) || defined(I3C2_BASE)

// ============================================================================
// I2C helpers on mixed I3C bus
// ============================================================================
bool I3CBus::isValidI2CStaticAddr(uint8_t addr) const
{
  return (addr >= 0x08U) && (addr < 0x78U);
}

void I3CBus::markI2CAddrUsed(uint8_t addr)
{
  if (addr < 128U) {
    _addrMap[addr] = I3CAddrState::I2CDevice;
  }
}

// ============================================================================
// Explicit I2C helpers on mixed bus
// ============================================================================

int I3CBus::i2cWrite(uint8_t staticAddr,
                     const uint8_t *buf,
                     size_t len,
                     uint32_t timeout)
{
  int result = -1;

  if (_initialized &&
      (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER) &&
      (_busType == I3CBusType::Mixed) &&
      isValidI2CStaticAddr(staticAddr) &&
      (buf != nullptr) &&
      (len != 0U)) {
    I3C_XferTypeDef    context {};
    I3C_PrivateTypeDef priv {};
    uint32_t           controlBuffer[0x0F];
    HAL_StatusTypeDef  st;

    priv.TargetAddr    = staticAddr;
    priv.TxBuf.pBuffer = const_cast<uint8_t *>(buf);
    priv.TxBuf.Size    = static_cast<uint32_t>(len);
    priv.RxBuf.pBuffer = nullptr;
    priv.RxBuf.Size    = 0U;
    priv.Direction     = HAL_I3C_DIRECTION_WRITE;

    context.CtrlBuf.pBuffer = controlBuffer;
    context.CtrlBuf.Size    = 1U;
    context.TxBuf.pBuffer   = const_cast<uint8_t *>(buf);
    context.TxBuf.Size      = static_cast<uint32_t>(len);

    st = HAL_I3C_AddDescToFrame(
           &_hi3c,
           nullptr,
           &priv,
           &context,
           context.CtrlBuf.Size,
           I2C_PRIVATE_WITHOUT_ARB_STOP);

    if (st == HAL_OK) {
      st = HAL_I3C_Ctrl_Transmit(&_hi3c, &context, timeout);
      result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    } else {
      result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    }
  }

  return result;
}

int I3CBus::i2cRead(uint8_t staticAddr,
                    uint8_t *buf,
                    size_t len,
                    uint32_t timeout)
{
  int result = -1;

  if (_initialized &&
      (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER) &&
      (_busType == I3CBusType::Mixed) &&
      isValidI2CStaticAddr(staticAddr) &&
      (buf != nullptr) &&
      (len != 0U)) {
    I3C_XferTypeDef    context {};
    I3C_PrivateTypeDef priv {};
    uint32_t           controlBuffer[0x0F];
    HAL_StatusTypeDef  st;

    priv.TargetAddr    = staticAddr;
    priv.TxBuf.pBuffer = nullptr;
    priv.TxBuf.Size    = 0U;
    priv.RxBuf.pBuffer = buf;
    priv.RxBuf.Size    = static_cast<uint32_t>(len);
    priv.Direction     = HAL_I3C_DIRECTION_READ;

    context.CtrlBuf.pBuffer = controlBuffer;
    context.CtrlBuf.Size    = 1U;
    context.RxBuf.pBuffer   = buf;
    context.RxBuf.Size      = static_cast<uint32_t>(len);

    st = HAL_I3C_AddDescToFrame(
           &_hi3c,
           nullptr,
           &priv,
           &context,
           context.CtrlBuf.Size,
           I2C_PRIVATE_WITHOUT_ARB_STOP);

    if (st == HAL_OK) {
      st = HAL_I3C_Ctrl_Receive(&_hi3c, &context, timeout);
      result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    } else {
      result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    }
  }

  return result;
}

int I3CBus::i2cWriteRead(uint8_t staticAddr,
                         const uint8_t *txBuf,
                         size_t txLen,
                         uint8_t *rxBuf,
                         size_t rxLen,
                         uint32_t timeout)
{
  int result = -1;

  if ((!_initialized) ||
      (_hi3c.Mode != HAL_I3C_MODE_CONTROLLER) ||
      (_busType != I3CBusType::Mixed) ||
      (!isValidI2CStaticAddr(staticAddr)) ||
      (txBuf == nullptr) ||
      (txLen == 0U) ||
      (rxBuf == nullptr) ||
      (rxLen == 0U)) {
    result = -1;
  } else {
    I3C_XferTypeDef    context {};
    I3C_PrivateTypeDef priv {};
    uint32_t           controlBuffer[0x0F];
    HAL_StatusTypeDef  st;

    // 1) write phase with RESTART
    priv.TargetAddr    = staticAddr;
    priv.TxBuf.pBuffer = const_cast<uint8_t *>(txBuf);
    priv.TxBuf.Size    = static_cast<uint32_t>(txLen);
    priv.RxBuf.pBuffer = nullptr;
    priv.RxBuf.Size    = 0U;
    priv.Direction     = HAL_I3C_DIRECTION_WRITE;

    std::memset(&context, 0, sizeof(context));
    context.CtrlBuf.pBuffer = controlBuffer;
    context.CtrlBuf.Size    = 1U;
    context.TxBuf.pBuffer   = const_cast<uint8_t *>(txBuf);
    context.TxBuf.Size      = static_cast<uint32_t>(txLen);

    st = HAL_I3C_AddDescToFrame(
           &_hi3c,
           nullptr,
           &priv,
           &context,
           context.CtrlBuf.Size,
           I2C_PRIVATE_WITHOUT_ARB_RESTART);

    if (st != HAL_OK) {
      result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    } else {
      st = HAL_I3C_Ctrl_Transmit(&_hi3c, &context, timeout);
      if (st != HAL_OK) {
        result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
      } else {
        // 2) read phase with STOP
        priv.TargetAddr    = staticAddr;
        priv.TxBuf.pBuffer = nullptr;
        priv.TxBuf.Size    = 0U;
        priv.RxBuf.pBuffer = rxBuf;
        priv.RxBuf.Size    = static_cast<uint32_t>(rxLen);
        priv.Direction     = HAL_I3C_DIRECTION_READ;

        std::memset(&context, 0, sizeof(context));
        context.CtrlBuf.pBuffer = controlBuffer;
        context.CtrlBuf.Size    = 1U;
        context.RxBuf.pBuffer   = rxBuf;
        context.RxBuf.Size      = static_cast<uint32_t>(rxLen);

        st = HAL_I3C_AddDescToFrame(
               &_hi3c,
               nullptr,
               &priv,
               &context,
               context.CtrlBuf.Size,
               I2C_PRIVATE_WITHOUT_ARB_STOP);

        if (st != HAL_OK) {
          result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
        } else {
          st = HAL_I3C_Ctrl_Receive(&_hi3c, &context, timeout);
          result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
        }
      }
    }
  }

  return result;
}

int I3CBus::i2cWriteRegBuffer(uint8_t staticAddr,
                              uint8_t reg,
                              const uint8_t *pData,
                              size_t len,
                              uint32_t timeout)
{
  int result = -1;

  if ((_initialized) &&
      (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER) &&
      (_busType == I3CBusType::Mixed) &&
      isValidI2CStaticAddr(staticAddr) &&
      (pData != nullptr) &&
      (len != 0U) &&
      (len <= 31U)) {
    I3C_XferTypeDef    context {};
    I3C_PrivateTypeDef priv {};
    uint32_t           controlBuffer[0x0F];
    uint8_t            data[32] = {0};
    HAL_StatusTypeDef  st;

    data[0] = reg;
    memcpy(&data[1], pData, len);

    priv.TargetAddr    = staticAddr;
    priv.TxBuf.pBuffer = data;
    priv.TxBuf.Size    = static_cast<uint32_t>(1U + len);
    priv.RxBuf.pBuffer = nullptr;
    priv.RxBuf.Size    = 0U;
    priv.Direction     = HAL_I3C_DIRECTION_WRITE;

    std::memset(&context, 0, sizeof(context));
    context.CtrlBuf.pBuffer = controlBuffer;
    context.CtrlBuf.Size    = 1U;
    context.TxBuf.pBuffer   = data;
    context.TxBuf.Size      = static_cast<uint32_t>(1U + len);

    st = HAL_I3C_AddDescToFrame(
           &_hi3c,
           nullptr,
           &priv,
           &context,
           context.CtrlBuf.Size,
           I2C_PRIVATE_WITHOUT_ARB_STOP);

    if (st != HAL_OK) {
      result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    } else {
      st = HAL_I3C_Ctrl_Transmit(&_hi3c, &context, timeout);
      result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    }
  }

  return result;
}

int I3CBus::i2cReadRegBuffer(uint8_t staticAddr,
                             uint8_t reg,
                             uint8_t *pData,
                             size_t len,
                             uint32_t timeout)
{
  if ((pData == nullptr) || (len == 0U)) {
    return -1;
  }

  return i2cWriteRead(staticAddr, &reg, 1U, pData, len, timeout);
}

int I3CBus::i2cWriteReg(uint8_t staticAddr,
                        uint8_t reg,
                        uint8_t value,
                        uint32_t timeout)
{
  return i2cWriteRegBuffer(staticAddr, reg, &value, 1U, timeout);
}

int I3CBus::i2cReadReg(uint8_t staticAddr,
                       uint8_t reg,
                       uint8_t &value,
                       uint32_t timeout)
{
  return i2cReadRegBuffer(staticAddr, reg, &value, 1U, timeout);
}

int I3CBus::scanI2CDevices(uint8_t *addrs,
                           size_t maxAddrs,
                           size_t *foundCount,
                           uint32_t trials,
                           uint32_t timeout)
{
  int result = -1;

  if ((_initialized) &&
      (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER) &&
      (_busType == I3CBusType::Mixed) &&
      (addrs != nullptr) &&
      (foundCount != nullptr)) {
    size_t count = 0U;

    for (uint8_t addr = 0x08U; addr < 0x78U; ++addr) {
      if (isI2CDeviceReady(addr, trials, timeout)) {
        if (count < maxAddrs) {
          addrs[count] = addr;
        }
        markI2CAddrUsed(addr);
        ++count;
      }
    }

    *foundCount = count;
    result = 0;
  }

  return result;
}


// ============================================================================
// Unified overloads
// ============================================================================

int I3CBus::write(uint8_t addr,
                  const uint8_t *buf,
                  size_t len,
                  I3CTransferType type,
                  uint32_t timeout)
{
  return (type == I3CTransferType::I2C)
         ? i2cWrite(addr, buf, len, timeout)
         : write(addr, buf, len, timeout);
}

int I3CBus::read(uint8_t addr,
                 uint8_t *buf,
                 size_t len,
                 I3CTransferType type,
                 uint32_t timeout)
{
  return (type == I3CTransferType::I2C)
         ? i2cRead(addr, buf, len, timeout)
         : read(addr, buf, len, timeout);
}

int I3CBus::writeReg(uint8_t addr,
                     uint8_t reg,
                     uint8_t value,
                     I3CTransferType type,
                     uint32_t timeout)
{
  return (type == I3CTransferType::I2C)
         ? i2cWriteReg(addr, reg, value, timeout)
         : writeReg(addr, reg, value, timeout);
}

int I3CBus::readReg(uint8_t addr,
                    uint8_t reg,
                    uint8_t &value,
                    I3CTransferType type,
                    uint32_t timeout)
{
  return (type == I3CTransferType::I2C)
         ? i2cReadReg(addr, reg, value, timeout)
         : readReg(addr, reg, value, timeout);
}

int I3CBus::writeRegBuffer(uint8_t addr,
                           uint8_t reg,
                           const uint8_t *pData,
                           size_t len,
                           I3CTransferType type,
                           uint32_t timeout)
{
  return (type == I3CTransferType::I2C)
         ? i2cWriteRegBuffer(addr, reg, pData, len, timeout)
         : writeRegBuffer(addr, reg, pData, len, timeout);
}

int I3CBus::readRegBuffer(uint8_t addr,
                          uint8_t reg,
                          uint8_t *pData,
                          size_t len,
                          I3CTransferType type,
                          uint32_t timeout)
{
  return (type == I3CTransferType::I2C)
         ? i2cReadRegBuffer(addr, reg, pData, len, timeout)
         : readRegBuffer(addr, reg, pData, len, timeout);
}

#endif
