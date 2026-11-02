#pragma once

#include "Arduino.h"

#if defined(I3C1_BASE) || defined(I3C2_BASE)

#include "stm32yyxx_utils_i3c.h"

// ============================================================================
// Descriptors, configuration structures, and enums
// ============================================================================
/** @brief Number of elements of an array. */
#define COUNTOF(__BUFFER__) (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/**
 * @brief Description of a device found on the bus by discover() or assignDynamicAddresses().
 */
struct I3CDiscoveredDevice {
  /** 7-bit dynamic address. */
  uint8_t  dynAddr = 0;
  /** 7-bit static address if known, else 0. */
  uint8_t  staticAddr = 0;
  /** Bus Characteristics Register. */
  uint8_t  bcr = 0;
  /** Device Characteristics Register. */
  uint8_t  dcr = 0;
  /** 48-bit Provisioned ID. */
  uint64_t pid = 0;
  /** Full raw 64-bit payload from HAL DAA. */
  uint64_t entdaaPayloadRaw = 0;
  /** true if the device address was assigned by DAA (ENTDAA). */
  bool     fromDaa = false;
  /** true if the device address was assigned by SETDASA. */
  bool     assignedBySetdasa = false;
  /** true if the device matches an I3CKnownDevice entry. */
  bool     matchedKnown = false;
};

/**
 * @brief Options of the bus initialization sequence run by discover().
 */
struct I3CBusBeginConfig {
  /** Send the RSTACT CCC first (whole target reset, else peripheral only). */
  bool    doRstact = false;
  /** Reset all dynamic addresses (RSTDAA CCC). */
  bool    doRstdaa = true;
  /** Disable all target events (DISEC CCC). */
  bool    disableEvents = true;
  /** Assign the dynamic address of the known devices from their static
   *  address. */
  bool    doSetdasa = true;
  /** Run the dynamic address assignment (ENTDAA CCC) for the unknown
   *  devices. */
  bool    doDaa = true;
  /** Retry the DAA phase once if it fails. */
  bool    retryDaaOnce = true;
  /** Enable the Hot-Join event once the sequence is done. */
  bool    allowHotJoinAfterInit = false;
  /** First dynamic address used by DAA. */
  uint8_t firstAutoDynAddr = 0x10;
  /** Run DAA also when known devices were assigned. */
  bool    discoverUnknownAfterKnown = false;
};

/**
 * @brief Description of a device expected on the bus, used by discover().
 */
struct I3CKnownDevice {
  /** 48-bit PID in low bits if known, else 0. */
  uint64_t pid = 0;
  /** 7-bit static address, 0 if none. */
  uint8_t  staticAddr = 0;
  /** 7-bit preferred dynamic address, 0 = auto. */
  uint8_t  preferredDynAddr = 0;
  /** true if the device supports the SETAASA CCC. */
  bool     supportsSetaasa = false;
  /** false to ignore this entry. */
  bool     present = true;
};

/**
 * @brief Role of the I3C peripheral on the bus.
 */
enum class I3CRole : uint8_t {
  None,       /**< Not initialized. */
  Controller, /**< Bus controller. */
  Target      /**< Bus target. */
};

/**
 * @brief Target mode configuration, see I3CBus::beginTarget() and I3CBus::configureTarget().
 *
 * The HAL specific values use the definitions of the STM32Cube HAL I3C driver in use.
 */
struct I3CTargetConfig {
  /** Device Characteristics Register (DCR). */
  uint8_t  identifier = 0;
  /** MIPI Instance ID (4 useful bits). */
  uint8_t  mipiIdentifier = 0;

  /** Enable the controller role request. */
  bool     ctrlRoleRequest = false;
  /** Enable the Hot-Join request. */
  bool     hotJoinRequest = false;
  /** Enable the In-Band Interrupt (IBI) request. */
  bool     ibiRequest = false;
  /** true if the IBI carries a payload. */
  bool     ibiPayload = false;

  /** Size of the IBI payload. */
  uint32_t ibiPayloadSize = LL_I3C_PAYLOAD_EMPTY;

  /** Maximum read data size in bytes. */
  uint16_t maxReadDataSize = 0xFFFF;
  /** Maximum write data size in bytes. */
  uint16_t maxWriteDataSize = 0xFFFF;

  /** true if the target is controller capable. */
  bool     ctrlCapability = false;
  /** true if the target supports group addresses. */
  bool     groupAddrCapability = false;

  /** Data turnaround duration. */
  uint32_t dataTurnAroundDuration = HAL_I3C_TURNAROUND_TIME_TSCO_LESS_12NS;
  /** Maximum read turnaround time. */
  uint8_t  maxReadTurnAround = 0;
  /** GETMXDS CCC format. */
  uint32_t maxDataSpeed = HAL_I3C_GETMXDS_FORMAT_1;
  /** Activity state after the controller hand-off. */
  uint32_t handOffActivityState = HAL_I3C_HANDOFF_ACTIVITY_STATE_0;

  /** true if the target has a maximum data speed limitation. */
  bool     maxSpeedLimitation = false;
  /** Enable the controller hand-off delay. */
  bool     handOffDelay = false;
  /** Enable the pending read Mandatory Data Byte (MDB). */
  bool     pendingReadMDB = false;
};

/**
 * @brief In-Band Interrupt (IBI) received by the controller.
 */
typedef struct {
  /** true if the IBI has not been read yet. */
  bool     pending = false;
  /** HAL event identifier. */
  uint32_t eventId = 0;
  /** Dynamic address of the target which raised the IBI. */
  uint8_t  sourceDa = 0;
  /** Size of the payload in bytes. */
  uint8_t  payloadSize = 0;
  /** Raw IBI payload. */
  uint32_t payloadRaw = 0;
  /** Reception time in milliseconds. */
  uint32_t timestampMs = 0;
} I3CControllerIbiInfo;

/**
 * @brief IBI callback type, see I3CBus::onIbi().
 * @param info Received IBI.
 * @param user User pointer given to I3CBus::onIbi().
 */
using I3CIbiCallback = void (*)(const I3CControllerIbiInfo &info, void *user);

/**
 * @brief Type of the bus.
 */
enum class I3CBusType : uint8_t {
  Pure,   /**< Only I3C devices on the bus. */
  Mixed   /**< I3C and legacy I2C devices on the bus. */
};

/**
 * @brief Kind of transfer used by the unified transfer functions.
 */
enum class I3CTransferType : uint8_t {
  I3C,    /**< Private SDR transfer using I3C dynamic address. */
  I2C     /**< Legacy I2C transfer using static 7-bit address. */
};

/**
 * @brief Controller mode configuration, see I3CBus::begin().
 *
 * The default FIFO threshold values depend on the STM32Cube HAL I3C driver in use.
 */
