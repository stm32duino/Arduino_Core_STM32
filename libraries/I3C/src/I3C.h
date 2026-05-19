#pragma once

#include "Arduino.h"

#if defined(I3C1_BASE) || defined(I3C2_BASE)

#include "stm32yyxx_util_i3c.h"

// ============================================================================
// Descriptors, configuration structures, and enums
// ============================================================================

struct I3CDiscoveredDevice {
  uint8_t  dynAddr = 0;            // 7-bit dynamic address
  uint8_t  staticAddr = 0;         // 7-bit static address if known, else 0
  uint8_t  bcr = 0;
  uint8_t  dcr = 0;
  uint64_t pid = 0;                // 48-bit PID
  uint64_t entdaaPayloadRaw = 0;   // full raw 64-bit payload from HAL DAA
  bool     fromDaa = false;
  bool     assignedBySetdasa = false;
  bool     matchedKnown = false;
};

struct I3CBusBeginConfig {
  bool    doRstact = false;
  bool    doRstdaa = true;
  bool    disableEvents = true;
  bool    doSetdasa = true;
  bool    doDaa = true;
  bool    retryDaaOnce = true;
  bool    allowHotJoinAfterInit = false;
  uint8_t firstAutoDynAddr = 0x10;
  bool    discoverUnknownAfterKnown = false;
};

struct I3CKnownDevice {
  uint64_t pid = 0;                // 48-bit PID in low bits if known, else 0
  uint8_t  staticAddr = 0;         // 7-bit static address, 0 if none
  uint8_t  preferredDynAddr = 0;   // 7-bit preferred dynamic address, 0 = auto
  bool     supportsSetaasa = false;
  bool     present = true;
};

enum class I3CRole : uint8_t {
  None,
  Controller,
  Target
};

struct I3CTargetConfig {
  uint8_t  identifier = 0;                  // DCR
  uint8_t  mipiIdentifier = 0;              // MIPI Instance ID (4 useful bits)

  bool     ctrlRoleRequest = false;
  bool     hotJoinRequest = false;
  bool     ibiRequest = false;
  bool     ibiPayload = false;

  uint32_t ibiPayloadSize = HAL_I3C_PAYLOAD_EMPTY;

  uint16_t maxReadDataSize = 0xFFFF;
  uint16_t maxWriteDataSize = 0xFFFF;

  bool     ctrlCapability = false;
  bool     groupAddrCapability = false;

  uint32_t dataTurnAroundDuration = HAL_I3C_TURNAROUND_TIME_TSCO_LESS_12NS;
  uint8_t  maxReadTurnAround = 0;
  uint32_t maxDataSpeed = HAL_I3C_GETMXDS_FORMAT_1;
  bool     maxSpeedLimitation = false;

  uint32_t handOffActivityState = HAL_I3C_HANDOFF_ACTIVITY_STATE_0;
  bool     handOffDelay = false;
  bool     pendingReadMDB = false;
};

typedef struct {
  bool     pending = false;
  uint32_t eventId = 0;
  uint8_t  sourceDa = 0;
  uint8_t  payloadSize = 0;
  uint32_t payloadRaw = 0;
  uint32_t timestampMs = 0;
} I3CControllerIbiInfo;

using I3CIbiCallback = void (*)(const I3CControllerIbiInfo &info, void *user);

enum class I3CBusType : uint8_t {
  Pure,
  Mixed
};

enum class I3CTransferType : uint8_t {
  I3C,    // private SDR transfer using I3C dynamic address
  I2C     // legacy I2C transfer using static 7-bit address
};

struct I3CControllerConfig {
  uint32_t rxFifoThreshold = HAL_I3C_RXFIFO_THRESHOLD_1_4;
  uint32_t txFifoThreshold = HAL_I3C_TXFIFO_THRESHOLD_1_4;
  uint32_t controlFifo     = HAL_I3C_CONTROLFIFO_DISABLE;
  uint32_t statusFifo      = HAL_I3C_STATUSFIFO_DISABLE;

  uint8_t  dynamicAddr     = 0U;
  uint8_t  stallTime       = 0x00U;

  bool     hotJoinAllowed  = false;
  bool     ackStall        = false;
  bool     cccStall        = false;
  bool     txStall         = false;
  bool     rxStall         = false;
  bool     highKeeperSDA   = false;
};

// ============================================================================
// I3CBus
// ============================================================================

