# I3C

## Introduction

The I3C library gives access to the I3C peripheral (MIPI I3C) of the STM32
series that provide it (the core enables it for STM32C5, STM32H5 and STM32U3). The
peripheral can work as a **controller** or as a **target**, on a pure I3C bus or
on a mixed bus with legacy I2C devices.

The library defines the `I3CBus` class and a predefined instance named `I3C`.
Everything is only available when the device has an I3C peripheral
(`I3C1_BASE` or `I3C2_BASE`).

```Arduino
#include <I3C.h>
```

Conventions:

* Addresses are 7-bit addresses.
* Timeouts are in milliseconds (default: 1000).
* Transfer functions return `0` on success and a negative value on error: `-1`
  if the arguments are invalid or the bus is not initialized in the expected
  role, otherwise the opposite of the HAL error code.

The default pins are `I3C_SDA` and `I3C_SCL`. SDA and SCL must belong to the
same I3C peripheral.

## Controller

### Initialization

```Arduino
#include <I3C.h>

I3CDiscoveredDevice devices[8];

void setup() {
  if (!I3C.begin(I3C_SDA, I3C_SCL, 1000000U)) {
    while (1) {}
  }

  size_t found = 0;
  I3C.discover(devices, 8, &found);   // assign dynamic addresses (DAA)

  uint8_t value;
  for (size_t i = 0; i < found; i++) {
    I3C.readReg(devices[i].dynAddr, 0x0F, value);
  }
}
```

| Method | Description |
| ------ | ----------- |
| `bool begin(uint32_t freq = 1000000, I3CBusType type = I3CBusType::Pure, uint32_t mixedOdHz = 1000000)` | Starts the controller on the default pins. `freq` is the push-pull frequency in Hz. |
| `bool begin(pin_size_t sda, pin_size_t scl, uint32_t freq = 1000000, I3CBusType type = I3CBusType::Pure, uint32_t mixedOdHz = 1000000)` | Starts the controller on the given pins. |
| `bool begin(..., const I3CControllerConfig &ctrlCfg)` | Same as above with a controller configuration (FIFO thresholds, stall options, ...). Both pin variants exist. |
| `bool setClock(uint32_t hz)` | Changes the push-pull frequency. |
| `void setBusType(I3CBusType type)` / `I3CBusType getBusType()` | Sets or gets the bus type for the next timing computation: `I3CBusType::Pure` or `I3CBusType::Mixed`. |
| `void setMixedBusOpenDrainFrequency(uint32_t hz)` / `uint32_t getMixedBusOpenDrainFrequency()` | Sets or gets the open-drain frequency of a mixed bus. |
| `I3CRole getRole()` | `I3CRole::None`, `I3CRole::Controller` or `I3CRole::Target`. |
| `bool isController()` / `bool isTarget()` | Role of the instance. |
| `bool flushAllFifos()` | Flushes all the FIFOs of the peripheral. |
| `void end()` | Disables the peripheral, its pins and its clock. |

### Transfers to I3C targets

Private SDR transfers using the dynamic address of the target.

| Method | Description |
| ------ | ----------- |
| `int write(uint8_t dynAddr, const uint8_t *buf, size_t len, uint32_t timeout = 1000)` | Writes `len` bytes (`len` must not be 0). |
| `int read(uint8_t dynAddr, uint8_t *buf, size_t len, uint32_t timeout = 1000)` | Reads `len` bytes. |
| `int writeReg(uint8_t dynAddr, uint8_t reg, uint8_t value, uint32_t timeout = 1000)` | Writes a register. |
| `int readReg(uint8_t dynAddr, uint8_t reg, uint8_t &value, uint32_t timeout = 1000)` | Reads a register. |
| `int writeRegBuffer(uint8_t dynAddr, uint8_t reg, const uint8_t *pData, size_t len, uint32_t timeout = 1000)` | Writes consecutive registers. |
| `int readRegBuffer(uint8_t dynAddr, uint8_t reg, uint8_t *pData, size_t len, uint32_t timeout = 1000)` | Reads consecutive registers. |

### Unified transfers

The same functions exist with an extra `I3CTransferType type` parameter before
the timeout, to select the transport at run time: `I3CTransferType::I3C`
(`addr` is the dynamic address) or `I3CTransferType::I2C` (`addr` is the static
address). This allows a driver to talk to a device whichever the bus it is on.