struct I3CControllerConfig {

#if defined(USE_HALV2_DRIVER)
  /** Reception FIFO threshold. */
  uint32_t rxFifoThreshold = HAL_I3C_RX_FIFO_THRESHOLD_1_8;
  /** Transmission FIFO threshold. */
  uint32_t txFifoThreshold = HAL_I3C_TX_FIFO_THRESHOLD_1_8;
  /** Control FIFO state (0: disabled). */
  uint32_t controlFifo     = 0U;
  /** Status FIFO state (0: disabled). */
  uint32_t statusFifo      = 0U;
#else
  /** Reception FIFO threshold. */
  uint32_t rxFifoThreshold = HAL_I3C_RXFIFO_THRESHOLD_1_4;
  /** Transmission FIFO threshold. */
  uint32_t txFifoThreshold = HAL_I3C_TXFIFO_THRESHOLD_1_4;
  /** Control FIFO state. */
  uint32_t controlFifo     = HAL_I3C_CONTROLFIFO_DISABLE;
  /** Status FIFO state. */
  uint32_t statusFifo      = HAL_I3C_STATUSFIFO_DISABLE;
#endif

  /** Own dynamic address of the controller. */
  uint8_t  dynamicAddr     = 0U;
  /** Stall time in number of clock cycles. */
  uint8_t  stallTime       = 0x00U;

  /** Allow Hot-Join requests from the targets. */
  bool     hotJoinAllowed  = false;
  /** Stall the clock after the ACK phase. */
  bool     ackStall        = false;
  /** Stall the clock after the CCC code. */
  bool     cccStall        = false;
  /** Stall the clock during the transmitted data. */
  bool     txStall         = false;
  /** Stall the clock during the received data. */
  bool     rxStall         = false;
  /** Enable the high keeper on SDA. */
  bool     highKeeperSDA   = false;
};

/**
 * @brief Reception buffer of the target events, see I3CBus::enableTargetEvents().
 */
struct I3CTargetEventConfig {
  uint8_t *rxData = nullptr;     /**< Buffer filled with the received data. */
  uint32_t rxSize = 0U;          /**< Size of the buffer in bytes. */
};

/**
 * @brief Content of an ENEC/DISEC CCC received by a target, see I3CBus::getTargetCccInfo().
 */
struct I3CTargetCccInfo {
  bool hotJoinAllowed = false;   /**< Hot-Join requests are allowed. */
  bool inBandAllowed = false;    /**< In-Band Interrupt requests are allowed. */
  bool ctrlRoleAllowed = false;  /**< Controller role requests are allowed. */
};
// ============================================================================
// I3CBus
// ============================================================================

/**
 * @brief I3C bus instance, used as controller or as target.
 *
 * The global I3C object is the default instance. Timeouts are in milliseconds.
 * Unless specified otherwise, the transfer functions return 0 on success and a
 * negative value on error (-1 if the arguments are invalid or the bus is not
 * initialized in the expected role, else the opposite of the HAL error code
 * when available).
 * Addresses are 7-bit addresses.
 */
class I3CBus {
  public:
    /**
     * @brief Create an I3C bus instance, not initialized.
     */
    explicit I3CBus() : _instance(nullptr) {}

    // ------------------------------------------------------------------------
    // Controller initialization and bus configuration
    // ------------------------------------------------------------------------
    /**
     * @brief Initialize the instance as controller using the given pins.
     * @param sda SDA pin.
     * @param scl SCL pin. Both pins must belong to the same I3C peripheral.
     * @param freq I3C push-pull frequency in Hz. Default: 1 MHz.
     * @param type Bus type: I3CBusType::Pure or I3CBusType::Mixed (with legacy I2C devices).
     * @param mixedOdHz Open-drain frequency in Hz used on a mixed bus.
     *        Default: 1 MHz.
     * @return true if the controller is initialized, false otherwise.
     */
    bool begin(pin_size_t sda,
               pin_size_t scl,
               uint32_t freq = 1000000U,
               I3CBusType type = I3CBusType::Pure,
               uint32_t mixedOdHz = 1000000U);

    /**
     * @brief Initialize the instance as controller using the default I3C_SDA
     *        and I3C_SCL pins.
     * @param freq I3C push-pull frequency in Hz. Default: 1 MHz.
     * @param type Bus type: I3CBusType::Pure or I3CBusType::Mixed (with legacy I2C devices).
     * @param mixedOdHz Open-drain frequency in Hz used on a mixed bus.
     *        Default: 1 MHz.
     * @return true if the controller is initialized, false otherwise.
     */
    bool begin(uint32_t freq = 1000000U,
               I3CBusType type = I3CBusType::Pure,
               uint32_t mixedOdHz = 1000000U);

    /**
     * @brief Initialize the instance as controller using the given pins and
     *        controller configuration.
     * @param sda SDA pin.
     * @param scl SCL pin. Both pins must belong to the same I3C peripheral.
     * @param freq I3C push-pull frequency in Hz.
     * @param type Bus type: I3CBusType::Pure or I3CBusType::Mixed (with legacy I2C devices).
     * @param mixedOdHz Open-drain frequency in Hz used on a mixed bus.
     * @param ctrlCfg Controller configuration.
     * @return true if the controller is initialized, false otherwise.
     */
    bool begin(pin_size_t sda,
               pin_size_t scl,
               uint32_t freq,
               I3CBusType type,
               uint32_t mixedOdHz,
               const I3CControllerConfig &ctrlCfg);

    /**
     * @brief Initialize the instance as controller using the default I3C_SDA
     *        and I3C_SCL pins and the given controller configuration.
     * @param freq I3C push-pull frequency in Hz.
     * @param type Bus type: I3CBusType::Pure or I3CBusType::Mixed (with legacy I2C devices).
     * @param mixedOdHz Open-drain frequency in Hz used on a mixed bus.
     * @param ctrlCfg Controller configuration.
     * @return true if the controller is initialized, false otherwise.
     */
    bool begin(uint32_t freq,
               I3CBusType type,
               uint32_t mixedOdHz,
               const I3CControllerConfig &ctrlCfg);

    /**
     * @brief Change the I3C push-pull frequency. Only available in controller mode.
     * @param hz New frequency in Hz.
     * @return true if the new timings are applied, false otherwise.
     */
    bool setClock(uint32_t hz);

    /**
     * @brief Set the bus type. Used by the next timing computation, see begin() and setClock().
     * @param type Bus type.
     */
    void setBusType(I3CBusType type);
    /**
     * @brief Get the bus type.
     * @return Bus type.
     */
    I3CBusType getBusType() const;

