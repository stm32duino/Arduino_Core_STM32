#include "I3C.h"
#include <cstring>

#if defined(I3C1_BASE) || defined(I3C2_BASE)

// ============================================================================
// Global bus instances
// ============================================================================
#if defined(I3C1)
  static I3CBus *g_i3c1Owner = nullptr;
#endif

#if defined(I3C2)
  static I3CBus *g_i3c2Owner = nullptr;
#endif

I3CBus I3C;

// ============================================================================
// File-local constants and helpers
// ============================================================================
static constexpr uint8_t I3C_CCC_ENEC_BCAST    = 0x00U;
static constexpr uint8_t I3C_CCC_DISEC_BCAST   = 0x01U;
static constexpr uint8_t I3C_CCC_RSTDAA_BCAST  = 0x06U;
static constexpr uint8_t I3C_CCC_ENTDAA_BCAST  = 0x07U;
static constexpr uint8_t I3C_CCC_SETAASA_BCAST = 0x29U;
static constexpr uint8_t I3C_CCC_RSTACT_BCAST  = 0x2AU;
static constexpr uint8_t I3C_CCC_SETDASA_DIR   = 0x87U;

static constexpr uint8_t I3C_CCC_EVT_INTR = 0x01U;
static constexpr uint8_t I3C_CCC_EVT_CR   = 0x02U;
static constexpr uint8_t I3C_CCC_EVT_HJ   = 0x08U;
static constexpr uint8_t I3C_CCC_EVT_ALL  = (I3C_CCC_EVT_INTR | I3C_CCC_EVT_CR | I3C_CCC_EVT_HJ);

static constexpr uint8_t I3C_CCC_RSTACT_PERIPHERAL_ONLY    = 0x01U;
static constexpr uint8_t I3C_CCC_RSTACT_RESET_WHOLE_TARGET = 0x02U;

static constexpr uint8_t I3C_CCC_GETPID_DIR = 0x8DU;
static constexpr uint8_t I3C_CCC_GETBCR_DIR = 0x8EU;
static constexpr uint8_t I3C_CCC_GETDCR_DIR = 0x8FU;

static constexpr uint8_t I3C_CCC_ENEC_DIR  = 0x80U;
static constexpr uint8_t I3C_CCC_DISEC_DIR = 0x81U;

#if defined(USE_HALV2_DRIVER)
  static constexpr hal_i3c_transfer_mode_t I3C_PRIVATE_WITH_ARB_RESTART_V2 =
  static_cast<hal_i3c_transfer_mode_t>(LL_I3C_CONTROLLER_MTYPE_PRIVATE);
#endif

/**
  * @brief  Check that an address can be used for an I3C private transfer.
  * @param  addr 7-bit address.
  * @return true if the address is not 0 and below the reserved 0x7E address, false otherwise.
  */
static bool isValidI3CTransferAddr(uint8_t addr)
{
  return (addr != 0U) && (addr < 0x7EU);
}

/**
  * @brief  Rebuild the BCR register value from the BCR fields reported by the HAL.
  * @param  bcrInfo BCR fields.
  * @return BCR register value.
  */