### Legacy I2C devices (mixed bus)

Available only in controller mode, when the bus type is `I3CBusType::Mixed`.
Static addresses range from 0x08 to 0x77.

| Method | Description |
| ------ | ----------- |
| `int i2cWrite(uint8_t staticAddr, const uint8_t *buf, size_t len, uint32_t timeout = 1000)` | Writes data. |
| `int i2cRead(uint8_t staticAddr, uint8_t *buf, size_t len, uint32_t timeout = 1000)` | Reads data. |
| `int i2cWriteRead(uint8_t staticAddr, const uint8_t *txBuf, size_t txLen, uint8_t *rxBuf, size_t rxLen, uint32_t timeout = 1000)` | Writes then reads with a repeated start. |
| `int i2cWriteReg(...)` / `int i2cReadReg(...)` | Writes or reads one register. |
| `int i2cWriteRegBuffer(...)` / `int i2cReadRegBuffer(...)` | Writes or reads consecutive registers. |
| `int scanI2CDevices(uint8_t *addrs, size_t maxAddrs, size_t *foundCount, uint32_t trials = 2, uint32_t timeout = 10)` | Scans the legacy I2C devices and marks their addresses as used. |

### Device readiness

| Method | Description |
| ------ | ----------- |
| `bool isI3CDeviceReady(uint8_t dynAddr, uint32_t trials = 3, uint32_t timeout = 10)` | Checks that an I3C device acknowledges its dynamic address. |
| `bool isI2CDeviceReady(uint8_t staticAddr, uint32_t trials = 3, uint32_t timeout = 10)` | Checks that an I2C device acknowledges its address. |

### Discovery and dynamic addresses

| Method | Description |
| ------ | ----------- |
| `int discover(I3CDiscoveredDevice *discovered, size_t maxDiscovered, size_t *outCount, uint8_t firstDynAddr = 0x10)` | Resets the dynamic addresses, then assigns them to all the devices with the DAA (ENTDAA). |
| `int discover(const I3CKnownDevice *knownDevices, size_t numKnownDevices, I3CDiscoveredDevice *discovered, size_t maxDiscovered, size_t *outCount, bool discoverUnknown = true, uint8_t firstDynAddr = 0x10)` | Assigns the known devices (SETDASA), then optionally discovers the unknown ones. |
| `int discover(const I3CBusBeginConfig &cfg, const I3CKnownDevice *knownDevices, size_t numKnownDevices, I3CDiscoveredDevice *discovered, size_t maxDiscovered, size_t *outCount)` | Runs the full initialization sequence selected by `cfg`. |
| `int assignDynamicAddresses(I3CDiscoveredDevice *devices, size_t maxDevices, uint8_t firstDynAddr = 0x10, uint32_t timeout = 1000)` | Runs the DAA only. Returns the number of devices found, or a negative value on error. |

`discover()` returns `0` on success and stores the number of devices in `outCount`.

Descriptions used by these functions:

* `I3CDiscoveredDevice`: `dynAddr`, `staticAddr`, `bcr`, `dcr`, `pid` (48 bits),
  and the flags `fromDaa`, `assignedBySetdasa` and `matchedKnown`.
* `I3CKnownDevice`: `pid`, `staticAddr`, `preferredDynAddr`, `supportsSetaasa`
  and `present`.
* `I3CBusBeginConfig`: selects the steps of the sequence (`doRstact`,
  `doRstdaa`, `disableEvents`, `doSetdasa`, `doDaa`, `retryDaaOnce`,
  `allowHotJoinAfterInit`, `firstAutoDynAddr`, `discoverUnknownAfterKnown`).

### Common command codes (CCC)

| Method | Description |
| ------ | ----------- |
| `bool resetDynamicAddresses()` | RSTDAA broadcast. |
| `bool disableEvents(const uint8_t *pCCCData, uint16_t length)` | DISEC broadcast. |
| `bool assignAllStaticAsDynamic()` | SETAASA broadcast. |
| `bool assignDynamicAddress(uint8_t staticAddr, uint8_t dynAddr)` | SETDASA direct command. |
| `bool getbcr(uint8_t dynAddr, uint8_t &bcr, uint32_t timeout = 1000)` | GETBCR. |
| `bool getdcr(uint8_t dynAddr, uint8_t &dcr, uint32_t timeout = 1000)` | GETDCR. |
| `bool getpid(uint8_t dynAddr, uint64_t &pid, uint32_t timeout = 1000)` | GETPID. |
| `bool setEvents(uint8_t dynAddr, bool enable, uint8_t events, uint32_t timeout = 1000)` | ENEC/DISEC direct command. `events`: `0x01` In-Band Interrupt, `0x02` controller role request, `0x08` Hot-Join. |