    /**
     * @brief Set the open-drain frequency used on a mixed bus. Used by the next timing computation.
     * @param hz Open-drain frequency in Hz.
     */
    void setMixedBusOpenDrainFrequency(uint32_t hz);
    /**
     * @brief Get the open-drain frequency used on a mixed bus.
     * @return Open-drain frequency in Hz.
     */
    uint32_t getMixedBusOpenDrainFrequency() const;

    /**
     * @brief Get the role of the instance.
     * @return I3CRole::None if the instance is not initialized, else its role.
     */
    I3CRole getRole() const;
    /**
     * @brief Check if the instance is initialized as controller.
     * @return true if the instance is a controller, false otherwise.
     */
    bool isController() const;
    /**
     * @brief Check if the instance is initialized as target.
     * @return true if the instance is a target, false otherwise.
     */
    bool isTarget() const;

    /**
     * @brief Deinitialize the instance: disable the interrupts, the peripheral,
     *        its pins and its clock.
     */
    void end();

    /**
     * @brief Flush all the FIFOs of the peripheral.
     * @return true if the FIFOs are flushed, false otherwise.
     */
    bool  flushAllFifos();

    // ------------------------------------------------------------------------
    // Default I3C controller transfers
    // ------------------------------------------------------------------------
    /**
     * @brief Write data to an I3C target (private transfer). Controller mode only.
     * @param dynAddr Dynamic address of the target.
     * @param buf Data to send.
     * @param len Number of bytes to send, it must not be 0.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error (-1 if the arguments are
     *         invalid or not in controller mode).
     */
    int write(uint8_t dynAddr,
              const uint8_t *buf,
              size_t len,
              uint32_t timeout = 1000U);

    /**
     * @brief Read data from an I3C target (private transfer). Controller mode only.
     * @param dynAddr Dynamic address of the target.
     * @param buf Buffer filled with the received data.
     * @param len Number of bytes to read, it must not be 0.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error (-1 if the arguments are
     *         invalid or not in controller mode).
     */
    int read(uint8_t dynAddr,
             uint8_t *buf,
             size_t len,
             uint32_t timeout = 1000U);

    /**
     * @brief Write one register of an I3C target. Controller mode only.
     * @param dynAddr Dynamic address of the target.
     * @param reg Register address.
     * @param value Value to write.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int writeReg(uint8_t dynAddr,
                 uint8_t reg,
                 uint8_t value,
                 uint32_t timeout = 1000U);

    /**
     * @brief Read one register of an I3C target. Controller mode only.
     * @param dynAddr Dynamic address of the target.
     * @param reg Register address.
     * @param value Read value.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int readReg(uint8_t dynAddr,
                uint8_t reg,
                uint8_t &value,
                uint32_t timeout = 1000U);

    /**
     * @brief Write several consecutive registers of an I3C target. Controller mode only.
     * @param dynAddr Dynamic address of the target.
     * @param reg Address of the first register.
     * @param pData Data to write.
     * @param len Number of bytes to write.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error (-1 if the arguments are
     *         invalid or not in controller mode).
     */
    int writeRegBuffer(uint8_t dynAddr,
                       uint8_t reg,
                       const uint8_t *pData,
                       size_t len,
                       uint32_t timeout = 1000U);

    /**
     * @brief Read several consecutive registers of an I3C target. Controller mode only.
     * @param dynAddr Dynamic address of the target.
     * @param reg Address of the first register.
     * @param pData Buffer filled with the read data.
     * @param len Number of bytes to read.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error (-1 if the arguments are
     *         invalid or not in controller mode).
     */
    int readRegBuffer(uint8_t dynAddr,
                      uint8_t reg,
                      uint8_t *pData,
                      size_t len,
                      uint32_t timeout = 1000U);

    // ------------------------------------------------------------------------
    // Unified transfers with selectable transport kind
    // ------------------------------------------------------------------------
    /**
     * @brief Write data to a target using the selected transport.
     * @param addr Dynamic address (I3C) or static address (I2C) of the target.
     * @param buf Data to send.
     * @param len Number of bytes to send.
     * @param type Transfer type: I3CTransferType::I3C or I3CTransferType::I2C.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     * @see write(uint8_t, const uint8_t *, size_t, uint32_t), i2cWrite()
     */
    int write(uint8_t addr,
              const uint8_t *buf,
              size_t len,
              I3CTransferType type,
              uint32_t timeout = 1000U);

    /**
     * @brief Read data from a target using the selected transport.
     * @param addr Dynamic address (I3C) or static address (I2C) of the target.
     * @param buf Buffer filled with the received data.
     * @param len Number of bytes to read.
     * @param type Transfer type: I3CTransferType::I3C or I3CTransferType::I2C.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     * @see read(uint8_t, uint8_t *, size_t, uint32_t), i2cRead()
     */
    int read(uint8_t addr,
             uint8_t *buf,
             size_t len,
             I3CTransferType type,
             uint32_t timeout = 1000U);

    /**
     * @brief Write one register of a target using the selected transport.
     * @param addr Dynamic address (I3C) or static address (I2C) of the target.
     * @param reg Register address.
     * @param value Value to write.
     * @param type Transfer type: I3CTransferType::I3C or I3CTransferType::I2C.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int writeReg(uint8_t addr,
                 uint8_t reg,
                 uint8_t value,
                 I3CTransferType type,
                 uint32_t timeout = 1000U);

    /**
     * @brief Read one register of a target using the selected transport.
     * @param addr Dynamic address (I3C) or static address (I2C) of the target.
     * @param reg Register address.
     * @param value Read value.
     * @param type Transfer type: I3CTransferType::I3C or I3CTransferType::I2C.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int readReg(uint8_t addr,
                uint8_t reg,
                uint8_t &value,
                I3CTransferType type,
                uint32_t timeout = 1000U);

    /**
     * @brief Write several consecutive registers of a target using the selected transport.
     * @param addr Dynamic address (I3C) or static address (I2C) of the target.
     * @param reg Address of the first register.
     * @param pData Data to write.
     * @param len Number of bytes to write.
     * @param type Transfer type: I3CTransferType::I3C or I3CTransferType::I2C.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int writeRegBuffer(uint8_t addr,
                       uint8_t reg,
                       const uint8_t *pData,
                       size_t len,
                       I3CTransferType type,
                       uint32_t timeout = 1000U);

    /**
     * @brief Read several consecutive registers of a target using the selected transport.
     * @param addr Dynamic address (I3C) or static address (I2C) of the target.
     * @param reg Address of the first register.
     * @param pData Buffer filled with the read data.
     * @param len Number of bytes to read.
     * @param type Transfer type: I3CTransferType::I3C or I3CTransferType::I2C.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int readRegBuffer(uint8_t addr,
                      uint8_t reg,
                      uint8_t *pData,
                      size_t len,
                      I3CTransferType type,
                      uint32_t timeout = 1000U);

    // ------------------------------------------------------------------------
    // Legacy I2C transfers on mixed I3C bus
    // ------------------------------------------------------------------------
    /**
     * @brief Write data to a legacy I2C device. Controller mode and mixed bus only.
     * @param staticAddr 7-bit static address of the device, from 0x08 to 0x77.
     * @param buf Data to send.
     * @param len Number of bytes to send, it must not be 0.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error (-1 if the arguments are
     *         invalid or the bus is not a mixed bus).
     */
    int i2cWrite(uint8_t staticAddr,
                 const uint8_t *buf,
                 size_t len,
                 uint32_t timeout = 1000U);