#if defined(USE_HALV2_DRIVER)
static uint8_t reconstructBcr(const hal_i3c_bcr_t &bcrInfo)
{
  uint8_t bcr = 0U;

  bcr |= (bcrInfo.max_data_speed_limitation ? (1U << 0) : 0U);
  bcr |= (bcrInfo.ibi_request_capable       ? (1U << 1) : 0U);
  bcr |= (bcrInfo.ibi_payload               ? (1U << 2) : 0U);
  bcr |= (bcrInfo.offline_capable           ? (1U << 3) : 0U);
  bcr |= (bcrInfo.virtual_target_support    ? (1U << 4) : 0U);
  bcr |= (bcrInfo.advanced_capabilities     ? (1U << 5) : 0U);
  bcr |= (bcrInfo.ctrl_role                 ? (1U << 6) : 0U);
#else
static uint8_t reconstructBcr(const I3C_BCRTypeDef &bcrInfo)
{
  uint8_t bcr = 0U;

  bcr |= (bcrInfo.MaxDataSpeedLimitation ? (1U << 0) : 0U);
  bcr |= (bcrInfo.IBIRequestCapable      ? (1U << 1) : 0U);
  bcr |= (bcrInfo.IBIPayload             ? (1U << 2) : 0U);
  bcr |= (bcrInfo.OfflineCapable         ? (1U << 3) : 0U);
  bcr |= (bcrInfo.VirtualTargetSupport   ? (1U << 4) : 0U);
  bcr |= (bcrInfo.AdvancedCapabilities   ? (1U << 5) : 0U);
  bcr |= (bcrInfo.DeviceRole             ? (1U << 6) : 0U);
#endif
  return bcr;
}

// ============================================================================
// HAL callback bridge
// ============================================================================

/**
  * @brief  HAL notification callback: forward the event to the bus instance
  *         owning the peripheral.
  * @param  hi3c HAL I3C handle.
  * @param  eventId HAL event identifier.
  */
#if defined(USE_HALV2_DRIVER)
extern "C" void HAL_I3C_NotifyCallback(hal_i3c_handle_t *hi3c, uint32_t eventId)
{
  if (hi3c != nullptr) {
#if defined(I3C1)
    if ((hi3c->instance == HAL_I3C1) && (g_i3c1Owner != nullptr)) {
      g_i3c1Owner->handleHalNotify(eventId);
    }
#endif
  }
}
#else
extern "C" void HAL_I3C_NotifyCallback(I3C_HandleTypeDef *hi3c, uint32_t eventId)
{
  if ((hi3c != nullptr) && (hi3c->Instance != nullptr)) {
#if defined(I3C1)
    if ((hi3c->Instance == I3C1) && (g_i3c1Owner != nullptr)) {
      g_i3c1Owner->handleHalNotify(eventId);
    }
#endif

#if defined(I3C2)
    if ((hi3c->Instance == I3C2) && (g_i3c2Owner != nullptr)) {
      g_i3c2Owner->handleHalNotify(eventId);
    }
#endif
  }
}
#endif

// ------------------------------------------------------------------------
// instance
// ------------------------------------------------------------------------
bool I3CBus::prepareInstanceFromPins()
{
  bool result = false;

  if ((_sdaPin != NC) && (_sclPin != NC)) {
    void *merged    = pinmap_merge_peripheral(
                        pinmap_peripheral(_sdaPin, PinMap_I3C_SDA),
                        pinmap_peripheral(_sclPin, PinMap_I3C_SCL));

    if (merged != (void *)NP) {
      _instance = reinterpret_cast<I3C_TypeDef *>(merged);
      result = true;
    }
  }

  return result;
}

// ============================================================================
// Low-level initialization
// ============================================================================

bool I3CBus::initGPIO()
{
  bool result = false;

  if ((_sdaPin != NC) && (_sclPin != NC) && (_instance != nullptr)) {
    pinmap_pinout(_sdaPin, PinMap_I3C_SDA);
    pinmap_pinout(_sclPin, PinMap_I3C_SCL);
    result = true;
  }

  return result;
}

bool I3CBus::initClocks()
{
  bool result = false;

#if defined(I3C1)
  if (_instance == I3C1) {
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_I3C1_EnableClock();
#else
    __HAL_RCC_I3C1_CLK_ENABLE();
#endif
    result = true;
  }
#endif

#if defined(I3C2)
  if (_instance == I3C2) {
#if !defined(USE_HALV2_DRIVER)
    __HAL_RCC_I3C2_CLK_ENABLE();
    result = true;
#else
    result = false;
#endif
  }
#endif

  return result;
}

// ============================================================================
// Controller initialization
// ============================================================================

bool I3CBus::begin(pin_size_t sda,
                   pin_size_t scl,
                   uint32_t freq,
                   I3CBusType type,
                   uint32_t mixedOdHz)
{
  return begin(sda, scl, freq, type, mixedOdHz, I3CControllerConfig{});
}

bool I3CBus::begin(pin_size_t sda,
                   pin_size_t scl,
                   uint32_t freq,
                   I3CBusType type,
                   uint32_t mixedOdHz,
                   const I3CControllerConfig &ctrlCfg)
{
  _sdaPin = digitalPinToPinName(sda);
  _sclPin = digitalPinToPinName(scl);

  _busType = type;
  _mixedBusOdFreq = mixedOdHz;
  _ctrlCfg = ctrlCfg;

  return begin(freq, type, mixedOdHz, ctrlCfg);
}

bool I3CBus::begin(uint32_t freq, I3CBusType type, uint32_t mixedOdHz)
{
  return begin(freq, type, mixedOdHz, I3CControllerConfig{});
}

bool I3CBus::begin(uint32_t freq,
                   I3CBusType type,
                   uint32_t mixedOdHz,
                   const I3CControllerConfig &ctrlCfg)
{
  bool result = true;

  if (!_initialized) {
#if defined(USE_HALV2_DRIVER)
    std::memset(&_hi3c, 0, sizeof(_hi3c));
#else
    _hi3c.Instance = nullptr;
#endif
    _instance = nullptr;

    _busType = type;
    _mixedBusOdFreq = mixedOdHz;
    _ctrlCfg = ctrlCfg;

    if (!prepareInstanceFromPins() || !initClocks() || !initGPIO()) {
      result = false;
    } else {
      std::memset(&_hi3c, 0, sizeof(_hi3c));

#if defined(USE_HALV2_DRIVER)

      hal_i3c_t halInstance = HAL_I3C1;
      if (_instance != I3C1) {
        result = false;
      } else {
        if (HAL_I3C_Init(&_hi3c, halInstance) != HAL_OK) {
          result = false;
        }
      }

      if (result) {
        hal_i3c_ctrl_config_t ctrlTimingCfg {};
        uint32_t srcFreq = HAL_I3C_GetClockFreq(&_hi3c);

        if (!buildControllerTiming(srcFreq, freq, _busType, _mixedBusOdFreq, ctrlTimingCfg)) {
          result = false;
        } else if (HAL_I3C_CTRL_SetConfig(&_hi3c, &ctrlTimingCfg) != HAL_OK) {
          result = false;
        }
      }

#if defined(LL_I3C_END_OF_FRAME_CPLT_ENABLE)
      if (result) {
        LL_I3C_SetEndOfFrameMode(_instance, LL_I3C_END_OF_FRAME_CPLT_ENABLE);
      }
#endif

      if (result) {
        hal_i3c_ctrl_fifo_config_t fifoCfg {};

        fifoCfg.rx_fifo_threshold = static_cast<hal_i3c_rx_fifo_threshold_t>(_ctrlCfg.rxFifoThreshold);
        fifoCfg.tx_fifo_threshold = static_cast<hal_i3c_tx_fifo_threshold_t>(_ctrlCfg.txFifoThreshold);

        const bool controlFifoEnabled = (_ctrlCfg.controlFifo != 0U);
        const bool statusFifoEnabled  = (_ctrlCfg.statusFifo != 0U);

        if (controlFifoEnabled && statusFifoEnabled) {
          fifoCfg.ctrl_fifo = HAL_I3C_CTRL_FIFO_ALL;
        } else if (controlFifoEnabled) {
          fifoCfg.ctrl_fifo = HAL_I3C_CTRL_FIFO_CONTROL_ONLY;
        } else if (statusFifoEnabled) {
          fifoCfg.ctrl_fifo = HAL_I3C_CTRL_FIFO_STATUS_ONLY;
        } else {
          fifoCfg.ctrl_fifo = HAL_I3C_CTRL_FIFO_NONE;
        }

        if (HAL_I3C_CTRL_SetConfigFifo(&_hi3c, &fifoCfg) != HAL_OK) {
          result = false;
        }
      }

      if (result) {
        if (HAL_I3C_CTRL_SetConfigOwnDynamicAddress(&_hi3c, _ctrlCfg.dynamicAddr) != HAL_OK) {
          result = false;
        }
      }

      if (result) {
        uint32_t stallFeatures = HAL_I3C_CTRL_STALL_NONE;

        if (_ctrlCfg.ackStall) {
          stallFeatures |= HAL_I3C_CTRL_STALL_ACK;
        }
        if (_ctrlCfg.cccStall) {
          stallFeatures |= HAL_I3C_CTRL_STALL_CCC;
        }
        if (_ctrlCfg.txStall) {
          stallFeatures |= HAL_I3C_CTRL_STALL_TX;
        }
        if (_ctrlCfg.rxStall) {
          stallFeatures |= HAL_I3C_CTRL_STALL_RX;
        }

        if (HAL_I3C_CTRL_SetConfigStallTime(&_hi3c, _ctrlCfg.stallTime, stallFeatures) != HAL_OK) {
          result = false;
        }
      }

      if (result) {
        if (_ctrlCfg.hotJoinAllowed) {
          if (HAL_I3C_CTRL_EnableHotJoinAllowed(&_hi3c) != HAL_OK) {
            result = false;
          }
        } else {
          if (HAL_I3C_CTRL_DisableHotJoinAllowed(&_hi3c) != HAL_OK) {
            result = false;
          }
        }
      }

      if (result) {
        if (_ctrlCfg.highKeeperSDA) {
          if (HAL_I3C_CTRL_EnableHighKeeperSDA(&_hi3c) != HAL_OK) {
            result = false;
          }
        } else {
          if (HAL_I3C_CTRL_DisableHighKeeperSDA(&_hi3c) != HAL_OK) {
            result = false;
          }
        }
      }

      if (result) {
        _hi3c.mode = HAL_I3C_MODE_CTRL;
        registerInstanceOwner();
        _initialized = true;
        _role = I3CRole::Controller;
      }

#else

      _hi3c.Instance = _instance;
      _hi3c.Mode     = HAL_I3C_MODE_CONTROLLER;

      LL_I3C_CtrlBusConfTypeDef outCtrl {};

      if (!buildControllerTiming(freq, outCtrl)) {
        result = false;
      } else {
        _hi3c.Init.CtrlBusCharacteristic = outCtrl;
      }

      if (result) {
        if (HAL_I3C_Init(&_hi3c) != HAL_OK) {
          result = false;
        } else {
#if defined(LL_I3C_END_OF_FRAME_CPLT_ENABLE)
          LL_I3C_SetEndOfFrameMode(_instance, LL_I3C_END_OF_FRAME_CPLT_ENABLE);
#endif
          if (result) {
            I3C_FifoConfTypeDef fifoCfg {};
            fifoCfg.RxFifoThreshold = _ctrlCfg.rxFifoThreshold;
            fifoCfg.TxFifoThreshold = _ctrlCfg.txFifoThreshold;
            fifoCfg.ControlFifo     = _ctrlCfg.controlFifo;
            fifoCfg.StatusFifo      = _ctrlCfg.statusFifo;

            if (HAL_I3C_SetConfigFifo(&_hi3c, &fifoCfg) != HAL_OK) {
              result = false;
            } else {
              I3C_CtrlConfTypeDef ctrlCfgHal {};
              ctrlCfgHal.DynamicAddr    = _ctrlCfg.dynamicAddr;
              ctrlCfgHal.StallTime      = _ctrlCfg.stallTime;
              ctrlCfgHal.HotJoinAllowed = _ctrlCfg.hotJoinAllowed ? ENABLE : DISABLE;
              ctrlCfgHal.ACKStallState  = _ctrlCfg.ackStall ? ENABLE : DISABLE;
              ctrlCfgHal.CCCStallState  = _ctrlCfg.cccStall ? ENABLE : DISABLE;
              ctrlCfgHal.TxStallState   = _ctrlCfg.txStall ? ENABLE : DISABLE;
              ctrlCfgHal.RxStallState   = _ctrlCfg.rxStall ? ENABLE : DISABLE;
              ctrlCfgHal.HighKeeperSDA  = _ctrlCfg.highKeeperSDA ? ENABLE : DISABLE;

              if (HAL_I3C_Ctrl_Config(&_hi3c, &ctrlCfgHal) != HAL_OK) {
                result = false;
              } else {
                registerInstanceOwner();
                _initialized = true;
                _role = I3CRole::Controller;
              }
            }
          }
        }
      }

#endif

      if (!result) {
#if defined(USE_HALV2_DRIVER)
        HAL_I3C_DeInit(&_hi3c);
#else
        if (_hi3c.Instance != nullptr) {
          (void)HAL_I3C_DeInit(&_hi3c);
        }
#endif
        unregisterInstanceOwner();
        _initialized = false;
        _role = I3CRole::None;
      }
    }
  }

  return result;
}


void I3CBus::setBusType(I3CBusType type)
{
  _busType = type;
}

I3CBusType I3CBus::getBusType() const
{
  return _busType;
}

void I3CBus::setMixedBusOpenDrainFrequency(uint32_t hz)
{
  _mixedBusOdFreq = hz;
}

uint32_t I3CBus::getMixedBusOpenDrainFrequency() const
{
  return _mixedBusOdFreq;
}

I3CRole I3CBus::getRole() const
{
  return _role;
}

bool I3CBus::isController() const
{
  return _role == I3CRole::Controller;
}

bool I3CBus::isTarget() const
{
  return _role == I3CRole::Target;
}



bool I3CBus::setClock(uint32_t i3cFreq)
{
  bool result = false;

  if (_initialized && (i3cFreq != 0U)) {
#if defined(USE_HALV2_DRIVER)
    if (_hi3c.mode == HAL_I3C_MODE_CTRL) {
      hal_i3c_ctrl_config_t outCtrl {};

      if (buildControllerTiming(getPeripheralClockFreq(),
                                i3cFreq,
                                _busType,
                                _mixedBusOdFreq,
                                outCtrl) &&
          (HAL_I3C_CTRL_SetConfig(&_hi3c, &outCtrl) == HAL_OK)) {
        result = true;
      }
    }
#else
    if (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER) {
      LL_I3C_CtrlBusConfTypeDef outCtrl {};

      if (buildControllerTiming(i3cFreq, outCtrl) &&
          (HAL_I3C_Ctrl_BusCharacteristicConfig(&_hi3c, &outCtrl) == HAL_OK)) {
        result = true;
      }
    }
#endif
  }

  return result;
}

void I3CBus::end()
{
  if (_initialized) {

    disableIRQs();
    unregisterInstanceOwner();

    (void)HAL_I3C_DeInit(&_hi3c);

    deinitGPIO();
    deinitClocks();

    _initialized = false;
    _role = I3CRole::None;

#if !defined(USE_HALV2_DRIVER)
    _ibiPending = false;
    _lastIbi = {};
    _targetEventPending = false;
    _lastTargetEventId = 0U;
#endif

    std::memset(&_hi3c, 0, sizeof(_hi3c));
    _instance = nullptr;
  }
}

void I3CBus::deinitClocks()
{
#if defined(I3C1)
  if (_instance == I3C1) {
#if defined(USE_HALV2_DRIVER)
    HAL_RCC_I3C1_Reset();
    HAL_RCC_I3C1_DisableClock();
#else
    __HAL_RCC_I3C1_FORCE_RESET();
    __HAL_RCC_I3C1_RELEASE_RESET();
    __HAL_RCC_I3C1_CLK_DISABLE();
#endif
  }
#endif

#if defined(I3C2)
  if (_instance == I3C2) {
#if !defined(USE_HALV2_DRIVER)
    __HAL_RCC_I3C2_FORCE_RESET();
    __HAL_RCC_I3C2_RELEASE_RESET();
    __HAL_RCC_I3C2_CLK_DISABLE();
#endif
  }
#endif
}

void I3CBus::deinitGPIO()
{
  if (_sdaPin != NC) {
    pin_function(_sdaPin, STM_PIN_DATA(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0));
  }

  if (_sclPin != NC) {
    pin_function(_sclPin, STM_PIN_DATA(STM_MODE_ANALOG, LL_GPIO_PULL_NO, 0));
  }
}

bool  I3CBus::flushAllFifos()
{
  bool result = false;

  if (_initialized) {
#if defined(USE_HALV2_DRIVER)
    result = (HAL_I3C_FlushAllFifos(&_hi3c) == HAL_OK);
#else
    result = (HAL_I3C_FlushAllFifo(&_hi3c) == HAL_OK);
#endif
  }

  return result;
}

// ============================================================================
// Default I3C controller transfers
// ============================================================================

int I3CBus::write(uint8_t dynAddr,
                  const uint8_t *buf,
                  size_t len,
                  uint32_t timeout)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)
  if (_initialized &&
      (_hi3c.mode == HAL_I3C_MODE_CTRL) &&
      isValidI3CTransferAddr(dynAddr) &&
      (buf != nullptr) &&
      (len != 0U)) {
    uint32_t                controlBuffer[1] = {};
    hal_i3c_transfer_ctx_t  ctx {};
    hal_i3c_private_desc_t  priv[] = {
      { dynAddr, static_cast<uint32_t>(len), HAL_I3C_DIRECTION_WRITE },
    };

    if ((HAL_I3C_CTRL_ResetTransferCtx(&ctx) == HAL_OK) &&
        (HAL_I3C_CTRL_InitTransferCtxTc(&ctx, controlBuffer, 1U) == HAL_OK) &&
        (HAL_I3C_CTRL_InitTransferCtxTx(&ctx, buf, static_cast<uint32_t>(len)) == HAL_OK) &&
        (HAL_I3C_CTRL_BuildTransferCtxPrivate(&ctx,
                                              priv,
                                              COUNTOF(priv),
                                              HAL_I3C_PRIVATE_WITH_ARB_STOP) == HAL_OK)) {
      hal_status_t st = HAL_I3C_CTRL_Transfer(&_hi3c, &ctx, timeout);
      result = HAL_I3C_GetError(_hi3c, st);
    }
  }
#else
  if (_initialized &&
      (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER) &&
      isValidI3CTransferAddr(dynAddr) &&
      (buf != nullptr) &&
      (len != 0U)) {
    I3C_XferTypeDef    context {};
    I3C_PrivateTypeDef priv {};
    uint32_t           controlBuffer[1] = {};
    HAL_StatusTypeDef  st;

    priv.TargetAddr    = dynAddr;
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
           I3C_PRIVATE_WITH_ARB_STOP);

    if (st == HAL_OK) {
      st = HAL_I3C_Ctrl_Transmit(&_hi3c, &context, timeout);
      result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    } else {
      result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    }
  }
#endif

  return result;
}

int I3CBus::read(uint8_t dynAddr,
                 uint8_t *buf,
                 size_t len,
                 uint32_t timeout)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)
  if (_initialized &&
      (_hi3c.mode == HAL_I3C_MODE_CTRL) &&
      isValidI3CTransferAddr(dynAddr) &&
      (buf != nullptr) &&
      (len != 0U)) {
    uint32_t                controlBuffer[1] = {};
    hal_i3c_transfer_ctx_t  ctx {};
    hal_i3c_private_desc_t  priv[] = {
      { dynAddr, static_cast<uint32_t>(len), HAL_I3C_DIRECTION_READ },
    };

    if ((HAL_I3C_CTRL_ResetTransferCtx(&ctx) == HAL_OK) &&
        (HAL_I3C_CTRL_InitTransferCtxTc(&ctx, controlBuffer, 1U) == HAL_OK) &&
        (HAL_I3C_CTRL_InitTransferCtxRx(&ctx, buf, static_cast<uint32_t>(len)) == HAL_OK) &&
        (HAL_I3C_CTRL_BuildTransferCtxPrivate(&ctx, priv, COUNTOF(priv), HAL_I3C_PRIVATE_WITH_ARB_STOP) == HAL_OK)) {
      hal_status_t st = HAL_I3C_CTRL_Transfer(&_hi3c, &ctx, timeout);
      result = HAL_I3C_GetError(_hi3c, st);
    }
  }
#else
  if (_initialized &&
      (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER) &&
      isValidI3CTransferAddr(dynAddr) &&
      (buf != nullptr) &&
      (len != 0U)) {
    I3C_XferTypeDef    context {};
    I3C_PrivateTypeDef priv {};
    uint32_t           controlBuffer[1] = {};
    HAL_StatusTypeDef  st;

    priv.TargetAddr    = dynAddr;
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
           I3C_PRIVATE_WITH_ARB_STOP);

    if (st == HAL_OK) {
      st = HAL_I3C_Ctrl_Receive(&_hi3c, &context, timeout);
      result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    } else {
      result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    }
  }
#endif

  return result;
}