class I3CBus {
  public:
    explicit I3CBus(I3C_TypeDef *inst = I3C1) : _instance(inst) {}

    // ------------------------------------------------------------------------
    // Controller initialization and bus configuration
    // ------------------------------------------------------------------------
    bool begin(pin_size_t sda,
               pin_size_t scl,
               uint32_t freq = 1000000U,
               I3CBusType type = I3CBusType::Pure,
               uint32_t mixedOdHz = 1000000U);

    bool begin(uint32_t freq = 1000000U,
               I3CBusType type = I3CBusType::Pure,
               uint32_t mixedOdHz = 1000000U);

    bool begin(pin_size_t sda,
               pin_size_t scl,
               uint32_t freq,
               I3CBusType type,
               uint32_t mixedOdHz,
               const I3CControllerConfig &ctrlCfg);

    bool begin(uint32_t freq,
               I3CBusType type,
               uint32_t mixedOdHz,
               const I3CControllerConfig &ctrlCfg);

    int setClock(uint32_t hz);

    void setBusType(I3CBusType type);
    I3CBusType getBusType() const;

    void setMixedBusOpenDrainFrequency(uint32_t hz);
    uint32_t getMixedBusOpenDrainFrequency() const;

    I3CRole getRole() const;
    bool isController() const;
    bool isTarget() const;

    // ------------------------------------------------------------------------
    // Default I3C controller transfers
    // ------------------------------------------------------------------------
    int write(uint8_t dynAddr,
              const uint8_t *buf,
              size_t len,
              uint32_t timeout = 1000U);

    int read(uint8_t dynAddr,
             uint8_t *buf,
             size_t len,
             uint32_t timeout = 1000U);

    int writeReg(uint8_t dynAddr,
                 uint8_t reg,
                 uint8_t value,
                 uint32_t timeout = 1000U);

    int readReg(uint8_t dynAddr,
                uint8_t reg,
                uint8_t &value,
                uint32_t timeout = 1000U);

    int writeRegBuffer(uint8_t dynAddr,
                       uint8_t reg,
                       const uint8_t *pData,
                       size_t len,
                       uint32_t timeout = 1000U);

    int readRegBuffer(uint8_t dynAddr,
                      uint8_t reg,
                      uint8_t *pData,
                      size_t len,
                      uint32_t timeout = 1000U);

    // ------------------------------------------------------------------------
    // Unified transfers with selectable transport kind
    // ------------------------------------------------------------------------
    int write(uint8_t addr,
              const uint8_t *buf,
              size_t len,
              I3CTransferType type,
              uint32_t timeout = 1000U);

    int read(uint8_t addr,
             uint8_t *buf,
             size_t len,
             I3CTransferType type,
             uint32_t timeout = 1000U);

    int writeReg(uint8_t addr,
                 uint8_t reg,
                 uint8_t value,
                 I3CTransferType type,
                 uint32_t timeout = 1000U);

    int readReg(uint8_t addr,
                uint8_t reg,
                uint8_t &value,
                I3CTransferType type,
                uint32_t timeout = 1000U);

    int writeRegBuffer(uint8_t addr,
                       uint8_t reg,
                       const uint8_t *pData,
                       size_t len,
                       I3CTransferType type,
                       uint32_t timeout = 1000U);

    int readRegBuffer(uint8_t addr,
                      uint8_t reg,
                      uint8_t *pData,
                      size_t len,
                      I3CTransferType type,
                      uint32_t timeout = 1000U);

    // ------------------------------------------------------------------------
    // Legacy I2C transfers on mixed I3C bus
    // ------------------------------------------------------------------------
    int i2cWrite(uint8_t staticAddr,
                 const uint8_t *buf,
                 size_t len,
                 uint32_t timeout = 1000U);

    int i2cRead(uint8_t staticAddr,
                uint8_t *buf,
                size_t len,
                uint32_t timeout = 1000U);

    int i2cWriteRead(uint8_t staticAddr,
                     const uint8_t *txBuf,
                     size_t txLen,
                     uint8_t *rxBuf,
                     size_t rxLen,
                     uint32_t timeout = 1000U);

    int i2cWriteReg(uint8_t staticAddr,
                    uint8_t reg,
                    uint8_t value,
                    uint32_t timeout = 1000U);

    int i2cReadReg(uint8_t staticAddr,
                   uint8_t reg,
                   uint8_t &value,
                   uint32_t timeout = 1000U);