    /**
     * @brief Read data from a legacy I2C device. Controller mode and mixed bus only.
     * @param staticAddr 7-bit static address of the device, from 0x08 to 0x77.
     * @param buf Buffer filled with the received data.
     * @param len Number of bytes to read, it must not be 0.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error (-1 if the arguments are
     *         invalid or the bus is not a mixed bus).
     */
    int i2cRead(uint8_t staticAddr,
                uint8_t *buf,
                size_t len,
                uint32_t timeout = 1000U);

    /**
     * @brief Write then read data of a legacy I2C device in one transfer
     *        (repeated start). Controller mode and mixed bus only.
     * @param staticAddr 7-bit static address of the device, from 0x08 to 0x77.
     * @param txBuf Data to send.
     * @param txLen Number of bytes to send, it must not be 0.
     * @param rxBuf Buffer filled with the received data.
     * @param rxLen Number of bytes to read, it must not be 0.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error (-1 if the arguments are
     *         invalid or the bus is not a mixed bus).
     */
    int i2cWriteRead(uint8_t staticAddr,
                     const uint8_t *txBuf,
                     size_t txLen,
                     uint8_t *rxBuf,
                     size_t rxLen,
                     uint32_t timeout = 1000U);

    /**
     * @brief Write one register of a legacy I2C device. Controller mode and
     *        mixed bus only.
     * @param staticAddr 7-bit static address of the device.
     * @param reg Register address.
     * @param value Value to write.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int i2cWriteReg(uint8_t staticAddr,
                    uint8_t reg,
                    uint8_t value,
                    uint32_t timeout = 1000U);

    /**
     * @brief Read one register of a legacy I2C device. Controller mode and
     *        mixed bus only.
     * @param staticAddr 7-bit static address of the device.
     * @param reg Register address.
     * @param value Read value.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int i2cReadReg(uint8_t staticAddr,
                   uint8_t reg,
                   uint8_t &value,
                   uint32_t timeout = 1000U);

    /**
     * @brief Write several consecutive registers of a legacy I2C device.
     *        Controller mode and mixed bus only.
     * @param staticAddr 7-bit static address of the device.
     * @param reg Address of the first register.
     * @param pData Data to write.
     * @param len Number of bytes to write.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int i2cWriteRegBuffer(uint8_t staticAddr,
                          uint8_t reg,
                          const uint8_t *pData,
                          size_t len,
                          uint32_t timeout = 1000U);

    /**
     * @brief Read several consecutive registers of a legacy I2C device.
     *        Controller mode and mixed bus only.
     * @param staticAddr 7-bit static address of the device.
     * @param reg Address of the first register.
     * @param pData Buffer filled with the read data.
     * @param len Number of bytes to read.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int i2cReadRegBuffer(uint8_t staticAddr,
                         uint8_t reg,
                         uint8_t *pData,
                         size_t len,
                         uint32_t timeout = 1000U);

    /**
     * @brief Scan the legacy I2C devices (0x08 to 0x77) of a mixed bus.
     *        Controller mode only.
     *
     * The addresses of the devices found are marked as used.
     * @param addrs Array filled with the static addresses of the devices found.
     * @param maxAddrs Size of the addrs array.
     * @param foundCount Number of devices found, it can be greater than maxAddrs.
     * @param trials Number of trials per address. Default: 2.
     * @param timeout Timeout per trial in milliseconds. Default: 10.
     * @return 0 on success, -1 if the arguments are invalid or the bus is not a
     *         mixed bus controller.
     */
    int scanI2CDevices(uint8_t *addrs,
                       size_t maxAddrs,
                       size_t *foundCount,
                       uint32_t trials = 2U,
                       uint32_t timeout = 10U);

    // ------------------------------------------------------------------------
    // Device readiness checks
    // ------------------------------------------------------------------------
    /**
     * @brief Check if a legacy I2C device acknowledges its address.
     * @param staticAddr 7-bit static address of the device.
     * @param trials Number of trials. Default: 3.
     * @param timeout Timeout per trial in milliseconds. Default: 10.
     * @return true if the device is ready, false otherwise.
     */
    bool isI2CDeviceReady(uint8_t staticAddr,
                          uint32_t trials = 3U,
                          uint32_t timeout = 10U);

    /**
     * @brief Check if an I3C device acknowledges its dynamic address.
     * @param dynAddr Dynamic address of the device.
     * @param trials Number of trials. Default: 3.
     * @param timeout Timeout per trial in milliseconds. Default: 10.
     * @return true if the device is ready, false otherwise.
     */
    bool isI3CDeviceReady(uint8_t dynAddr,
                          uint32_t trials = 3U,
                          uint32_t timeout = 10U);

    // ------------------------------------------------------------------------
    // CCC broadcast & direct commands
    // ------------------------------------------------------------------------
    /**
     * @brief Reset the dynamic addresses of all the targets (RSTDAA broadcast CCC).
     * @return true on success, false otherwise.
     */
    bool resetDynamicAddresses();
    /**
     * @brief Disable events on all the targets (DISEC broadcast CCC).
     * @param pCCCData Events to disable, as defined by the DISEC CCC. Can be
     *        NULL if length is 0.
     * @param length Number of bytes of pCCCData.
     * @return true on success, false otherwise.
     */
    bool disableEvents(const uint8_t *pCCCData, uint16_t length);
    /**
     * @brief Assign the static address as dynamic address on all the targets
     *        supporting it (SETAASA broadcast CCC).
     * @return true on success, false otherwise.
     */
    bool assignAllStaticAsDynamic();
    /**
     * @brief Assign a dynamic address to a target from its static address
     *        (SETDASA direct CCC).
     * @param staticAddr 7-bit static address of the target.
     * @param dynAddr 7-bit dynamic address to assign.
     * @return true on success, false otherwise.
     */
    bool assignDynamicAddress(uint8_t staticAddr, uint8_t dynAddr);