int I3CBus::writeRegBuffer(uint8_t dynAddr,
                           uint8_t reg,
                           const uint8_t *pData,
                           size_t len,
                           uint32_t timeout)
{
  int result = 0;

  if ((!_initialized) || (pData == nullptr) || (len == 0U) || (len > 31U)) {
    result = -1;
  } else {
#if defined(USE_HALV2_DRIVER)
    uint32_t               controlBuffer[1] = {};
    uint8_t                data[32] = {0};
    hal_i3c_transfer_ctx_t ctx {};
    hal_i3c_private_desc_t priv[] = {
      { dynAddr, static_cast<uint32_t>(1U + len), HAL_I3C_DIRECTION_WRITE },
    };

    data[0] = reg;
    memcpy(&data[1], pData, len);

    if ((HAL_I3C_CTRL_ResetTransferCtx(&ctx) == HAL_OK) &&
        (HAL_I3C_CTRL_InitTransferCtxTc(&ctx, controlBuffer, 1U) == HAL_OK) &&
        (HAL_I3C_CTRL_InitTransferCtxTx(&ctx, data, static_cast<uint32_t>(1U + len)) == HAL_OK) &&
        (HAL_I3C_CTRL_BuildTransferCtxPrivate(&ctx,
                                              priv,
                                              COUNTOF(priv),
                                              I3C_PRIVATE_WITH_ARB_RESTART_V2) == HAL_OK)) {
      hal_status_t st = HAL_I3C_CTRL_Transfer(&_hi3c, &ctx, timeout);
      result = HAL_I3C_GetError(_hi3c, st);
    } else {
      result = -1;
    }
#else
    I3C_XferTypeDef    context {};
    I3C_PrivateTypeDef priv {};
    uint32_t           controlBuffer[1] = {};
    uint8_t            data[32] = {0};
    HAL_StatusTypeDef  st;

    data[0] = reg;
    memcpy(&data[1], pData, len);

    priv.TargetAddr    = dynAddr;
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
           I3C_PRIVATE_WITH_ARB_RESTART);

    if (st != HAL_OK) {
      result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    } else {
      st = HAL_I3C_Ctrl_Transmit(&_hi3c, &context, timeout);
      result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    }
#endif
  }

  return result;
}

int I3CBus::readRegBuffer(uint8_t dynAddr,
                          uint8_t reg,
                          uint8_t *pData,
                          size_t len,
                          uint32_t timeout)
{
  int result = 0;

  if ((!_initialized) || (pData == nullptr) || (len == 0U) || (len > 32U)) {
    result = -1;
  } else {
#if defined(USE_HALV2_DRIVER)
    uint32_t               controlBuffer[2] = {};
    uint8_t                regBuf[1] = { reg };
    hal_i3c_transfer_ctx_t ctx {};
    hal_i3c_private_desc_t priv[] = {
      { dynAddr, 1U,                        HAL_I3C_DIRECTION_WRITE },
      { dynAddr, static_cast<uint32_t>(len), HAL_I3C_DIRECTION_READ  },
    };

    if ((HAL_I3C_CTRL_ResetTransferCtx(&ctx) == HAL_OK) &&
        (HAL_I3C_CTRL_InitTransferCtxTc(&ctx, controlBuffer, 2U) == HAL_OK) &&
        (HAL_I3C_CTRL_InitTransferCtxTx(&ctx, regBuf, 1U) == HAL_OK) &&
        (HAL_I3C_CTRL_InitTransferCtxRx(&ctx, pData, static_cast<uint32_t>(len)) == HAL_OK) &&
        (HAL_I3C_CTRL_BuildTransferCtxPrivate(&ctx,
                                              priv,
                                              COUNTOF(priv),
                                              I3C_PRIVATE_WITH_ARB_RESTART_V2) == HAL_OK)) {
      hal_status_t st = HAL_I3C_CTRL_Transfer(&_hi3c, &ctx, timeout);
      result = HAL_I3C_GetError(_hi3c, st);
    } else {
      result = -1;
    }
#else
    I3C_XferTypeDef    context {};
    I3C_PrivateTypeDef priv {};
    uint32_t           controlBuffer[1] = {};
    uint8_t            regBuf[1] = { reg };
    uint8_t            data[32]  = {0};
    HAL_StatusTypeDef  st;

    priv.TargetAddr    = dynAddr;
    priv.TxBuf.pBuffer = regBuf;
    priv.TxBuf.Size    = 1U;
    priv.RxBuf.pBuffer = nullptr;
    priv.RxBuf.Size    = 0U;
    priv.Direction     = HAL_I3C_DIRECTION_WRITE;

    std::memset(&context, 0, sizeof(context));
    context.CtrlBuf.pBuffer = controlBuffer;
    context.CtrlBuf.Size    = 1U;
    context.TxBuf.pBuffer   = regBuf;
    context.TxBuf.Size      = 1U;

    st = HAL_I3C_AddDescToFrame(
           &_hi3c,
           nullptr,
           &priv,
           &context,
           context.CtrlBuf.Size,
           I3C_PRIVATE_WITH_ARB_RESTART);

    if (st != HAL_OK) {
      result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    } else {
      st = HAL_I3C_Ctrl_Transmit(&_hi3c, &context, timeout);
      if (st != HAL_OK) {
        result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
      } else {
        priv.TargetAddr    = dynAddr;
        priv.TxBuf.pBuffer = nullptr;
        priv.TxBuf.Size    = 0U;
        priv.RxBuf.pBuffer = data;
        priv.RxBuf.Size    = static_cast<uint32_t>(len);
        priv.Direction     = HAL_I3C_DIRECTION_READ;

        std::memset(&context, 0, sizeof(context));
        context.CtrlBuf.pBuffer = controlBuffer;
        context.CtrlBuf.Size    = 1U;
        context.RxBuf.pBuffer   = data;
        context.RxBuf.Size      = static_cast<uint32_t>(len);

        st = HAL_I3C_AddDescToFrame(
               &_hi3c,
               nullptr,
               &priv,
               &context,
               context.CtrlBuf.Size,
               I3C_PRIVATE_WITH_ARB_STOP);

        if (st != HAL_OK) {
          result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
        } else {
          st = HAL_I3C_Ctrl_Receive(&_hi3c, &context, timeout);
          if (st != HAL_OK) {
            result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
          } else {
            memcpy(pData, data, len);
            result = 0;
          }
        }
      }
    }
#endif
  }

  return result;
}

int I3CBus::writeReg(uint8_t dynAddr,
                     uint8_t reg,
                     uint8_t value,
                     uint32_t timeout)
{
  return writeRegBuffer(dynAddr, reg, &value, 1U, timeout);
}

int I3CBus::readReg(uint8_t dynAddr,
                    uint8_t reg,
                    uint8_t &value,
                    uint32_t timeout)
{
  return readRegBuffer(dynAddr, reg, &value, 1U, timeout);
}

// ============================================================================
// Device readiness helpers
// ============================================================================

bool I3CBus::isI2CDeviceReady(uint8_t addr, uint32_t trials, uint32_t timeout)
{
  bool result = false;
  if (_initialized) {
#if defined(USE_HALV2_DRIVER)
    for (uint32_t i = 0U; i < trials; ++i) {
      if (HAL_I3C_CTRL_PoolForDeviceI2cReady(&_hi3c, addr, timeout) == HAL_OK) {
        result = true;
        break;
      }
    }
#else
    result = (HAL_I3C_Ctrl_IsDeviceI2C_Ready(&_hi3c, addr, trials, timeout) == HAL_OK);
#endif
  }
  return result;
}

bool I3CBus::isI3CDeviceReady(uint8_t dynAddr, uint32_t trials, uint32_t timeout)
{
  bool result = false;
  if (_initialized) {
#if defined(USE_HALV2_DRIVER)
    for (uint32_t i = 0U; i < trials; ++i) {
      if (HAL_I3C_CTRL_PoolForDeviceI3cReady(&_hi3c, dynAddr, timeout) == HAL_OK) {
        result = true;
        break;
      }
    }
#else
    result = (HAL_I3C_Ctrl_IsDeviceI3C_Ready(&_hi3c, dynAddr, trials, timeout) == HAL_OK);
#endif
  }
  return result;
}


// ============================================================================
// Low-level CCC helpers
// ============================================================================

bool I3CBus::cccBroadcastWrite(uint8_t cccId,
                               const uint8_t *data,
                               uint16_t length,
                               bool withDefByte,
                               uint32_t timeout)
{
  bool result = false;

  if (_initialized) {
#if defined(USE_HALV2_DRIVER)
    uint32_t txControlBuffer[1] = {};
    hal_i3c_transfer_ctx_t ctx {};
    hal_i3c_ccc_desc_t ccc[] = {
      { 0x7EU, cccId, length, HAL_I3C_DIRECTION_WRITE },
    };

    if (length <= I3C_CCC_TX_SCRATCH_MAX) {
      hal_i3c_transfer_mode_t mode = withDefByte
                                     ? HAL_I3C_CCC_BROADCAST_WITH_DEFBYTE_RESTART
                                     : HAL_I3C_CCC_BROADCAST_WITHOUT_DEFBYTE_RESTART;

      result = (HAL_I3C_CTRL_ResetTransferCtx(&ctx) == HAL_OK);

      if (result) {
        result = (HAL_I3C_CTRL_InitTransferCtxTc(&ctx, txControlBuffer, 1U) == HAL_OK);
      }

      if (result && (length != 0U)) {
        result = (HAL_I3C_CTRL_InitTransferCtxTx(&ctx, data, length) == HAL_OK);
      }

      if (result) {
        result = (HAL_I3C_CTRL_BuildTransferCtxCCC(&ctx, ccc, COUNTOF(ccc), mode) == HAL_OK);
      }

      if (result) {
        result = (HAL_I3C_CTRL_Transfer(&_hi3c, &ctx, timeout) == HAL_OK);

        if (!result) {
          uint32_t err = LL_I3C_GetRegister_SER(_instance);
          if ((err & HAL_I3C_CTRL_ERROR_2) == HAL_I3C_CTRL_ERROR_2) {
            result = true;
          }
        }
      }
    }

#else
    uint32_t        controlBuffer[1] = {};
    uint8_t         txBuffer[I3C_CCC_TX_SCRATCH_MAX] = {};
    I3C_XferTypeDef context {};

    I3C_CCCTypeDef ccc[] = {
      { 0x00U, cccId, { const_cast<uint8_t *>(data), length }, HAL_I3C_DIRECTION_WRITE },
    };

    if (!(length > sizeof(txBuffer))) {
      context.CtrlBuf.pBuffer = controlBuffer;
      context.CtrlBuf.Size    = 1U;
      context.TxBuf.pBuffer   = txBuffer;
      context.TxBuf.Size      = length;

      uint32_t option = withDefByte ? I3C_BROADCAST_WITH_DEFBYTE_RESTART
                        : I3C_BROADCAST_WITHOUT_DEFBYTE_RESTART;

      result = (HAL_I3C_AddDescToFrame(
                  &_hi3c,
                  ccc,
                  nullptr,
                  &context,
                  COUNTOF(ccc),
                  option) == HAL_OK);

      if (result) {
        result = (HAL_I3C_Ctrl_TransmitCCC(&_hi3c, &context, timeout) == HAL_OK);
        if (!result) {
          uint32_t err = HAL_I3C_GetError(&_hi3c);
          if ((err & HAL_I3C_ERROR_CE2) != 0U) {
            result = true;
          }
        }
      }
    }
#endif
  }

  return result;
}