    int i2cWriteRegBuffer(uint8_t staticAddr,
                          uint8_t reg,
                          const uint8_t *pData,
                          size_t len,
                          uint32_t timeout = 1000U);

    int i2cReadRegBuffer(uint8_t staticAddr,
                         uint8_t reg,
                         uint8_t *pData,
                         size_t len,
                         uint32_t timeout = 1000U);

    int scanI2CDevices(uint8_t *addrs,
                       size_t maxAddrs,
                       size_t *foundCount,
                       uint32_t trials = 2U,
                       uint32_t timeout = 10U);

    // ------------------------------------------------------------------------
    // Device readiness checks
    // ------------------------------------------------------------------------
    bool isI2CDeviceReady(uint8_t staticAddr,
                          uint32_t trials = 3U,
                          uint32_t timeout = 1000U);

    bool isI3CDeviceReady(uint8_t dynAddr,
                          uint32_t trials = 3U,
                          uint32_t timeout = 1000U);

    // ------------------------------------------------------------------------
    // CCC broadcast & direct commands
    // ------------------------------------------------------------------------
    bool resetDynamicAddresses();
    bool disableEvents(const uint8_t *pCCCData, uint16_t length);
    bool assignAllStaticAsDynamic();
    bool assignDynamicAddress(uint8_t staticAddr, uint8_t dynAddr);

    bool getbcr(uint8_t dynAddr, uint8_t &bcr, uint32_t timeout = 1000U);
    bool getdcr(uint8_t dynAddr, uint8_t &dcr, uint32_t timeout = 1000U);
    bool getpid(uint8_t dynAddr, uint64_t &pid, uint32_t timeout = 1000U);

    // ------------------------------------------------------------------------
    // Discovery and dynamic address assignment
    // ------------------------------------------------------------------------
    int assignDynamicAddresses(I3CDiscoveredDevice *devices,
                               size_t maxDevices,
                               uint8_t firstDynAddr = 0x10U,
                               uint32_t timeout = 1000U);

    int discover(const I3CBusBeginConfig &cfg,
                 const I3CKnownDevice *knownDevices,
                 size_t numKnownDevices,
                 I3CDiscoveredDevice *discovered,
                 size_t maxDiscovered,
                 size_t *outCount);

    // Unknown I3C devices only
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

    // Known devices + optional unknown discovery
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
    bool beginTarget(pin_size_t sda, pin_size_t scl, const I3CTargetConfig &cfg);
    bool beginTarget(const I3CTargetConfig &cfg);
    int configureTarget(const I3CTargetConfig &cfg);

    bool hasAddress() const;
    uint8_t address() const;

    // ------------------------------------------------------------------------
    // Target-side private communication
    // ------------------------------------------------------------------------
    int send(uint8_t *buf,
             uint16_t len,
             uint32_t timeout = 1000U);

    int receive(uint8_t *buf,
                uint16_t len,
                uint32_t timeout = 1000U);

    // ------------------------------------------------------------------------
    // Target-side non-private requests / events
    // ------------------------------------------------------------------------
    int sendIbi(const uint8_t *payload,
                uint8_t payloadSize,
                uint32_t timeout = 1000U);

    int enableTargetEvents(I3C_XferTypeDef *pXferData,
                           uint32_t interruptMask);

    int disableTargetEvents(uint32_t interruptMask);

    bool setEvents(uint8_t dynAddr,
                  bool enable,
                  uint8_t events,
                  uint32_t timeout = 1000U);

    bool hasTargetEvent() const;
    bool readTargetEvent(uint32_t &eventId);

    // ------------------------------------------------------------------------
    // Controller-side IBI support
    // ------------------------------------------------------------------------
    int configureControllerDevice(uint8_t deviceIndex,
                                  uint8_t dynAddr,
                                  bool ibiAck,
                                  bool ibiPayload,
                                  bool ctrlRoleReqAck = false,
                                  bool stopTransfer = false);

    int enableIbi(uint8_t deviceIndex,
                  uint8_t dynAddr,
                  bool withPayload,
                  bool stopTransfer = false,
                  uint32_t timeout = 1000U);

    int enableControllerEvents(uint32_t interruptMask = HAL_I3C_IT_IBIIE);
    int disableControllerEvents(uint32_t interruptMask = HAL_I3C_IT_IBIIE);