    /**
     * @brief Get the Bus Characteristics Register of a target (GETBCR direct CCC).
     * @param dynAddr Dynamic address of the target.
     * @param bcr Value read, only updated on success.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return true on success, false otherwise.
     */
    bool getbcr(uint8_t dynAddr, uint8_t &bcr, uint32_t timeout = 1000U);
    /**
     * @brief Get the Device Characteristics Register of a target (GETDCR direct CCC).
     * @param dynAddr Dynamic address of the target.
     * @param dcr Value read, only updated on success.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return true on success, false otherwise.
     */
    bool getdcr(uint8_t dynAddr, uint8_t &dcr, uint32_t timeout = 1000U);
    /**
     * @brief Get the 48-bit Provisioned ID of a target (GETPID direct CCC).
     * @param dynAddr Dynamic address of the target.
     * @param pid Value read, only updated on success.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return true on success, false otherwise.
     */
    bool getpid(uint8_t dynAddr, uint64_t &pid, uint32_t timeout = 1000U);

    // ------------------------------------------------------------------------
    // Discovery and dynamic address assignment
    // ------------------------------------------------------------------------
    /**
     * @brief Assign dynamic addresses to all the targets answering the DAA
     *        (ENTDAA CCC). Controller mode only.
     * @param devices Array filled with the dynamic address of each device found.
     * @param maxDevices Size of the devices array.
     * @param firstDynAddr First dynamic address to assign, the next ones are
     *        incremented by 2. Default: 0x10. 0 selects the default value.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return Number of devices found (>= 0), a negative value on error
     *         (-1 invalid arguments or HAL error, -2 devices array too small,
     *         -3 address assignment failed).
     */
    int assignDynamicAddresses(I3CDiscoveredDevice *devices,
                               size_t maxDevices,
                               uint8_t firstDynAddr = 0x10U,
                               uint32_t timeout = 1000U);

    /**
     * @brief Run the bus initialization sequence: reset and assignment of the dynamic addresses.
     *
     * The sequence is selected by cfg: RSTACT, RSTDAA, DISEC, assignment of the
     * known devices (SETDASA/SETAASA), DAA of the unknown devices, Hot-Join enabling.
     * @param cfg Sequence options.
     * @param knownDevices Devices expected on the bus. Can be NULL.
     * @param numKnownDevices Number of entries of knownDevices.
     * @param discovered Array filled with the devices found.
     * @param maxDiscovered Size of the discovered array.
     * @param outCount Number of devices stored in discovered.
     * @return 0 on success, a negative value on error (-1 if the arguments are
     *         invalid or the bus is not initialized).
     */
    int discover(const I3CBusBeginConfig &cfg,
                 const I3CKnownDevice *knownDevices,
                 size_t numKnownDevices,
                 I3CDiscoveredDevice *discovered,
                 size_t maxDiscovered,
                 size_t *outCount);

    /**
     * @brief Discover the unknown I3C devices only, using the DAA.
     * @param discovered Array filled with the devices found.
     * @param maxDiscovered Size of the discovered array.
     * @param outCount Number of devices stored in discovered.
     * @param firstDynAddr First dynamic address to assign. Default: 0x10.
     * @return 0 on success, a negative value on error.
     */
    int discover(I3CDiscoveredDevice *discovered,
                 size_t maxDiscovered,
                 size_t *outCount,
                 uint8_t firstDynAddr = 0x10U)
    {
      I3CBusBeginConfig cfg{};
      cfg.doRstact = false;
      cfg.doRstdaa = true;
      cfg.disableEvents = true;
      cfg.doSetdasa = false;
      cfg.doDaa = true;
      cfg.retryDaaOnce = true;
      cfg.allowHotJoinAfterInit = false;
      cfg.firstAutoDynAddr = firstDynAddr;
      cfg.discoverUnknownAfterKnown = false;

      return discover(cfg, nullptr, 0U, discovered, maxDiscovered, outCount);
    }

    /**
     * @brief Assign the known devices, then optionally discover the unknown
     *        devices using the DAA.
     * @param knownDevices Devices expected on the bus.
     * @param numKnownDevices Number of entries of knownDevices.
     * @param discovered Array filled with the devices found.
     * @param maxDiscovered Size of the discovered array.
     * @param outCount Number of devices stored in discovered.
     * @param discoverUnknown true to also discover the unknown devices.
     *        Default: true.
     * @param firstDynAddr First dynamic address assigned by the DAA.
     *        Default: 0x10.
     * @return 0 on success, a negative value on error.
     */
    int discover(const I3CKnownDevice *knownDevices,
                 size_t numKnownDevices,
                 I3CDiscoveredDevice *discovered,
                 size_t maxDiscovered,
                 size_t *outCount,
                 bool discoverUnknown = true,
                 uint8_t firstDynAddr = 0x10U)
    {
      I3CBusBeginConfig cfg{};
      cfg.doRstact = false;
      cfg.doRstdaa = true;
      cfg.disableEvents = true;
      cfg.doSetdasa = true;
      cfg.doDaa = true;
      cfg.retryDaaOnce = true;
      cfg.allowHotJoinAfterInit = false;
      cfg.firstAutoDynAddr = firstDynAddr;
      cfg.discoverUnknownAfterKnown = discoverUnknown;

      return discover(cfg, knownDevices, numKnownDevices, discovered, maxDiscovered, outCount);
    }

    // ------------------------------------------------------------------------
    // Target mode initialization
    // ------------------------------------------------------------------------
    /**
     * @brief Initialize the instance as target using the given pins.
     * @param sda SDA pin.
     * @param scl SCL pin. Both pins must belong to the same I3C peripheral.
     * @param cfg Target configuration.
     * @return true if the target is initialized, false otherwise.
     */
    bool beginTarget(pin_size_t sda, pin_size_t scl, const I3CTargetConfig &cfg);
    /**
     * @brief Initialize the instance as target using the default I3C_SDA and I3C_SCL pins.
     * @param cfg Target configuration.
     * @return true if the target is initialized, false otherwise.
     */
    bool beginTarget(const I3CTargetConfig &cfg);
    /**
     * @brief Apply a target configuration. Target mode only.
     * @param cfg Target configuration.
     * @return 0 on success, a negative value on error.
     */
    int configureTarget(const I3CTargetConfig &cfg);

    /**
     * @brief Check if a dynamic address has been assigned to the target by the controller.
     * @return true if the target has a dynamic address, false otherwise.
     */
    bool hasAddress() const;
    /**
     * @brief Get the dynamic address of the target.
     * @return Dynamic address, 0 if none is assigned.
     */
    uint8_t address() const;

    // ------------------------------------------------------------------------
    // Target-side private communication
    // ------------------------------------------------------------------------
    /**
     * @brief Send data to the controller (private transfer). Target mode only.
     * @param buf Data to send.
     * @param len Number of bytes to send, it must not be 0.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error (-1 if the arguments are
     *         invalid or not in target mode).
     */
    int send(uint8_t *buf,
             uint16_t len,
             uint32_t timeout = 1000U);