bool I3CBus::cccDirectWrite(uint8_t targetAddr,
                            uint8_t cccId,
                            const uint8_t *data,
                            uint16_t length,
                            bool withDefByte,
                            uint32_t timeout)
{
  bool result = false;

  if (_initialized) {
#if defined(USE_HALV2_DRIVER)
    uint32_t txControlBuffer[2] = {};
    hal_i3c_transfer_ctx_t ctx {};
    hal_i3c_ccc_desc_t ccc[] = {
      {
        static_cast<uint8_t>(targetAddr & 0x7FU),
        cccId,
        length,
        HAL_I3C_DIRECTION_WRITE
      },
    };

    if (length <= I3C_CCC_TX_SCRATCH_MAX) {
      hal_i3c_transfer_mode_t mode = withDefByte
                                     ? HAL_I3C_CCC_DIRECT_WITH_DEFBYTE_RESTART
                                     : HAL_I3C_CCC_DIRECT_WITHOUT_DEFBYTE_RESTART;

      result = (HAL_I3C_CTRL_ResetTransferCtx(&ctx) == HAL_OK);

      if (result) {
        result = (HAL_I3C_CTRL_InitTransferCtxTc(&ctx, txControlBuffer, 2U) == HAL_OK);
      }

      if (result && (length != 0U)) {
        result = (HAL_I3C_CTRL_InitTransferCtxTx(&ctx, data, length) == HAL_OK);
      }

      if (result) {
        result = (HAL_I3C_CTRL_BuildTransferCtxCCC(&ctx, ccc, COUNTOF(ccc), mode) == HAL_OK);
      }

      if (result) {
        result = (HAL_I3C_CTRL_Transfer(&_hi3c, &ctx, timeout) == HAL_OK);
      }
    }

#else
    uint32_t        controlBuffer[2] = {};
    uint8_t         txBuffer[I3C_CCC_TX_SCRATCH_MAX] = {};
    I3C_XferTypeDef context {};

    I3C_CCCTypeDef ccc[] = {
      {
        static_cast<uint8_t>(targetAddr & 0x7FU),
        cccId,
        { const_cast<uint8_t *>(data), length },
        HAL_I3C_DIRECTION_WRITE
      },
    };

    if (!(length > sizeof(txBuffer))) {

      context.CtrlBuf.pBuffer = controlBuffer;
      context.CtrlBuf.Size    = 2U;
      context.TxBuf.pBuffer   = txBuffer;
      context.TxBuf.Size      = length;

      uint32_t option = withDefByte ? I3C_DIRECT_WITH_DEFBYTE_RESTART
                        : I3C_DIRECT_WITHOUT_DEFBYTE_RESTART;

      result = (HAL_I3C_AddDescToFrame(
                  &_hi3c,
                  ccc,
                  nullptr,
                  &context,
                  COUNTOF(ccc),
                  option) == HAL_OK);

      if (result) {
        result = (HAL_I3C_Ctrl_TransmitCCC(&_hi3c, &context, timeout) == HAL_OK);
      }
    }
#endif
  }

  return result;
}

bool I3CBus::cccDirectRead(uint8_t targetAddr,
                           uint8_t cccId,
                           uint8_t *rxData,
                           uint16_t rxLength,
                           uint32_t timeout)
{
  bool result = false;

  if (_initialized && (rxData != nullptr) && (rxLength != 0U)) {
#if defined(USE_HALV2_DRIVER)
    uint32_t rxControlBuffer[2] = {};
    hal_i3c_transfer_ctx_t ctx {};
    hal_i3c_ccc_desc_t ccc[] = {
      {
        static_cast<uint8_t>(targetAddr & 0x7FU),
        cccId,
        rxLength,
        HAL_I3C_DIRECTION_READ
      },
    };

    result = (HAL_I3C_CTRL_ResetTransferCtx(&ctx) == HAL_OK);

    if (result) {
      result = (HAL_I3C_CTRL_InitTransferCtxTc(&ctx, rxControlBuffer, 2U) == HAL_OK);
    }

    if (result) {
      result = (HAL_I3C_CTRL_InitTransferCtxRx(&ctx, rxData, rxLength) == HAL_OK);
    }

    if (result) {
      result = (HAL_I3C_CTRL_BuildTransferCtxCCC(&ctx,
                                                 ccc,
                                                 COUNTOF(ccc),
                                                 HAL_I3C_CCC_DIRECT_WITHOUT_DEFBYTE_RESTART) == HAL_OK);
    }

    if (result) {
      result = (HAL_I3C_CTRL_Transfer(&_hi3c, &ctx, timeout) == HAL_OK);
    }

#else
    uint32_t        controlBuffer[2] = {};
    I3C_XferTypeDef context {};

    I3C_CCCTypeDef ccc[] = {
      {
        static_cast<uint8_t>(targetAddr & 0x7FU),
        cccId,
        { nullptr, rxLength },
        HAL_I3C_DIRECTION_READ
      },
    };

    context.CtrlBuf.pBuffer = controlBuffer;
    context.CtrlBuf.Size    = 2U;
    context.RxBuf.pBuffer   = rxData;
    context.RxBuf.Size      = rxLength;

    result = (HAL_I3C_AddDescToFrame(
                &_hi3c,
                ccc,
                nullptr,
                &context,
                COUNTOF(ccc),
                I3C_DIRECT_WITHOUT_DEFBYTE_RESTART) == HAL_OK);

    if (result) {
      result = (HAL_I3C_Ctrl_ReceiveCCC(&_hi3c, &context, timeout) == HAL_OK);
    }
#endif
  }

  return result;
}

// ============================================================================
// CCC direct-read helpers
// ============================================================================

bool I3CBus::getbcr(uint8_t dynAddr, uint8_t &bcr, uint32_t timeout)
{
  bool result = false;
  uint8_t rxData[1] = {0};

  result = cccDirectRead(dynAddr, I3C_CCC_GETBCR_DIR, rxData, 1U, timeout);
  if (result) {
    bcr = rxData[0];
  }
  return result;
}

bool I3CBus::getdcr(uint8_t dynAddr, uint8_t &dcr, uint32_t timeout)
{
  bool result = false;
  uint8_t rxData[1] = {0};

  result = cccDirectRead(dynAddr, I3C_CCC_GETDCR_DIR, rxData, 1U, timeout);
  if (result) {
    dcr = rxData[0];
  }

  return result;
}

bool I3CBus::getpid(uint8_t dynAddr, uint64_t &pid, uint32_t timeout)
{
  bool result = false;
  uint8_t rxData[6] = {0};

  result = cccDirectRead(dynAddr, I3C_CCC_GETPID_DIR, rxData, 6U, timeout);
  if (result) {
    pid = 0ULL;
    pid |= (uint64_t)rxData[0] << 40;
    pid |= (uint64_t)rxData[1] << 32;
    pid |= (uint64_t)rxData[2] << 24;
    pid |= (uint64_t)rxData[3] << 16;
    pid |= (uint64_t)rxData[4] << 8;
    pid |= (uint64_t)rxData[5];
  }

  return result;
}

// ============================================================================
// 9. High-level CCC commands
// ============================================================================

bool I3CBus::resetDynamicAddresses()
{
  return cccBroadcastWrite(I3C_CCC_RSTDAA_BCAST, nullptr, 0U, false, 1000U);
}

bool I3CBus::disableEvents(const uint8_t *pCCCData, uint16_t length)
{
  return cccBroadcastWrite(I3C_CCC_DISEC_BCAST, pCCCData, length, length > 0U, 1000U);
}

bool I3CBus::assignAllStaticAsDynamic()
{
  return cccBroadcastWrite(I3C_CCC_SETAASA_BCAST, nullptr, 0U, false, 1000U);
}

bool I3CBus::assignDynamicAddress(uint8_t staticAddr7, uint8_t dynAddr7)
{
  bool result = false;

  if (_initialized) {
    uint8_t daByte = static_cast<uint8_t>((dynAddr7 & 0x7FU) << 1);
    result = cccDirectWrite(staticAddr7, I3C_CCC_SETDASA_DIR, &daByte, 1U, false, 1000U);
  }

  return result;
}

bool I3CBus::disecAll()
{
  const uint8_t evAll = I3C_CCC_EVT_ALL;
  return disableEvents(&evAll, 1U);
}

bool I3CBus::rstactWholeTarget()
{
  bool result = false;

  if (_initialized) {
    uint8_t defByte = I3C_CCC_RSTACT_RESET_WHOLE_TARGET;

#if defined(USE_HALV2_DRIVER)
    if (HAL_I3C_CTRL_EnableResetPattern(&_hi3c) == HAL_OK) {
      result = cccBroadcastWrite(I3C_CCC_RSTACT_BCAST, &defByte, 1U, true, 1000U);
      (void)HAL_I3C_CTRL_DisableResetPattern(&_hi3c);
    }
#else
    if (HAL_I3C_Ctrl_SetConfigResetPattern(&_hi3c, HAL_I3C_RESET_PATTERN_ENABLE) == HAL_OK) {
      result = cccBroadcastWrite(I3C_CCC_RSTACT_BCAST, &defByte, 1U, true, 1000U);
      (void)HAL_I3C_Ctrl_SetConfigResetPattern(&_hi3c, HAL_I3C_RESET_PATTERN_DISABLE);
    }
#endif
  }

  return result;
}

bool I3CBus::rstactPeripheralOnly()
{
  bool result = false;

  if (_initialized) {
    uint8_t defByte = I3C_CCC_RSTACT_PERIPHERAL_ONLY;

#if defined(USE_HALV2_DRIVER)
    if (HAL_I3C_CTRL_EnableResetPattern(&_hi3c) == HAL_OK) {
      result = cccBroadcastWrite(I3C_CCC_RSTACT_BCAST, &defByte, 1U, true, 1000U);
      (void)HAL_I3C_CTRL_DisableResetPattern(&_hi3c);
    }
#else
    if (HAL_I3C_Ctrl_SetConfigResetPattern(&_hi3c, HAL_I3C_RESET_PATTERN_ENABLE) == HAL_OK) {
      result = cccBroadcastWrite(I3C_CCC_RSTACT_BCAST, &defByte, 1U, true, 1000U);
      (void)HAL_I3C_Ctrl_SetConfigResetPattern(&_hi3c, HAL_I3C_RESET_PATTERN_DISABLE);
    }
#endif
  }

  return result;
}