    bool hasIbi() const;
    bool readIbi(I3CControllerIbiInfo &out);
    bool peekIbi(I3CControllerIbiInfo &out) const;

    void onIbi(I3CIbiCallback cb, void *user = nullptr);

    // ------------------------------------------------------------------------
    // Internal HAL bridge
    // ------------------------------------------------------------------------
    void handleHalNotify(uint32_t eventId);

    I3C_HandleTypeDef *halHandle()
    {
      return &_hi3c;
    }

  private:
    enum class I3CAddrState : uint8_t {
      Free,
      Reserved,
      I2CDevice,
      I3CDevice
    };

    // ------------------------------------------------------------------------
    // Low-level initialization
    // ------------------------------------------------------------------------
    bool initClocks();
    bool initGPIO();

    // ------------------------------------------------------------------------
    // Address map helpers
    // ------------------------------------------------------------------------
    I3CAddrState _addrMap[128] {};

    void initAddressMap();
    bool isValidUsableDynamicAddr(uint8_t addr) const;
    bool isValidI2CStaticAddr(uint8_t addr) const;
    bool isAddrFree(uint8_t addr) const;
    void markAddrUsed(uint8_t addr);
    void markI2CAddrUsed(uint8_t addr);
    void markAddrFree(uint8_t addr);
    uint8_t allocNextDynamicAddr(uint8_t start) const;

    // ------------------------------------------------------------------------
    // Bus sequencing helpers
    // ------------------------------------------------------------------------
    bool disecAll();
    bool enecHotJoin();
    bool rstactPeripheralOnly();
    bool rstactWholeTarget();

    int assignKnownDevices(const I3CKnownDevice *knownDevices,
                           size_t numKnownDevices,
                           I3CDiscoveredDevice *discovered,
                           size_t maxDiscovered,
                           size_t &count,
                           bool &needAasa,
                           bool &needDaa);

    int doDaaPhase(const I3CBusBeginConfig &cfg,
                   const I3CKnownDevice *knownDevices,
                   size_t numKnownDevices,
                   I3CDiscoveredDevice *discovered,
                   size_t maxDiscovered,
                   size_t &count);

    int configBusDevicesFromDiscovery(const I3CDiscoveredDevice *discovered, size_t count);

    // ------------------------------------------------------------------------
    // Low-level CCC helpers
    // ------------------------------------------------------------------------
    bool cccBroadcastWrite(uint8_t cccId,
                          const uint8_t *data,
                          uint16_t length,
                          bool withDefByte,
                          uint32_t timeout = 1000U);

    bool cccDirectWrite(uint8_t targetAddr,
                       uint8_t cccId,
                       const uint8_t *data,
                       uint16_t length,
                       bool withDefByte,
                       uint32_t timeout = 1000U);

    bool cccDirectRead(uint8_t targetAddr,
                      uint8_t cccId,
                      uint8_t *rxData,
                      uint16_t rxLength,
                      uint32_t timeout = 1000);

    // ------------------------------------------------------------------------
    // Internal utility helpers
    // ------------------------------------------------------------------------
    static uint32_t bigToLittle32(uint32_t x);
    static uint64_t extractPid48FromEntdaaPayload(uint64_t payload);

    // ------------------------------------------------------------------------
    // Internal state
    // ------------------------------------------------------------------------
    I3CControllerConfig _ctrlCfg{};
    I3CRole _role = I3CRole::None;

    volatile bool _ibiPending = false;
    I3CControllerIbiInfo _lastIbi{};
    I3CIbiCallback _ibiCb = nullptr;
    void *_ibiCbUser = nullptr;

    volatile bool _targetEventPending = false;
    volatile uint32_t _lastTargetEventId = 0U;

    I3C_HandleTypeDef _hi3c{};
    bool _initialized = false;
    I3C_TypeDef *_instance = nullptr;

    I3CBusType _busType = I3CBusType::Pure;
    uint32_t _mixedBusOdFreq = 1000000U;

    PinName _sdaPin = digitalPinToPinName(I3C_SDA);
    PinName _sclPin = digitalPinToPinName(I3C_SCL);
};

// ============================================================================
// Global instances
// ============================================================================

#if defined(I3C1)
  extern I3CBus I3C1Bus;
#endif

#if defined(I3C2)
  extern I3CBus I3C2Bus;
#endif

#endif