    /**
     * @brief Receive data from the controller (private transfer). Target mode only.
     * @param buf Buffer filled with the received data.
     * @param len Size of the buffer in bytes, it must not be 0.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error (-1 if the arguments are
     *         invalid or not in target mode).
     */
    int receive(uint8_t *buf,
                uint16_t len,
                uint32_t timeout = 1000U);

    // ------------------------------------------------------------------------
    // Target-side non-private requests / events
    // ------------------------------------------------------------------------
    /**
     * @brief Request an In-Band Interrupt (IBI) to the controller. Target mode only.
     * @param payload IBI payload. Can be NULL if payloadSize is 0.
     * @param payloadSize Size of the payload in bytes.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int sendIbi(const uint8_t *payload,
                uint8_t payloadSize,
                uint32_t timeout = 1000U);

    /**
     * @brief Enable the notification of the target events and their interrupts.
     *        Target mode only.
     * @param cfg Reception buffer of the events.
     * @param interruptMask Mask of the events to enable, using the HAL notification definitions.
     * @return 0 on success, a negative value on error.
     */
    int enableTargetEvents(const I3CTargetEventConfig &cfg,
                           uint32_t interruptMask);

    /**
     * @brief Disable the notification of target events. Target mode only.
     *
     * The peripheral interrupts are disabled when no event remains enabled.
     * @param interruptMask Mask of the events to disable, using the HAL notification definitions.
     * @return 0 on success, a negative value on error.
     */
    int disableTargetEvents(uint32_t interruptMask);

    /**
     * @brief Enable or disable the events of a target (ENEC/DISEC direct CCC).
     *        Controller mode only.
     * @param dynAddr Dynamic address of the target.
     * @param enable true to enable the events (ENEC), false to disable them (DISEC).
     * @param events Events bit mask: 0x01 In-Band Interrupt, 0x02 controller
     *        role request, 0x08 Hot-Join.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return true on success, false otherwise.
     */
    bool setEvents(uint8_t dynAddr,
                   bool enable,
                   uint8_t events,
                   uint32_t timeout = 1000U);

    /**
     * @brief Check if a target event has been notified and not read yet.
     * @return true if an event is pending, false otherwise.
     */
    bool hasTargetEvent() const;
    /**
     * @brief Read and clear the last notified target event.
     * @param eventId HAL event identifier, only updated if an event is pending.
     * @return true if an event was pending, false otherwise.
     */
    bool readTargetEvent(uint32_t &eventId);
    /**
     * @brief Get the content of an ENEC/DISEC CCC received by the target.
     * @param eventId HAL event identifier, it must contain the ENEC/DISEC event.
     * @param out CCC information, cleared if the function fails.
     * @return true on success, false otherwise.
     */
    bool getTargetCccInfo(uint32_t eventId, I3CTargetCccInfo &out);

    // ------------------------------------------------------------------------
    // Controller-side IBI support
    // ------------------------------------------------------------------------
    /**
     * @brief Configure how the controller handles the requests of a target.
     *        Controller mode only.
     * @param deviceIndex Index of the device in the controller device table,
     *        from 1 to 4.
     * @param dynAddr Dynamic address of the target.
     * @param ibiAck true to acknowledge the In-Band Interrupts of the target.
     * @param ibiPayload true if the IBI of the target carries a payload.
     * @param ctrlRoleReqAck true to acknowledge the controller role requests of
     *        the target. Default: false.
     * @param stopTransfer true to stop the transfer after the IBI.
     *        Default: false.
     * @return 0 on success, a negative value on error (-1 if the arguments are
     *         invalid or not in controller mode).
     */
    int configureControllerDevice(uint8_t deviceIndex,
                                  uint8_t dynAddr,
                                  bool ibiAck,
                                  bool ibiPayload,
                                  bool ctrlRoleReqAck = false,
                                  bool stopTransfer = false);

    /**
     * @brief Enable the In-Band Interrupts of a target: configure the
     *        controller and enable the IBI event on the target.
     *        Controller mode only.
     * @param deviceIndex Index of the device in the controller device table,
     *        from 1 to 4.
     * @param dynAddr Dynamic address of the target.
     * @param withPayload true if the IBI of the target carries a payload.
     * @param stopTransfer true to stop the transfer after the IBI.
     *        Default: false.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return 0 on success, a negative value on error.
     */
    int enableIbi(uint8_t deviceIndex,
                  uint8_t dynAddr,
                  bool withPayload,
                  bool stopTransfer = false,
                  uint32_t timeout = 1000U);

    /**
     * @brief Enable the notification of the controller events and their
     *        interrupts. Controller mode only.
     * @param interruptMask Mask of the events to enable.
     *        Default: LL_I3C_IER_IBIIE (IBI).
     * @return 0 on success, a negative value on error.
     */
    int enableControllerEvents(uint32_t interruptMask = LL_I3C_IER_IBIIE);
    /**
     * @brief Disable the notification of controller events.
     *        Controller mode only.
     *
     * The peripheral interrupts are disabled when no event remains enabled.
     * @param interruptMask Mask of the events to disable.
     *        Default: LL_I3C_IER_IBIIE (IBI).
     * @return 0 on success, a negative value on error.
     */
    int disableControllerEvents(uint32_t interruptMask = LL_I3C_IER_IBIIE);

    /**
     * @brief Check if an IBI has been received and not read yet.
     * @return true if an IBI is pending, false otherwise.
     */
    bool hasIbi() const;
    /**
     * @brief Read and clear the last received IBI.
     * @param out Received IBI, only updated if an IBI is pending.
     * @return true if an IBI was pending, false otherwise.
     */
    bool readIbi(I3CControllerIbiInfo &out);
    /**
     * @brief Read the last received IBI without clearing it.
     * @param out Received IBI, only updated if an IBI is pending.
     * @return true if an IBI is pending, false otherwise.
     */
    bool peekIbi(I3CControllerIbiInfo &out) const;

    /**
     * @brief Register a callback called when an IBI is received.
     * @param cb Callback function, NULL to unregister.
     * @param user User pointer given to the callback. Default: nullptr.
     * @note The callback is called from the interrupt context.
     */
    void onIbi(I3CIbiCallback cb, void *user = nullptr);

    // ------------------------------------------------------------------------
    // Internal HAL bridge
    // ------------------------------------------------------------------------
    /**
     * @brief Handle a HAL notification. Called by the HAL callback, not
     *        intended to be used by the user.
     * @param eventId HAL event identifier.
     */
    void handleHalNotify(uint32_t eventId);

    /**
     * @brief Get the HAL handle of the instance, to mix the Arduino API and the
     *        STM32Cube HAL API.
     * @warning Use at your own risk.
     * @return Pointer to the HAL I3C handle.
     */
#if defined(USE_HALV2_DRIVER)
    hal_i3c_handle_t *halHandle()
    {
      return &_hi3c;
    }
#else
    I3C_HandleTypeDef *halHandle()
    {
      return &_hi3c;
    }
#endif