bool I3CBus::setEvents(uint8_t dynAddr,
                       bool enable,
                       uint8_t events,
                       uint32_t timeout)
{
  bool result = false;

#if defined(USE_HALV2_DRIVER)
  if (_initialized && (_hi3c.mode == HAL_I3C_MODE_CTRL)) {
#else
  if (_initialized && (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER)) {
#endif
    uint8_t ev    = events;
    uint8_t cccId = enable ? I3C_CCC_ENEC_DIR : I3C_CCC_DISEC_DIR;
    result = cccDirectWrite(dynAddr, cccId, &ev, 1U, false, timeout);
  }

  return result;
}

bool I3CBus::enecHotJoin()
{
  uint8_t evHj = I3C_CCC_EVT_HJ;
  return cccBroadcastWrite(I3C_CCC_ENEC_BCAST, &evHj, 1U, true, 1000U);
}

// ============================================================================
// Address map helpers
// ============================================================================

void I3CBus::initAddressMap()
{
  for (auto &s : _addrMap) {
    s = I3CAddrState::Free;
  }

  _addrMap[0x00] = I3CAddrState::Reserved;
  _addrMap[0x7E] = I3CAddrState::Reserved;
  _addrMap[0x7F] = I3CAddrState::Reserved;
}

bool I3CBus::isValidUsableDynamicAddr(uint8_t addr) const
{
  return (((addr != 0U) && (addr < 0x7EU)) && (addr & 0x01U) == 0U);
}

bool I3CBus::isAddrFree(uint8_t addr) const
{
  return (addr < 128U) && (_addrMap[addr] == I3CAddrState::Free);
}

void I3CBus::markAddrUsed(uint8_t addr)
{
  if (addr < 128U) {
    _addrMap[addr] = I3CAddrState::I3CDevice;
  }
}

void I3CBus::markAddrFree(uint8_t addr)
{
  if ((addr < 128U) && (addr != 0x00U) && (addr != 0x7EU) && (addr != 0x7FU)) {
    _addrMap[addr] = I3CAddrState::Free;
  }
}


uint8_t I3CBus::allocNextDynamicAddr(uint8_t start) const
{
  uint8_t result = 0U;
  uint8_t a = (start < 0x08U) ? 0x08U : start;

  if ((a & 1U) != 0U) {
    ++a;
  }

  for (; a < 0x7E; a = static_cast<uint8_t>(a + 2U)) {
    if (isValidUsableDynamicAddr(a) && isAddrFree(a)) {
      result = a;
      break;
    }
  }

  return result;
}

// ============================================================================
// 11. Discovery and address assignment flow
// ============================================================================
int I3CBus::assignDynamicAddresses(I3CDiscoveredDevice *devices,
                                   size_t maxDevices,
                                   uint8_t firstDynAddr,
                                   uint32_t timeout)
{
  int result = -1;

  if ((!_initialized) || (devices == nullptr) || (maxDevices == 0U)) {
    result = -1;
  } else {
    uint64_t entdaaPayload = 0ULL;
    size_t   count = 0U;
    bool     stop = false;

    uint8_t nextDynAddr = (firstDynAddr != 0U) ? firstDynAddr : 0x10U;

#if defined(USE_HALV2_DRIVER)

    do {
      entdaaPayload = 0ULL;

      hal_i3c_dyn_addr_opt_t dynOpt = (count == 0U)
                                      ? HAL_I3C_DYN_ADDR_RSTDAA_THEN_ENTDAA
                                      : HAL_I3C_DYN_ADDR_ONLY_ENTDAA;

      hal_i3c_target_detection_status_t detected = HAL_I3C_TGT_NOT_DETECTED;
      hal_status_t st = HAL_I3C_CTRL_DynAddrAssign(&_hi3c,
                                                   &entdaaPayload,
                                                   dynOpt,
                                                   &detected,
                                                   timeout);

      if (st != HAL_OK) {
        result = -1;
        stop   = true;
      } else if (detected == HAL_I3C_TGT_DETECTED) {
        if (count >= maxDevices) {
          result = -2;
          stop   = true;
        } else {
          uint8_t da = nextDynAddr;
          nextDynAddr = static_cast<uint8_t>(nextDynAddr + 2U);

          if (HAL_I3C_CTRL_SetDynAddr(&_hi3c, da) != HAL_OK) {
            result = -3;
            stop   = true;
          } else {
            markAddrUsed(da);
            devices[count].dynAddr = da;
            count++;
          }
        }
      } else {
        result = static_cast<int>(count);
        stop   = true;
      }
    } while (!stop);

#else

    HAL_StatusTypeDef st = HAL_OK;

    do {
      entdaaPayload = 0ULL;

      uint32_t dynOpt = (count == 0U) ? I3C_RSTDAA_THEN_ENTDAA : I3C_ONLY_ENTDAA;

      st = HAL_I3C_Ctrl_DynAddrAssign(&_hi3c, &entdaaPayload, dynOpt, timeout);

      if (st == HAL_BUSY) {
        if (count >= maxDevices) {
          result = -2;
          stop   = true;
        } else {
          uint8_t da = nextDynAddr;
          nextDynAddr = static_cast<uint8_t>(nextDynAddr + 2U);

          if (HAL_I3C_Ctrl_SetDynAddr(&_hi3c, da) != HAL_OK) {
            result = -3;
            stop   = true;
          } else {
            markAddrUsed(da);
            devices[count].dynAddr = da;
            count++;
          }
        }
      } else if (st != HAL_OK) {
        result = -static_cast<int>(HAL_I3C_GetError(&_hi3c));
        stop   = true;
      }
    } while ((st == HAL_BUSY) && (!stop));

    if ((!stop) && (st == HAL_OK)) {
      result = static_cast<int>(count);
    }

#endif
  }

  return result;
}

int I3CBus::assignKnownDevices(const I3CKnownDevice *knownDevices,
                               size_t numKnownDevices,
                               I3CDiscoveredDevice *discovered,
                               size_t maxDiscovered,
                               size_t &count,
                               bool &needAasa,
                               bool &needDaa)
{
  int result = 0;

  needAasa = false;
  needDaa  = false;

  if ((knownDevices == nullptr) || (numKnownDevices == 0U)) {
    needDaa = true;
  } else {
    for (size_t i = 0; i < numKnownDevices; ++i) {
      const auto &kd = knownDevices[i];

      if (!kd.present) {
        continue;
      }

      if (kd.staticAddr == 0U) {
        needDaa = true;
        continue;
      }

      if (kd.supportsSetaasa &&
          ((kd.preferredDynAddr == 0U) || (kd.preferredDynAddr == kd.staticAddr))) {
        needAasa = true;
        continue;
      }

      uint8_t dyn = kd.preferredDynAddr ? kd.preferredDynAddr : kd.staticAddr;

      if (!isValidUsableDynamicAddr(dyn) || !isAddrFree(dyn)) {
        continue;
      }

      if (assignDynamicAddress(kd.staticAddr, dyn)) {
        markAddrUsed(dyn);

        if (count < maxDiscovered) {
          auto &d = discovered[count++];
          d.dynAddr           = dyn;
          d.staticAddr        = kd.staticAddr;
          d.assignedBySetdasa = true;
          d.fromDaa           = false;
          d.matchedKnown      = true;
          d.entdaaPayloadRaw  = 0U;
          d.pid               = kd.pid;

          uint8_t  bcr = 0U;
          uint8_t  dcr = 0U;
          uint64_t pid = 0ULL;

          if (getbcr(dyn, bcr)) {
            d.bcr = bcr;
          }

          if (getdcr(dyn, dcr)) {
            d.dcr = dcr;
          }

          if ((d.pid == 0U) && (getpid(dyn, pid))) {
            d.pid = pid;
          }
        }
      }
    }
  }

  return result;
}

int I3CBus::doDaaPhase(const I3CBusBeginConfig &cfg,
                       const I3CKnownDevice *knownDevices,
                       size_t numKnownDevices,
                       I3CDiscoveredDevice *discovered,
                       size_t maxDiscovered,
                       size_t &count)
{
  int  result = 0;
  bool done = false;

  uint64_t payload = 0ULL;
  uint8_t nextAddr = cfg.firstAutoDynAddr ? cfg.firstAutoDynAddr : 0x10U;

  while (!done) {
    payload = 0ULL;

#if defined(USE_HALV2_DRIVER)

    hal_i3c_target_detection_status_t detected = HAL_I3C_TGT_NOT_DETECTED;
    hal_status_t st = HAL_I3C_CTRL_DynAddrAssign(&_hi3c,
                                                 &payload,
                                                 HAL_I3C_DYN_ADDR_ONLY_ENTDAA,
                                                 &detected,
                                                 1000U);

    if (st != HAL_OK) {
      result = -1;
      done   = true;
    } else if (detected == HAL_I3C_TGT_NOT_DETECTED) {
      result = 0;
      done   = true;
    } else {
      hal_i3c_entdaa_payload_t info {};
      if (HAL_I3C_CTRL_GetENTDAA_PayloadInfo(payload, &info) != HAL_OK) {
        result = -2;
        done   = true;
      } else {
        uint64_t pid48 = extractPid48FromEntdaaPayload(payload);

        uint8_t chosen = 0U;

        if (knownDevices != nullptr) {
          for (size_t i = 0; i < numKnownDevices; ++i) {
            const auto &kd = knownDevices[i];

            if (!kd.present || (kd.pid == 0U)) {
              continue;
            }

            if (kd.pid == pid48) {
              uint8_t pref = kd.preferredDynAddr;
              if ((pref != 0U) && isValidUsableDynamicAddr(pref) && isAddrFree(pref)) {
                chosen = pref;
              }
              break;
            }
          }
        }

        if (chosen == 0U) {
          chosen = allocNextDynamicAddr(nextAddr);
          if (chosen == 0U) {
            result = -3;
            done   = true;
          }
        }

        if (!done) {
          if (HAL_I3C_CTRL_SetDynAddr(&_hi3c, chosen) != HAL_OK) {
            result = -4;
            done   = true;
          } else {
            markAddrUsed(chosen);

            if (count < maxDiscovered) {
              auto &d = discovered[count++];
              d.dynAddr          = chosen;
              d.staticAddr       = 0U;
              d.bcr              = reconstructBcr(info.bcr);
              d.dcr              = static_cast<uint8_t>(info.dcr);
              d.pid              = pid48;
              d.entdaaPayloadRaw = payload;
              d.fromDaa          = true;
              d.matchedKnown     = false;
            }

            nextAddr = static_cast<uint8_t>(chosen + 2U);
          }
        }
      }
    }

#else

    HAL_StatusTypeDef st = HAL_I3C_Ctrl_DynAddrAssign(&_hi3c, &payload, I3C_ONLY_ENTDAA, 1000U);

    if (st == HAL_OK) {
      result = 0;
      done   = true;
    } else if (st != HAL_BUSY) {
      result = -1;
      done   = true;
    } else {
      I3C_ENTDAAPayloadTypeDef info {};
      if (HAL_I3C_Get_ENTDAA_Payload_Info(&_hi3c, payload, &info) != HAL_OK) {
        result = -2;
        done   = true;
      } else {
        uint64_t pid48 = extractPid48FromEntdaaPayload(payload);

        uint8_t chosen = 0U;

        if (knownDevices != nullptr) {
          for (size_t i = 0; i < numKnownDevices; ++i) {
            const auto &kd = knownDevices[i];

            if (!kd.present || (kd.pid == 0U)) {
              continue;
            }

            if (kd.pid == pid48) {
              uint8_t pref = kd.preferredDynAddr;
              if ((pref != 0U) && isValidUsableDynamicAddr(pref) && isAddrFree(pref)) {
                chosen = pref;
              }
              break;
            }
          }
        }

        if (chosen == 0U) {
          chosen = allocNextDynamicAddr(nextAddr);
          if (chosen == 0U) {
            result = -3;
            done   = true;
          }
        }

        if (!done) {
          if (HAL_I3C_Ctrl_SetDynAddr(&_hi3c, chosen) != HAL_OK) {
            result = -4;
            done   = true;
          } else {
            markAddrUsed(chosen);

            if (count < maxDiscovered) {
              auto &d = discovered[count++];
              d.dynAddr          = chosen;
              d.staticAddr       = 0U;
              d.bcr              = reconstructBcr(info.BCR);
              d.dcr              = info.DCR;
              d.pid              = pid48;
              d.entdaaPayloadRaw = payload;
              d.fromDaa          = true;
              d.matchedKnown     = false;
            }

            nextAddr = static_cast<uint8_t>(chosen + 2U);
          }
        }
      }
    }

#endif
  }

  return result;
}



int I3CBus::configBusDevicesFromDiscovery(const I3CDiscoveredDevice *discovered, size_t count)
{
  int result = 0;

  if ((discovered != nullptr) && (count != 0U)) {
    uint8_t n = 0U;

#if defined(USE_HALV2_DRIVER)

    hal_i3c_ctrl_device_config_t desc[4] {};

    for (size_t i = 0; (i < count) && (n < 4U); ++i) {
      desc[n].device_index       = n;
      desc[n].tgt_dynamic_addr   = discovered[i].dynAddr;
      desc[n].ibi_ack            = HAL_I3C_CTRL_IBI_ACK_DISABLED;
      desc[n].ctrl_role_req_ack  = HAL_I3C_CTRL_ROLE_ACK_DISABLED;
      desc[n].ctrl_stop_transfer = HAL_I3C_CTRL_STOP_TRANSFER_DISABLED;
      desc[n].ibi_payload        = HAL_I3C_CTRL_IBI_PAYLOAD_DISABLED;
      ++n;
    }

    if (n != 0U) {
      result = (HAL_I3C_CTRL_SetConfigBusDevices(&_hi3c, desc, n) == HAL_OK) ? 0 : -1;
    }

#else

    I3C_DeviceConfTypeDef desc[4] {};

    for (size_t i = 0; (i < count) && (n < 4U); ++i) {
      desc[n].DeviceIndex       = static_cast<uint8_t>(n + 1U);
      desc[n].TargetDynamicAddr = discovered[i].dynAddr;
      desc[n].IBIAck            = DISABLE;
      desc[n].CtrlRoleReqAck    = DISABLE;
      desc[n].CtrlStopTransfer  = DISABLE;
      desc[n].IBIPayload        = DISABLE;
      ++n;
    }

    if (n != 0U) {
      result = (HAL_I3C_Ctrl_ConfigBusDevices(&_hi3c, desc, n) == HAL_OK) ? 0 : -1;
    }

#endif
  }

  return result;
}
/////////////////////////////////
int I3CBus::discover(const I3CBusBeginConfig &cfg,
                     const I3CKnownDevice *knownDevices,
                     size_t numKnownDevices,
                     I3CDiscoveredDevice *discovered,
                     size_t maxDiscovered,
                     size_t *outCount)
{
  int result = -1;

  if (_initialized && (discovered != nullptr) && (outCount != nullptr)) {
    size_t count = 0U;
    bool   needAasa = false;
    bool   needDaa  = false;

    result    = 0;
    *outCount = 0U;

    initAddressMap();

    if (cfg.doRstact) {
      if (!rstactWholeTarget()) {
        (void)rstactPeripheralOnly();
      }
    }

    if (cfg.doRstdaa) {
      (void)resetDynamicAddresses();
    }

    if (cfg.disableEvents) {
      (void)disecAll();
    }

    if (cfg.doSetdasa) {
      int rc = assignKnownDevices(knownDevices,
                                  numKnownDevices,
                                  discovered,
                                  maxDiscovered,
                                  count,
                                  needAasa,
                                  needDaa);
      if (rc != 0) {
        result = rc;
      }
    } else {
      needDaa = true;
    }

    if (result == 0) {
      if (cfg.discoverUnknownAfterKnown) {
        needDaa = true;
      }

      if (needAasa) {
        (void)assignAllStaticAsDynamic();

        if (knownDevices != nullptr) {
          for (size_t i = 0U; i < numKnownDevices; ++i) {
            const auto &kd = knownDevices[i];

            if (!kd.present || (kd.staticAddr == 0U)) {
              continue;
            }

            if (!(kd.supportsSetaasa &&
                  ((kd.preferredDynAddr == 0U) || (kd.preferredDynAddr == kd.staticAddr)))) {
              continue;
            }

            uint8_t dyn = kd.staticAddr;

            if (!isValidUsableDynamicAddr(dyn) || !isAddrFree(dyn)) {
              continue;
            }

            markAddrUsed(dyn);

            if (count < maxDiscovered) {
              auto &d = discovered[count++];
              d.dynAddr           = dyn;
              d.staticAddr        = kd.staticAddr;
              d.pid               = kd.pid;
              d.assignedBySetdasa = false;
              d.fromDaa           = false;
              d.matchedKnown      = true;
            }
          }
        }
      }

      if (((knownDevices == nullptr) || (numKnownDevices == 0U)) && cfg.doDaa) {
        needDaa = true;
      }

      if (cfg.doDaa && needDaa) {
        int rc = doDaaPhase(cfg, knownDevices, numKnownDevices, discovered, maxDiscovered, count);
        if ((rc != 0) && cfg.retryDaaOnce) {
          rc = doDaaPhase(cfg, knownDevices, numKnownDevices, discovered, maxDiscovered, count);
        }

        if (rc != 0) {
          result = rc;
        }
      }
    }

    if (result == 0) {
      (void)configBusDevicesFromDiscovery(discovered, count);

      if (cfg.allowHotJoinAfterInit) {
        (void)enecHotJoin();
      }
    }

    *outCount = count;
  }

  return result;
}

uint32_t I3CBus::bigToLittle32(uint32_t x)
{
  return (((x & 0xFF000000U) >> 24) |
          ((x & 0x00FF0000U) >> 8)  |
          ((x & 0x0000FF00U) << 8)  |
          ((x & 0x000000FFU) << 24));
}

uint64_t I3CBus::extractPid48FromEntdaaPayload(uint64_t payload)
{
  uint64_t pid = payload & 0xFFFFFFFFFFFFULL;

  pid = (uint64_t)((((uint64_t)bigToLittle32((uint32_t)pid) << 32) |
                    ((uint64_t)bigToLittle32((uint32_t)(pid >> 32)))) >> 16);

  return pid & 0xFFFFFFFFFFFFULL;
}

#if defined(USE_HALV2_DRIVER)
int I3CBus::HAL_I3C_GetError(const hal_i3c_handle_t &hi3c, hal_status_t st)
{
  int result = 0;

  if (st != HAL_OK) {
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
    result = -static_cast<int>(HAL_I3C_GetLastErrorCodes(&hi3c));
#else
    (void)hi3c;
    result = -1;
#endif
  }

  return result;
}
#endif

// ============================================================================
// Target-mode initialization
// ============================================================================

bool I3CBus::beginTarget(pin_size_t sda, pin_size_t scl, const I3CTargetConfig &cfg)
{
  _sdaPin = digitalPinToPinName(sda);
  _sclPin = digitalPinToPinName(scl);

  return beginTarget(cfg);
}

bool I3CBus::beginTarget(const I3CTargetConfig &cfg)
{
  bool result = false;

#if defined(USE_HALV2_DRIVER)

  if (_initialized) {
    if (_hi3c.mode == HAL_I3C_MODE_TGT) {
      result = (configureTarget(cfg) == 0);
    }
  } else {
    std::memset(&_hi3c, 0, sizeof(_hi3c));
    _instance = nullptr;

    if (prepareInstanceFromPins() && initClocks() && initGPIO()) {
      hal_i3c_t halInstance = HAL_I3C1;
      if (_instance == I3C1) {
        if (HAL_I3C_Init(&_hi3c, halInstance) != HAL_OK) {
          result = false;
        } else {
          hal_i3c_tgt_config_t tgtCfg {};

          if (buildTargetTiming(getPeripheralClockFreq(), tgtCfg) &&
              (HAL_I3C_TGT_SetConfig(&_hi3c, &tgtCfg) == HAL_OK)) {
            hal_i3c_tgt_fifo_config_t fifoCfg {};
            fifoCfg.rx_fifo_threshold = HAL_I3C_RX_FIFO_THRESHOLD_1_8;
            fifoCfg.tx_fifo_threshold = HAL_I3C_TX_FIFO_THRESHOLD_1_8;

            if (HAL_I3C_TGT_SetConfigFifo(&_hi3c, &fifoCfg) == HAL_OK) {
              if (configureTarget(cfg) == 0) {
                _initialized = true;
                _role = I3CRole::Target;
                registerInstanceOwner();
                result = true;
              }
            }
          }
        }

        if (!result) {
          unregisterInstanceOwner();
          HAL_I3C_DeInit(&_hi3c);
          _initialized = false;
          _role = I3CRole::None;
        }
      }
    }
  }

#else

  if (_initialized) {
    if (_hi3c.Mode == HAL_I3C_MODE_TARGET) {
      result = (configureTarget(cfg) == 0);
    }
  } else {
    _hi3c.Instance = nullptr;
    _instance = nullptr;

    if (prepareInstanceFromPins() && initClocks() && initGPIO()) {
      std::memset(&_hi3c, 0, sizeof(_hi3c));
      _hi3c.Instance = _instance;
      _hi3c.Mode     = HAL_I3C_MODE_TARGET;

      LL_I3C_TgtBusConfTypeDef outTgt {};

      if (buildTargetTiming(outTgt)) {
        _hi3c.Init.TgtBusCharacteristic = outTgt;
        if (HAL_I3C_Init(&_hi3c) == HAL_OK) {
          I3C_FifoConfTypeDef fifoCfg {};
          fifoCfg.RxFifoThreshold = HAL_I3C_RXFIFO_THRESHOLD_1_4;
          fifoCfg.TxFifoThreshold = HAL_I3C_TXFIFO_THRESHOLD_1_4;
          fifoCfg.ControlFifo     = HAL_I3C_CONTROLFIFO_DISABLE;
          fifoCfg.StatusFifo      = HAL_I3C_STATUSFIFO_DISABLE;

          if (HAL_I3C_SetConfigFifo(&_hi3c, &fifoCfg) == HAL_OK) {
            if (configureTarget(cfg) == 0) {
              _initialized = true;
              _role = I3CRole::Target;
              registerInstanceOwner();
              result = true;
            }
          }
          if (!result) {
            if (_hi3c.Instance != nullptr) {
              (void)HAL_I3C_DeInit(&_hi3c);
            }
            unregisterInstanceOwner();
            _initialized = false;
            _role = I3CRole::None;
          }
        }
      }
    }
  }

#endif

  return result;
}

int I3CBus::configureTarget(const I3CTargetConfig &cfg)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)

  if (_hi3c.mode == HAL_I3C_MODE_TGT) {
    hal_i3c_tgt_config_payload_entdaa_t entdaaCfg {};
    hal_i3c_tgt_ibi_config_t            ibiCfg {};
    hal_i3c_tgt_getmxds_config_t        getmxdsCfg {};
    hal_status_t                        st = HAL_OK;

    entdaaCfg.identifier = cfg.identifier;
    entdaaCfg.mipi_identifier = cfg.mipiIdentifier;
    entdaaCfg.ctrl_role = cfg.ctrlCapability ? HAL_I3C_CTRL_ROLE_ENABLED : HAL_I3C_CTRL_ROLE_DISABLED;
    entdaaCfg.ibi_payload = cfg.ibiPayload ? HAL_I3C_IBI_PAYLOAD_ENABLED : HAL_I3C_IBI_PAYLOAD_DISABLED;
    entdaaCfg.max_data_speed_limitation = cfg.maxSpeedLimitation ? HAL_I3C_MAX_SPEED_LIMITATION_ENABLED : HAL_I3C_MAX_SPEED_LIMITATION_DISABLED;

    ibiCfg.ibi_payload_size_byte = static_cast<hal_i3c_tgt_payload_size_t>(cfg.ibiPayloadSize);
    ibiCfg.pending_read_mdb = cfg.pendingReadMDB ? HAL_I3C_PENDING_READ_MDB_ENABLED : HAL_I3C_PENDING_READ_MDB_DISABLED;

    getmxdsCfg.getmxds_format = static_cast<hal_i3c_getmxds_format_t>(cfg.maxDataSpeed);
    getmxdsCfg.ctrl_handoff_activity = static_cast<hal_i3c_handoff_activity_state_t>(cfg.handOffActivityState);
    getmxdsCfg.data_turnaround_duration = static_cast<hal_i3c_turnaround_time_tsco_t>(cfg.dataTurnAroundDuration);
    getmxdsCfg.max_read_turnaround = cfg.maxReadTurnAround;

    st = HAL_I3C_TGT_SetPayloadENTDAAConfig(&_hi3c, &entdaaCfg);
    if (st == HAL_OK) {
      st = HAL_I3C_TGT_SetConfigIBI(&_hi3c, &ibiCfg);
    }
    if (st == HAL_OK) {
      st = HAL_I3C_TGT_SetConfigMaxDataSize(&_hi3c, cfg.maxReadDataSize, cfg.maxWriteDataSize);
    }
    if (st == HAL_OK) {
      st = HAL_I3C_TGT_SetConfigGETMXDS(&_hi3c, &getmxdsCfg);
    }
    if (st == HAL_OK) {
      st = cfg.ctrlRoleRequest ? HAL_I3C_TGT_EnableCtrlRoleRequest(&_hi3c) : HAL_I3C_TGT_DisableCtrlRoleRequest(&_hi3c);
    }
    if (st == HAL_OK) {
      st = cfg.hotJoinRequest ? HAL_I3C_TGT_EnableHotJoinRequest(&_hi3c) : HAL_I3C_TGT_DisableHotJoinRequest(&_hi3c);
    }
    if (st == HAL_OK) {
      st = cfg.ibiRequest ? HAL_I3C_TGT_EnableIBI(&_hi3c) : HAL_I3C_TGT_DisableIBI(&_hi3c);
    }
    if (st == HAL_OK) {
      st = cfg.groupAddrCapability ? HAL_I3C_TGT_EnableGroupAddrCapability(&_hi3c) : HAL_I3C_TGT_DisableGroupAddrCapability(&_hi3c);
    }
    if (st == HAL_OK) {
      st = cfg.handOffDelay ? HAL_I3C_TGT_EnableHandOffDelay(&_hi3c) : HAL_I3C_TGT_DisableHandOffDelay(&_hi3c);
    }
    result = HAL_I3C_GetError(_hi3c, st);
  }