### In-Band Interrupts (IBI)

| Method | Description |
| ------ | ----------- |
| `int configureControllerDevice(uint8_t deviceIndex, uint8_t dynAddr, bool ibiAck, bool ibiPayload, bool ctrlRoleReqAck = false, bool stopTransfer = false)` | Configures how the controller handles the requests of a target. `deviceIndex` is from 1 to 4. |
| `int enableIbi(uint8_t deviceIndex, uint8_t dynAddr, bool withPayload, bool stopTransfer = false, uint32_t timeout = 1000)` | Configures the controller and enables the IBI event on the target. |
| `int enableControllerEvents(uint32_t interruptMask = LL_I3C_IER_IBIIE)` / `int disableControllerEvents(...)` | Enables or disables the controller event notifications. |
| `bool hasIbi()` | `true` if an IBI was received and not read yet. |
| `bool readIbi(I3CControllerIbiInfo &out)` | Reads and clears the last IBI. |
| `bool peekIbi(I3CControllerIbiInfo &out)` | Reads the last IBI without clearing it. |
| `void onIbi(I3CIbiCallback cb, void *user = nullptr)` | Registers a callback, `NULL` to unregister. |

`I3CControllerIbiInfo` contains `pending`, `eventId`, `sourceDa`, `payloadSize`,
`payloadRaw` and `timestampMs`.

> [!NOTE]
> The callback registered with `onIbi()` is called from the interrupt context.

## Target

```Arduino
#include <I3C.h>

uint8_t rxBuf[16];

void setup() {
  I3CTargetConfig cfg{};
  cfg.identifier = 0x62;      // DCR
  cfg.mipiIdentifier = 0x1;

  if (!I3C.beginTarget(I3C_SDA, I3C_SCL, cfg)) {
    while (1) {}
  }

  while (!I3C.hasAddress()) {   // wait for the controller to assign an address
    delay(10);
  }

  I3C.receive(rxBuf, sizeof(rxBuf), 10000);
}
```

| Method | Description |
| ------ | ----------- |
| `bool beginTarget(const I3CTargetConfig &cfg)` | Starts the target on the default pins. |
| `bool beginTarget(pin_size_t sda, pin_size_t scl, const I3CTargetConfig &cfg)` | Starts the target on the given pins. |
| `int configureTarget(const I3CTargetConfig &cfg)` | Applies a target configuration. |
| `bool hasAddress()` / `uint8_t address()` | Tells whether the controller assigned a dynamic address, and returns it (`0` if none). |
| `int send(uint8_t *buf, uint16_t len, uint32_t timeout = 1000)` | Sends data to the controller. |
| `int receive(uint8_t *buf, uint16_t len, uint32_t timeout = 1000)` | Receives data from the controller. |
| `int sendIbi(const uint8_t *payload, uint8_t payloadSize, uint32_t timeout = 1000)` | Requests an IBI. |
| `int enableTargetEvents(const I3CTargetEventConfig &cfg, uint32_t interruptMask)` / `int disableTargetEvents(uint32_t interruptMask)` | Enables or disables the notification of the target events. |
| `bool hasTargetEvent()` | `true` if an event was notified and not read yet. |
| `bool readTargetEvent(uint32_t &eventId)` | Reads and clears the last event. |
| `bool getTargetCccInfo(uint32_t eventId, I3CTargetCccInfo &out)` | Gets the content of an ENEC/DISEC CCC received by the target. |

`I3CTargetConfig` sets, among others, the DCR (`identifier`), the MIPI instance
ID (`mipiIdentifier`), the requests the target can raise (`hotJoinRequest`,
`ibiRequest`, `ibiPayload`, `ctrlRoleRequest`) and the maximum read and write
sizes.

## Examples

The library provides these examples: `BasicBegin`, `ScanBus`, `DeviceReady`,
`Controller_Target` (`ControllerWrite` and `TargetReceive`), `TargetIBI` and
`TargetNotifications` (each with a `Controller` and a `Target` sketch).