  private:
    // ------------------------------------------------------------------------
    // Instance
    // ------------------------------------------------------------------------
    /**
     * @brief Find the I3C peripheral matching the SDA and SCL pins.
     * @return true if a peripheral is found, false otherwise.
     */
    bool prepareInstanceFromPins();

    /**
     * @brief State of an address of the bus address map.
     */
    enum class I3CAddrState : uint8_t {
      Free,       /**< Address available. */
      /** Address reserved by the I3C specification (0x00, 0x7E and 0x7F). */
      Reserved,
      I2CDevice,  /**< Address used by a legacy I2C device. */
      I3CDevice   /**< Address used by an I3C device. */
    };

    // ------------------------------------------------------------------------
    // Low-level initialization
    // ------------------------------------------------------------------------
    /**
     * @brief Enable the clock of the I3C peripheral.
     * @return true if the clock is enabled, false otherwise.
     */
    bool initClocks();
    /**
     * @brief Configure the SDA and SCL pins for the I3C peripheral.
     * @return true if the pins are configured, false otherwise.
     */
    bool initGPIO();

    // ------------------------------------------------------------------------
    // Address map helpers
    // ------------------------------------------------------------------------
    /** @brief State of each of the 128 7-bit addresses of the bus. */
    I3CAddrState _addrMap[128] {};

    /**
     * @brief Mark all the addresses as free, except the reserved ones (0x00, 0x7E, 0x7F).
     */
    void initAddressMap();
    /**
     * @brief Check if an address can be used as dynamic address.
     * @param addr 7-bit address.
     * @return true if the address is usable, false otherwise.
     */
    bool isValidUsableDynamicAddr(uint8_t addr) const;
    /**
     * @brief Check if an address is a valid legacy I2C static address (0x08 to 0x77).
     * @param addr 7-bit address.
     * @return true if the address is valid, false otherwise.
     */
    bool isValidI2CStaticAddr(uint8_t addr) const;
    /**
     * @brief Check if an address is free in the address map.
     * @param addr 7-bit address.
     * @return true if the address is free, false otherwise.
     */
    bool isAddrFree(uint8_t addr) const;
    /**
     * @brief Mark an address as used by an I3C device.
     * @param addr 7-bit address.
     */
    void markAddrUsed(uint8_t addr);
    /**
     * @brief Mark an address as used by a legacy I2C device.
     * @param addr 7-bit address.
     */
    void markI2CAddrUsed(uint8_t addr);
    /**
     * @brief Mark an address as free. Reserved addresses are left untouched.
     * @param addr 7-bit address.
     */
    void markAddrFree(uint8_t addr);
    /**
     * @brief Find the first free usable dynamic address.
     * @param start Address from which the search starts (at least 0x08).
     * @return The address found, 0 if none is available.
     */
    uint8_t allocNextDynamicAddr(uint8_t start) const;

    // ------------------------------------------------------------------------
    // Bus sequencing helpers
    // ------------------------------------------------------------------------
    /**
     * @brief Disable all the events of all the targets (DISEC broadcast CCC).
     * @return true on success, false otherwise.
     */
    bool disecAll();
    /**
     * @brief Enable the Hot-Join event on all the targets (ENEC broadcast CCC).
     * @return true on success, false otherwise.
     */
    bool enecHotJoin();
    /**
     * @brief Reset the peripheral of all the targets only (RSTACT broadcast CCC).
     * @return true on success, false otherwise.
     */
    bool rstactPeripheralOnly();
    /**
     * @brief Reset the whole of all the targets (RSTACT broadcast CCC).
     * @return true on success, false otherwise.
     */
    bool rstactWholeTarget();

    /**
     * @brief Assign the dynamic address of the known devices using SETDASA, and
     *        record them in the address map.
     * @param knownDevices Devices expected on the bus. Can be NULL.
     * @param numKnownDevices Number of entries of knownDevices.
     * @param discovered Array filled with the devices assigned.
     * @param maxDiscovered Size of the discovered array.
     * @param count Number of entries of discovered, updated.
     * @param needAasa Set to true if some devices must be assigned with SETAASA.
     * @param needDaa Set to true if some devices must be assigned with DAA.
     * @return 0.
     */
    int assignKnownDevices(const I3CKnownDevice *knownDevices,
                           size_t numKnownDevices,
                           I3CDiscoveredDevice *discovered,
                           size_t maxDiscovered,
                           size_t &count,
                           bool &needAasa,
                           bool &needDaa);

    /**
     * @brief Run the dynamic address assignment (ENTDAA) until no more target answers.
     * @param cfg Sequence options, giving the first dynamic address.
     * @param knownDevices Devices expected on the bus, used to match the PID of
     *        the targets. Can be NULL.
     * @param numKnownDevices Number of entries of knownDevices.
     * @param discovered Array filled with the devices found.
     * @param maxDiscovered Size of the discovered array.
     * @param count Number of entries of discovered, updated.
     * @return 0 on success, a negative value on error.
     */
    int doDaaPhase(const I3CBusBeginConfig &cfg,
                   const I3CKnownDevice *knownDevices,
                   size_t numKnownDevices,
                   I3CDiscoveredDevice *discovered,
                   size_t maxDiscovered,
                   size_t &count);

    /**
     * @brief Declare the discovered devices (4 at most) in the controller device table.
     * @param discovered Devices found.
     * @param count Number of entries of discovered.
     * @return 0 on success, -1 on error.
     */
    int configBusDevicesFromDiscovery(const I3CDiscoveredDevice *discovered, size_t count);

    // ------------------------------------------------------------------------
    // Low-level CCC helpers
    // ------------------------------------------------------------------------
    /**
     * @brief Send a broadcast CCC.
     * @param cccId CCC code.
     * @param data CCC data. Can be NULL if length is 0.
     * @param length Number of bytes of data.
     * @param withDefByte true if the first data byte is the CCC defining byte.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return true on success, false otherwise.
     */
    bool cccBroadcastWrite(uint8_t cccId,
                           const uint8_t *data,
                           uint16_t length,
                           bool withDefByte,
                           uint32_t timeout = 1000U);

    /**
     * @brief Send a direct CCC writing data to a target.
     * @param targetAddr 7-bit address of the target.
     * @param cccId CCC code.
     * @param data CCC data. Can be NULL if length is 0.
     * @param length Number of bytes of data.
     * @param withDefByte true if the first data byte is the CCC defining byte.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return true on success, false otherwise.
     */
    bool cccDirectWrite(uint8_t targetAddr,
                        uint8_t cccId,
                        const uint8_t *data,
                        uint16_t length,
                        bool withDefByte,
                        uint32_t timeout = 1000U);