#else

  if (_hi3c.Mode == HAL_I3C_MODE_TARGET) {
    I3C_TgtConfTypeDef tgtCfg {};

    tgtCfg.Identifier             = cfg.identifier;
    tgtCfg.MIPIIdentifier         = cfg.mipiIdentifier;
    tgtCfg.CtrlRoleRequest        = cfg.ctrlRoleRequest ? ENABLE : DISABLE;
    tgtCfg.HotJoinRequest         = cfg.hotJoinRequest ? ENABLE : DISABLE;
    tgtCfg.IBIRequest             = cfg.ibiRequest ? ENABLE : DISABLE;
    tgtCfg.IBIPayload             = cfg.ibiPayload ? ENABLE : DISABLE;
    tgtCfg.IBIPayloadSize         = cfg.ibiPayloadSize;
    tgtCfg.MaxReadDataSize        = cfg.maxReadDataSize;
    tgtCfg.MaxWriteDataSize       = cfg.maxWriteDataSize;
    tgtCfg.CtrlCapability         = cfg.ctrlCapability ? ENABLE : DISABLE;
    tgtCfg.GroupAddrCapability    = cfg.groupAddrCapability ? ENABLE : DISABLE;
    tgtCfg.DataTurnAroundDuration = cfg.dataTurnAroundDuration;
    tgtCfg.MaxReadTurnAround      = cfg.maxReadTurnAround;
    tgtCfg.MaxDataSpeed           = cfg.maxDataSpeed;
    tgtCfg.MaxSpeedLimitation     = cfg.maxSpeedLimitation ? ENABLE : DISABLE;
    tgtCfg.HandOffActivityState   = cfg.handOffActivityState;
    tgtCfg.HandOffDelay           = cfg.handOffDelay ? ENABLE : DISABLE;
    tgtCfg.PendingReadMDB         = cfg.pendingReadMDB ? ENABLE : DISABLE;

    HAL_StatusTypeDef st = HAL_I3C_Tgt_Config(&_hi3c, &tgtCfg);
    result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
  }

#endif

  return result;
}

bool I3CBus::hasAddress() const
{
  bool result = false;

  if (_initialized &&
#if defined(USE_HALV2_DRIVER)
      (_hi3c.mode == HAL_I3C_MODE_TGT) &&
#else
      (_hi3c.Mode == HAL_I3C_MODE_TARGET) &&
#endif
      (_instance != nullptr)) {
    result = (LL_I3C_IsEnabledOwnDynAddress(_instance) == 1U);
  }

  return result;
}

uint8_t I3CBus::address() const
{
  uint8_t result = 0U;

  if (hasAddress()) {
    result = LL_I3C_GetOwnDynamicAddress(_instance);
  }

  return result;
}

// ============================================================================
// Target-side private communication
// ============================================================================

int I3CBus::send(uint8_t *buf,
                 uint16_t len,
                 uint32_t timeout)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)
  if (_initialized &&
      (_hi3c.mode == HAL_I3C_MODE_TGT) &&
      (buf != nullptr) &&
      (len != 0U)) {
    hal_status_t st = HAL_I3C_TGT_Transmit(&_hi3c, buf, len, timeout);
    result = HAL_I3C_GetError(_hi3c, st);
  }
#else
  if (_initialized &&
      (_hi3c.Mode == HAL_I3C_MODE_TARGET) &&
      (buf != nullptr) &&
      (len != 0U)) {
    I3C_XferTypeDef xfer {};
    xfer.TxBuf.pBuffer = buf;
    xfer.TxBuf.Size    = len;

    HAL_StatusTypeDef st = HAL_I3C_Tgt_Transmit(&_hi3c, &xfer, timeout);
    result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
  }
#endif

  return result;
}

int I3CBus::receive(uint8_t *buf,
                    uint16_t len,
                    uint32_t timeout)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)
  if (_initialized &&
      (_hi3c.mode == HAL_I3C_MODE_TGT) &&
      (buf != nullptr) &&
      (len != 0U)) {
    hal_status_t st = HAL_I3C_TGT_Receive(&_hi3c, buf, len, timeout);
    result = HAL_I3C_GetError(_hi3c, st);
  }
#else
  if (_initialized &&
      (_hi3c.Mode == HAL_I3C_MODE_TARGET) &&
      (buf != nullptr) &&
      (len != 0U)) {
    I3C_XferTypeDef xfer {};
    xfer.RxBuf.pBuffer = buf;
    xfer.RxBuf.Size    = len;

    HAL_StatusTypeDef st = HAL_I3C_Tgt_Receive(&_hi3c, &xfer, timeout);
    result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
  }
#endif

  return result;
}

// ============================================================================
// Target-side requests and notifications
// ============================================================================

int I3CBus::sendIbi(const uint8_t *payload,
                    uint8_t payloadSize,
                    uint32_t timeout)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)
  if (_initialized && (_hi3c.mode == HAL_I3C_MODE_TGT)) {
    hal_status_t st = HAL_I3C_TGT_IBIReq(&_hi3c, payload, payloadSize, timeout);
    result = HAL_I3C_GetError(_hi3c, st);
  }
#else
  if (_initialized && (_hi3c.Mode == HAL_I3C_MODE_TARGET)) {
    HAL_StatusTypeDef st = HAL_I3C_Tgt_IBIReq(&_hi3c, payload, payloadSize, timeout);
    result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
  }
#endif

  return result;
}
int I3CBus::enableTargetEvents(const I3CTargetEventConfig &cfg,
                               uint32_t interruptMask)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)
  if (_initialized && (_hi3c.mode == HAL_I3C_MODE_TGT)) {
    enableIRQs();
    hal_status_t st = HAL_I3C_TGT_ActivateNotification(&_hi3c, cfg.rxData, cfg.rxSize, interruptMask);
    if (st != HAL_OK) {
      disableIRQs();
    }
    result = HAL_I3C_GetError(_hi3c, st);
  }
#else
  if (_initialized && (_hi3c.Mode == HAL_I3C_MODE_TARGET)) {
    I3C_XferTypeDef xfer {};
    I3C_DataTypeDef rxBuf {};

    rxBuf.pBuffer = cfg.rxData;
    rxBuf.Size    = cfg.rxSize;
    xfer.RxBuf    = rxBuf;

    enableIRQs();
    HAL_StatusTypeDef st = HAL_I3C_ActivateNotification(&_hi3c, &xfer, interruptMask);
    if (st != HAL_OK) {
      if (_hi3c.Instance->IER == 0U) {
        disableIRQs();
      }
    }
    result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
  }
#endif

  return result;
}

int I3CBus::disableTargetEvents(uint32_t interruptMask)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)
  if (_initialized && (_hi3c.mode == HAL_I3C_MODE_TGT)) {
    hal_status_t st = HAL_I3C_TGT_DeactivateNotification(&_hi3c, interruptMask);
    result = HAL_I3C_GetError(_hi3c, st);

    if ((st == HAL_OK) && (LL_I3C_GetEnabledIT(_instance) == 0U)) {
      disableIRQs();
    }
  }
#else
  if (_initialized && (_hi3c.Mode == HAL_I3C_MODE_TARGET)) {
    HAL_StatusTypeDef st = HAL_I3C_DeactivateNotification(&_hi3c, interruptMask);
    result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));

    if ((st == HAL_OK) && (_hi3c.Instance->IER == 0U)) {
      disableIRQs();
    }
  }
#endif

  return result;
}

bool I3CBus::hasTargetEvent() const
{
  return _targetEventPending;
}

bool I3CBus::readTargetEvent(uint32_t &eventId)
{
  bool result = false;

  if (_targetEventPending) {
    noInterrupts();
    eventId = _lastTargetEventId;
    _targetEventPending = false;
    interrupts();
    result = true;
  }

  return result;
}

bool I3CBus::getTargetCccInfo(uint32_t eventId, I3CTargetCccInfo &out)
{
  bool result = false;
  out = {};

#if defined(USE_HALV2_DRIVER)
  if (_initialized &&
      (_hi3c.mode == HAL_I3C_MODE_TGT) &&
      ((eventId & HAL_I3C_TGT_NOTIFICATION_ENEC_DISEC) != 0U)) {
    hal_i3c_ccc_info_t info {};

    if (HAL_I3C_GetCCCInfo(&_hi3c, HAL_I3C_TGT_NOTIFICATION_ENEC_DISEC, &info) == HAL_OK) {
      out.hotJoinAllowed = (info.hot_join_allowed != 0U);
      out.inBandAllowed  = (info.in_band_allowed != 0U);
      out.ctrlRoleAllowed = (info.ctrl_role_allowed != 0U);
      result = true;
    }
  }
#else
  if (_initialized &&
      (_hi3c.Mode == HAL_I3C_MODE_TARGET) &&
      ((eventId & EVENT_ID_ENEC_DISEC) != 0U)) {
    I3C_CCCInfoTypeDef info {};

    if (HAL_I3C_GetCCCInfo(&_hi3c, EVENT_ID_ENEC_DISEC, &info) == HAL_OK) {
      out.hotJoinAllowed  = (info.HotJoinAllowed != 0U);
      out.inBandAllowed   = (info.InBandAllowed != 0U);
      out.ctrlRoleAllowed = (info.CtrlRoleAllowed != 0U);
      result = true;
    }
  }
#endif

  return result;
}

// ============================================================================
// Controller-side IBI support
// ============================================================================

int I3CBus::configureControllerDevice(uint8_t deviceIndex,
                                      uint8_t dynAddr,
                                      bool ibiAck,
                                      bool ibiPayload,
                                      bool ctrlRoleReqAck,
                                      bool stopTransfer)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)
  if (_initialized && (_hi3c.mode == HAL_I3C_MODE_CTRL)) {
    if ((deviceIndex >= 1U) && (deviceIndex <= 4U)) {
      hal_i3c_ctrl_device_config_t desc {};

      desc.device_index       = static_cast<uint8_t>(deviceIndex - 1U);
      desc.tgt_dynamic_addr   = dynAddr;
      desc.ibi_ack            = ibiAck ? HAL_I3C_CTRL_IBI_ACK_ENABLED
                                : HAL_I3C_CTRL_IBI_ACK_DISABLED;
      desc.ibi_payload        = ibiPayload ? HAL_I3C_CTRL_IBI_PAYLOAD_ENABLED
                                : HAL_I3C_CTRL_IBI_PAYLOAD_DISABLED;
      desc.ctrl_role_req_ack  = ctrlRoleReqAck ? HAL_I3C_CTRL_ROLE_ACK_ENABLED
                                : HAL_I3C_CTRL_ROLE_ACK_DISABLED;
      desc.ctrl_stop_transfer = stopTransfer ? HAL_I3C_CTRL_STOP_TRANSFER_ENABLED
                                : HAL_I3C_CTRL_STOP_TRANSFER_DISABLED;

      hal_status_t st = HAL_I3C_CTRL_SetConfigBusDevices(&_hi3c, &desc, 1U);
      result = HAL_I3C_GetError(_hi3c, st);
    }
  }
#else
  if (_initialized && (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER)) {
    if ((deviceIndex >= 1U) && (deviceIndex <= 4U)) {
      I3C_DeviceConfTypeDef desc {};

      desc.DeviceIndex       = deviceIndex;
      desc.TargetDynamicAddr = dynAddr;
      desc.IBIAck            = ibiAck ? ENABLE : DISABLE;
      desc.IBIPayload        = ibiPayload ? ENABLE : DISABLE;
      desc.CtrlRoleReqAck    = ctrlRoleReqAck ? ENABLE : DISABLE;
      desc.CtrlStopTransfer  = stopTransfer ? ENABLE : DISABLE;

      HAL_StatusTypeDef st = HAL_I3C_Ctrl_ConfigBusDevices(&_hi3c, &desc, 1U);
      result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
    }
  }
#endif

  return result;
}

int I3CBus::enableIbi(uint8_t deviceIndex,
                      uint8_t dynAddr,
                      bool withPayload,
                      bool stopTransfer,
                      uint32_t timeout)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)
  if (_initialized && (_hi3c.mode == HAL_I3C_MODE_CTRL)) {
#else
  if (_initialized && (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER)) {
#endif
    result = configureControllerDevice(deviceIndex,
                                       dynAddr,
                                       true,
                                       withPayload,
                                       false,
                                       stopTransfer);

    if (result == 0) {
      result = setEvents(dynAddr, true, I3C_CCC_EVT_INTR, timeout) ? 0 : -1;
    }
  }

  return result;
}

int I3CBus::enableControllerEvents(uint32_t interruptMask)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)
  if (_initialized && (_hi3c.mode == HAL_I3C_MODE_CTRL)) {
    enableIRQs();
    hal_status_t st = HAL_I3C_CTRL_ActivateNotification(&_hi3c, interruptMask);
    if (st != HAL_OK) {
      disableIRQs();
    }
    result = HAL_I3C_GetError(_hi3c, st);
  }
#else
  if (_initialized && (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER)) {
    enableIRQs();
    HAL_StatusTypeDef st = HAL_I3C_ActivateNotification(&_hi3c, nullptr, interruptMask);
    if (st != HAL_OK) {
      if (_hi3c.Instance->IER == 0U) {
        disableIRQs();
      }
    }
    result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));
  }
#endif

  return result;
}

int I3CBus::disableControllerEvents(uint32_t interruptMask)
{
  int result = -1;

#if defined(USE_HALV2_DRIVER)
  if (_initialized && (_hi3c.mode == HAL_I3C_MODE_CTRL)) {
    hal_status_t st = HAL_I3C_CTRL_DeactivateNotification(&_hi3c, interruptMask);
    result = HAL_I3C_GetError(_hi3c, st);

    if ((st == HAL_OK) && (LL_I3C_GetEnabledIT(_instance) == 0U)) {
      disableIRQs();
    }
  }
#else
  if (_initialized && (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER)) {
    HAL_StatusTypeDef st = HAL_I3C_DeactivateNotification(&_hi3c, interruptMask);
    result = (st == HAL_OK) ? 0 : -static_cast<int>(HAL_I3C_GetError(&_hi3c));

    if ((st == HAL_OK) && (_hi3c.Instance->IER == 0U)) {
      disableIRQs();
    }
  }
#endif

  return result;
}