    /**
     * @brief Send a direct CCC reading data from a target.
     * @param targetAddr 7-bit address of the target.
     * @param cccId CCC code.
     * @param rxData Buffer filled with the data read.
     * @param rxLength Number of bytes to read.
     * @param timeout Timeout in milliseconds. Default: 1000.
     * @return true on success, false otherwise.
     */
    bool cccDirectRead(uint8_t targetAddr,
                       uint8_t cccId,
                       uint8_t *rxData,
                       uint16_t rxLength,
                       uint32_t timeout = 1000);

    // ------------------------------------------------------------------------
    // Internal utility helpers
    // ------------------------------------------------------------------------
    /**
     * @brief Swap the byte order of a 32-bit value.
     * @param x Value to convert.
     * @return Value with the byte order swapped.
     */
    static uint32_t bigToLittle32(uint32_t x);
    /**
     * @brief Extract the 48-bit PID from the 64-bit payload received during the DAA.
     * @param payload Raw ENTDAA payload.
     * @return 48-bit PID.
     */
    static uint64_t extractPid48FromEntdaaPayload(uint64_t payload);

#if defined(USE_HALV2_DRIVER)
    /**
     * @brief Convert a HAL status to the result code of the transfer functions.
     * @param hi3c HAL handle.
     * @param st HAL status.
     * @return 0 if st is HAL_OK, else the opposite of the last HAL error code
     *         (-1 if not available).
     */
    static int HAL_I3C_GetError(const hal_i3c_handle_t &hi3c, hal_status_t st = HAL_OK);
#endif

    // ------------------------------------------------------------------------
    // Clock helpers
    // ------------------------------------------------------------------------
    /**
     * @brief Get the kernel clock frequency of the I3C peripheral.
     * @return Frequency in Hz, 0 if not available.
     */
    uint32_t getPeripheralClockFreq() const;

#if defined(USE_HALV2_DRIVER)
    /**
     * @brief Compute the controller bus timing registers.
     * @param srcFreq Kernel clock frequency in Hz.
     * @param freq I3C push-pull frequency in Hz, 0 selects 1 MHz.
     * @param busType Bus type.
     * @param mixedBusOdFreq Open-drain frequency in Hz used on a mixed bus.
     * @param outCtrl Controller configuration filled with the timing.
     * @return true on success, false otherwise.
     */
    bool buildControllerTiming(uint32_t srcFreq,
                               uint32_t freq,
                               I3CBusType busType,
                               uint32_t mixedBusOdFreq,
                               hal_i3c_ctrl_config_t &outCtrl) ;
    /**
     * @brief Compute the target bus timing.
     * @param srcFreq Kernel clock frequency in Hz.
     * @param outTgt Target configuration filled with the timing.
     * @return true on success, false otherwise.
     */
    bool buildTargetTiming(uint32_t srcFreq, hal_i3c_tgt_config_t &outTgt) ;
#else
    /**
     * @brief Compute the controller bus timing, using the bus type and the
     *        open-drain frequency of the instance.
     * @param freq I3C push-pull frequency in Hz, 0 selects 1 MHz.
     * @param outCtrl Controller bus configuration filled with the timing.
     * @return true on success, false otherwise.
     */
    bool buildControllerTiming(uint32_t freq, LL_I3C_CtrlBusConfTypeDef &outCtrl) const;
    /**
     * @brief Compute the target bus timing.
     * @param outTgt Target bus configuration filled with the timing.
     * @return true on success, false otherwise.
     */
    bool buildTargetTiming(LL_I3C_TgtBusConfTypeDef &outTgt) const;
#endif

    // ------------------------------------------------------------------------
    // Irq helpers
    // ------------------------------------------------------------------------
    /**
     * @brief Enable the NVIC interrupts of the peripheral, if not already enabled.
     */
    void enableIRQs();
    /**
     * @brief Disable the NVIC interrupts of the peripheral, if enabled.
     */
    void disableIRQs();
    /**
     * @brief Register this instance as the owner of its peripheral, to dispatch
     *        the HAL callbacks and interrupts.
     */
    void registerInstanceOwner();
    /**
     * @brief Unregister this instance as the owner of its peripheral.
     */
    void unregisterInstanceOwner();

    /**
     * @brief Reset and disable the clock of the I3C peripheral.
     */
    void deinitClocks();
    /**
     * @brief Set the SDA and SCL pins in analog mode.
     */
    void deinitGPIO();

    // ------------------------------------------------------------------------
    // Internal state
    // ------------------------------------------------------------------------
    /** @brief Controller configuration given to begin(). */
    I3CControllerConfig _ctrlCfg{};
    /** @brief Role of the instance. */
    I3CRole _role = I3CRole::None;

    /** @brief true if an IBI has been received and not read yet. */
    volatile bool _ibiPending = false;
    /** @brief Last received IBI. */
    I3CControllerIbiInfo _lastIbi{};
    /** @brief Callback called when an IBI is received. */
    I3CIbiCallback _ibiCb = nullptr;
    /** @brief User pointer given to the IBI callback. */
    void *_ibiCbUser = nullptr;

    /** @brief true if a target event has been notified and not read yet. */
    volatile bool _targetEventPending = false;
    /** @brief Last notified target event identifier. */
    volatile uint32_t _lastTargetEventId = 0U;


    /** @brief HAL handle of the peripheral. */
#if defined(USE_HALV2_DRIVER)
    hal_i3c_handle_t _hi3c {};
#else
    I3C_HandleTypeDef _hi3c {};
#endif

    /** @brief true once the instance is initialized as controller or target. */
    bool _initialized = false;
    /** @brief I3C peripheral used by the instance. */
    I3C_TypeDef *_instance = nullptr;

    /** @brief Bus type. */
    I3CBusType _busType = I3CBusType::Pure;
    /** @brief Open-drain frequency in Hz used on a mixed bus. */
    uint32_t _mixedBusOdFreq = 1000000U;

    /** @brief true if the NVIC interrupts of the peripheral are enabled. */
    bool _irqEnabled = false;

    /**
     * @brief Maximum number of control words of a transfer (not used by the
     *        current implementation).
     */
    static constexpr uint32_t I3C_CTRL_WORDS_MAX = 2U;
    /** @brief Size of the scratch buffer used to send the CCC data. */
    static constexpr uint32_t I3C_CCC_TX_SCRATCH_MAX = 16U;

    /** @brief SDA pin. */
    PinName _sdaPin = digitalPinToPinName(I3C_SDA);
    /** @brief SCL pin. */
    PinName _sclPin = digitalPinToPinName(I3C_SCL);
};

// ============================================================================
// Global instances
// ============================================================================

/** @brief Default I3C instance. */
extern I3CBus I3C;

#endif