bool I3CBus::hasIbi() const
{
  return _ibiPending;
}

bool I3CBus::peekIbi(I3CControllerIbiInfo &out) const
{
  bool result = false;

  if (_ibiPending) {
    noInterrupts();
    out = _lastIbi;
    interrupts();
    result = true;
  }

  return result;
}

bool I3CBus::readIbi(I3CControllerIbiInfo &out)
{
  bool result = false;

  if (_ibiPending) {
    noInterrupts();
    out = _lastIbi;
    _lastIbi.pending = false;
    _ibiPending      = false;
    interrupts();
    result = true;
  }

  return result;
}

void I3CBus::onIbi(I3CIbiCallback cb, void *user)
{
  _ibiCb     = cb;
  _ibiCbUser = user;
}

void I3CBus::handleHalNotify(uint32_t eventId)
{
#if defined(USE_HALV2_DRIVER)

  if (_hi3c.mode == HAL_I3C_MODE_CTRL) {
    if ((eventId & HAL_I3C_CTRL_NOTIFICATION_IBI) != 0U) {
      hal_i3c_ccc_info_t info {};
      if (HAL_I3C_GetCCCInfo(&_hi3c, HAL_I3C_CTRL_NOTIFICATION_IBI, &info) == HAL_OK) {
        _lastIbi.pending     = true;
        _lastIbi.eventId     = eventId;
        _lastIbi.sourceDa    = static_cast<uint8_t>(info.ibi_cr_tgt_addr);
        _lastIbi.payloadSize = static_cast<uint8_t>(info.ibi_tgt_nb_payload);
        _lastIbi.payloadRaw  = info.ibi_tgt_payload;
        _lastIbi.timestampMs = millis();
        _ibiPending          = true;

        if (_ibiCb != nullptr) {
          _ibiCb(_lastIbi, _ibiCbUser);
        }
      }
    }
  } else if (_hi3c.mode == HAL_I3C_MODE_TGT) {
    _lastTargetEventId  = eventId;
    _targetEventPending = true;
  }

#else

  if (_hi3c.Mode == HAL_I3C_MODE_CONTROLLER) {
    if ((eventId & EVENT_ID_IBI) != 0U) {
      I3C_CCCInfoTypeDef info{};
      if (HAL_I3C_GetCCCInfo(&_hi3c, EVENT_ID_IBI, &info) == HAL_OK) {
        _lastIbi.pending     = true;
        _lastIbi.eventId     = eventId;
        _lastIbi.sourceDa    = static_cast<uint8_t>(info.IBICRTgtAddr);
        _lastIbi.payloadSize = static_cast<uint8_t>(info.IBITgtNbPayload);
        _lastIbi.payloadRaw  = info.IBITgtPayload;
        _lastIbi.timestampMs = millis();
        _ibiPending          = true;

        if (_ibiCb != nullptr) {
          _ibiCb(_lastIbi, _ibiCbUser);
        }
      }
    }
  } else if (_hi3c.Mode == HAL_I3C_MODE_TARGET) {
    _lastTargetEventId  = eventId;
    _targetEventPending = true;
  }

#endif
}

// ============================================================================
// Clock helpers
// ============================================================================
uint32_t I3CBus::getPeripheralClockFreq() const
{
  uint32_t srcFreq = 0U;

#if defined(USE_HALV2_DRIVER)

  srcFreq = HAL_I3C_GetClockFreq(&_hi3c);

#else

#if defined(I3C1)
  if (_instance == I3C1) {
    srcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I3C1);
  }
#endif

#if defined(I3C2)
  if (_instance == I3C2) {
    srcFreq = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_I3C2);
  }
#endif
#endif

  return srcFreq;
}

#if defined(USE_HALV2_DRIVER)
bool I3CBus::buildControllerTiming(uint32_t srcFreq,
                                   uint32_t freq,
                                   I3CBusType busType,
                                   uint32_t mixedBusOdFreq,
                                   hal_i3c_ctrl_config_t &outCtrl)
{
  bool result = false;

  if (srcFreq != 0U) {
    stm32_utils_i3c_ctrl_timing_config_t inTiming {};
    uint32_t timingReg0 = 0U;
    uint32_t timingReg1 = 0U;

    inTiming.clock_src_freq_hz  = srcFreq;
    inTiming.i3c_pp_freq_hz     = (freq == 0U) ? 1000000U : freq;
    inTiming.i2c_od_freq_hz     = (busType == I3CBusType::Pure) ? 0U : mixedBusOdFreq;
    inTiming.duty_cycle_purcent = 50U;
    inTiming.wait_time          = STM32_UTILS_I3C_ACTIVITY_STATE_0;
    inTiming.bus_type           = (busType == I3CBusType::Pure)
                                  ? STM32_UTILS_I3C_PURE_I3C_BUS
                                  : STM32_UTILS_I3C_I2C_MIXED_BUS;

    if (STM32_UTILS_I3C_CTRL_ComputeTiming(&inTiming, &timingReg0, &timingReg1) == STM32_UTILS_I3C_OK) {
      outCtrl.timing_reg0 = timingReg0;
      outCtrl.timing_reg1 = timingReg1;
      result = true;
    }
  }

  return result;
}

bool I3CBus::buildTargetTiming(uint32_t srcFreq, hal_i3c_tgt_config_t &outTgt)
{
  bool result = false;

  if (srcFreq != 0U) {
    stm32_utils_i3c_tgt_timing_config_t inTiming {};
    uint32_t timingReg1 = 0U;

    inTiming.clock_src_freq_hz = srcFreq;

    if (STM32_UTILS_I3C_TGT_ComputeTiming(&inTiming, &timingReg1) == STM32_UTILS_I3C_OK) {
      outTgt.timing_reg1 = timingReg1;
      result = true;
    }
  }

  return result;
}
#else
bool I3CBus::buildControllerTiming(uint32_t freq, LL_I3C_CtrlBusConfTypeDef &outCtrl) const
{
  bool result = false;
  uint32_t srcFreq = getPeripheralClockFreq();

  if (srcFreq != 0U) {
    I3C_CtrlTimingTypeDef inTiming {};

    inTiming.clockSrcFreq = srcFreq;
    inTiming.i3cPPFreq    = (freq == 0U) ? 1000000U : freq;
    inTiming.dutyCycle    = 50U;

    if (_busType == I3CBusType::Pure) {
      inTiming.busType   = I3C_PURE_I3C_BUS;
      inTiming.i2cODFreq = 0U;
    } else {
      inTiming.busType   = I3C_MIXED_BUS;
      inTiming.i2cODFreq = _mixedBusOdFreq;
    }

    if (I3C_CtrlTimingComputation(&inTiming, &outCtrl) == SUCCESS) {
      result = true;
    }
  }

  return result;
}

bool I3CBus::buildTargetTiming(LL_I3C_TgtBusConfTypeDef &outTgt) const
{
  bool result = false;
  uint32_t srcFreq = getPeripheralClockFreq();

  if (srcFreq != 0U) {
    I3C_TgtTimingTypeDef inTiming {};
    inTiming.clockSrcFreq = srcFreq;

    if (I3C_TgtTimingComputation(&inTiming, &outTgt) == SUCCESS) {
      result = true;
    }
  }

  return result;
}
#endif

// ============================================================================
// IRQ handlers & helpers
// ============================================================================
void I3CBus::enableIRQs()
{
  if (!_irqEnabled) {
#if defined(I3C1)
    if (_instance == I3C1) {
#if defined(USE_HALV2_DRIVER)
      HAL_CORTEX_NVIC_SetPriority(I3C1_EV_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_5, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
      HAL_CORTEX_NVIC_EnableIRQ(I3C1_EV_IRQn);
      HAL_CORTEX_NVIC_SetPriority(I3C1_ERR_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_5, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
      HAL_CORTEX_NVIC_EnableIRQ(I3C1_ERR_IRQn);
#else
      HAL_NVIC_SetPriority(I3C1_EV_IRQn, 5, 0);
      HAL_NVIC_EnableIRQ(I3C1_EV_IRQn);
      HAL_NVIC_SetPriority(I3C1_ER_IRQn, 5, 0);
      HAL_NVIC_EnableIRQ(I3C1_ER_IRQn);
#endif
      _irqEnabled = true;
    }
#endif

#if defined(I3C2)
    if (_instance == I3C2) {
#if !defined(USE_HALV2_DRIVER)
      HAL_NVIC_SetPriority(I3C2_EV_IRQn, 5, 0);
      HAL_NVIC_EnableIRQ(I3C2_EV_IRQn);
      HAL_NVIC_SetPriority(I3C2_ER_IRQn, 5, 0);
      HAL_NVIC_EnableIRQ(I3C2_ER_IRQn);
      _irqEnabled = true;
#endif
    }
#endif
  }
}

void I3CBus::disableIRQs()
{
  if (_irqEnabled) {
#if defined(I3C1)
    if (_instance == I3C1) {
#if defined(USE_HALV2_DRIVER)
      HAL_CORTEX_NVIC_DisableIRQ(I3C1_EV_IRQn);
      HAL_CORTEX_NVIC_DisableIRQ(I3C1_ERR_IRQn);
#else
      HAL_NVIC_DisableIRQ(I3C1_EV_IRQn);
      HAL_NVIC_DisableIRQ(I3C1_ER_IRQn);
#endif
    }
#endif

#if defined(I3C2)
    if (_instance == I3C2) {
#if !defined(USE_HALV2_DRIVER)
      HAL_NVIC_DisableIRQ(I3C2_EV_IRQn);
      HAL_NVIC_DisableIRQ(I3C2_ER_IRQn);
#endif
    }
#endif

    _irqEnabled = false;
  }
}

void I3CBus::registerInstanceOwner()
{
#if defined(I3C1)
  if (_instance == I3C1) {
    g_i3c1Owner = this;
  }
#endif

#if defined(I3C2)
  if (_instance == I3C2) {
    g_i3c2Owner = this;
  }
#endif
}

void I3CBus::unregisterInstanceOwner()
{
#if defined(I3C1)
  if ((g_i3c1Owner == this) && (_instance == I3C1)) {
    g_i3c1Owner = nullptr;
  }
#endif

#if defined(I3C2)
  if ((g_i3c2Owner == this) && (_instance == I3C2)) {
    g_i3c2Owner = nullptr;
  }
#endif
}

/**
  * @brief  I3C1 event interrupt handler.
  */
extern "C" void I3C1_EV_IRQHandler(void)
{
#if defined(I3C1)
  if (g_i3c1Owner != nullptr) {
    HAL_I3C_EV_IRQHandler(g_i3c1Owner->halHandle());
  }
#endif
}

#if defined(USE_HALV2_DRIVER)
/**
  * @brief  I3C1 error interrupt handler.
  */
extern "C" void I3C1_ERR_IRQHandler(void)
{
#if defined(I3C1)
  if (g_i3c1Owner != nullptr) {
    HAL_I3C_ERR_IRQHandler(g_i3c1Owner->halHandle());
  }
#endif
}
#else
/**
  * @brief  I3C1 error interrupt handler.
  */
extern "C" void I3C1_ER_IRQHandler(void)
{
#if defined(I3C1)
  if (g_i3c1Owner != nullptr) {
    HAL_I3C_ER_IRQHandler(g_i3c1Owner->halHandle());
  }
#endif
}
#endif

#if defined(I3C2)
/**
  * @brief  I3C2 event interrupt handler.
  */
extern "C" void I3C2_EV_IRQHandler(void)
{
  if (g_i3c2Owner != nullptr) {
    HAL_I3C_EV_IRQHandler(g_i3c2Owner->halHandle());
  }
}

/**
  * @brief  I3C2 error interrupt handler.
  */
extern "C" void I3C2_ER_IRQHandler(void)
{
  if (g_i3c2Owner != nullptr) {
#if !defined(USE_HALV2_DRIVER)
    HAL_I3C_ER_IRQHandler(g_i3c2Owner->halHandle());
#endif
  }
}
#endif

#endif
