/*
  SPI Master

  This example implements a SPI Master device for the SPI Slave example.
  The data is transmitted to the SPI Slave and its response received back.

  Every 1000ms the LED state toggles and the latest received data is printed
  to the Serial port

  The circuit:
   * A LED to show a heartbeat signal
   * CS - to digital pin PA4 (SS pin)
   * SCK - to digital pin PA5 (SCK pin)
   * MISO - to digital pin PA6 (MISO pin)
   * MOSI - to digital pin PA7 (MOSI pin)

  Default SPI pin definitions can be found at variants/STM32XXxx/<VARIANT>/variant_generic.h

  created 29 Dec 2021
  by brainelectronics
*/

#include <SPI.h>

// PC13 on the Bluepill board
#define DEBUG_LED         PC13

// comment this line to disable debug output on Serial
#define DEBUG_OUTPUT

// amount of data to be sent to the SPI Slave device
#define BUFFER_SIZE       8

uint8_t TX_Buffer[BUFFER_SIZE] = {0};
uint8_t RX_Buffer[BUFFER_SIZE] = {0};
uint8_t up_counter = 0;   //< data to be transmitted

uint32_t prevTime = 0;    //< previous timestamp of printing received data
uint32_t interval = 1000; //< [ms] interval at which to print received data

spi_t _spi;

void setup() {
  // put your setup code here, to run once:
  pinMode(DEBUG_LED, OUTPUT);

  // setup serial communication at 115200 baud
  Serial.begin(115200);

  // setup SPI interface
  setup_spi();
}

void setup_spi() {
  uint32_t clk = SPI_SPEED_CLOCK_DEFAULT;

  // communicating at full clock speed might not work
  // check the documentation at system/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c
  clk = spi_getClkFreq(&_spi) / SPI_CLOCK_DIV16;

#ifdef DEBUG_OUTPUT
  Serial.printf("PCLK: %d Hz\n", HAL_RCC_GetPCLK2Freq());
  // e.g. 48.000.000 Hz if running on the internal oscillator
  Serial.printf("SPI CLK: %d Hz\n", clk);
  // becomes 3.000.000 Hz in case PCLK is 48MHz and SPI_CLOCK_DIV16 is used
#endif

  // set the default CS pin as an output
  pinMode(PIN_SPI_SS, OUTPUT);

  _spi.pin_mosi = digitalPinToPinName(PIN_SPI_MOSI);
  _spi.pin_miso = digitalPinToPinName(PIN_SPI_MISO);
  _spi.pin_sclk = digitalPinToPinName(PIN_SPI_SCK);
  _spi.pin_ssel = NC;      // in send_and_receive_data function

  _spi.mode = SPI_MASTER;  //< master mode

  _spi.handle.State = HAL_SPI_STATE_RESET;

  spi_init(&_spi, clk, SPI_MODE_0, MSBFIRST);

#ifdef DEBUG_OUTPUT
  Serial.printf("SPI State: %d\n", _spi.handle.State);
  // should be in state "1": Peripheral Initialized and ready for use
#endif
}

void loop() {
  uint32_t now = millis();

  if (now > (prevTime + interval))
  {
    // save the last time the data has been printed
    prevTime = now;

    // toggle the LED state
    digitalWrite(DEBUG_LED, !digitalRead(DEBUG_LED));

#ifdef DEBUG_OUTPUT
    Serial.printf("HAL_SPI_GetError: %d\n", HAL_SPI_GetError(&(_spi.handle)));
    Serial.printf("SPI State: %d\n", _spi.handle.State);
#endif

    // increment counter. This value will be sent to the SPI slave device
    up_counter++;

    // reset value to zero, just to be save
    if (up_counter >= 255) {
      up_counter = 0;
    }

    // to only send data to the slave device use this function
    // send_data_to_slave(up_counter);

    // to send data and read the slave device response use this function
    send_and_receive_data(up_counter);
  }
}

void send_data_to_slave(uint8_t data) {
  uint8_t tmp_data_rx = 0;

  // take the SS pin low to select the chip
  digitalWrite(PIN_SPI_SS, LOW);

  // transfer the given data 8 times in a row to slave -> Slave BUFFER_SIZE = 8
  // [1, 1, 1, 1, 1, 1, 1, 1]
  for (uint8_t i = 0; i < 8; i++)
  {
    spi_transfer(&_spi,
                 &data,
                 &tmp_data_rx,
                 sizeof(uint8_t),
                 SPI_TRANSFER_TIMEOUT,
                 SPI_TRANSMITONLY);
  }

  // take the SS pin high to de-select the chip
  digitalWrite(PIN_SPI_SS, HIGH);
}

void send_and_receive_data(uint8_t data) {
  uint8_t tmp_data_rx = 0;
  uint8_t tmp_data_tx = 0;

  for (uint8_t i = 0; i < BUFFER_SIZE; i++)
  {
    TX_Buffer[i] = data + i;
  }
  // e.g. [1, 2, 3, 4, 5, 6, 7, 8] if data = 1

  Serial.print("Send data to Slave: ");
  for (uint8_t i = 0; i < BUFFER_SIZE; i++)
  {
    Serial.printf("%d, ", TX_Buffer[i]);
  }
  Serial.println();

  // take the CS pin low to select the Slave device
  digitalWrite(PIN_SPI_SS, LOW);

  for (uint8_t i = 0; i < BUFFER_SIZE; i++)
  {
    tmp_data_tx = TX_Buffer[i];
    spi_transfer(&_spi,
                 &tmp_data_tx,
                 &tmp_data_rx,
                 sizeof(uint8_t),
                 SPI_TRANSFER_TIMEOUT,
                 SPI_TRANSMITONLY);
  }

  // Serial print on slave requires approx. 1 ms
  // wait for that amount of time until dummy data is sent to the slave in
  // order to provide a CLK signal for the response of the slave device
#ifdef DEBUG_OUTPUT
  delay(2);
#else
  delay(1);
#endif

  tmp_data_tx = 0x0; // dummy data
  for (uint8_t i = 0; i < BUFFER_SIZE; i++)
  {
    spi_transfer(&_spi,
                 &tmp_data_tx,
                 &tmp_data_rx,
                 sizeof(uint8_t),
                 SPI_TRANSFER_TIMEOUT,
                 SPI_TRANSMITRECEIVE);
    RX_Buffer[i] = tmp_data_rx;
  }

  // take the SS pin high to de-select the slave device again
  digitalWrite(PIN_SPI_SS, HIGH);

  Serial.print("Received data from Slave: ");
  for (uint8_t i = 0; i < BUFFER_SIZE; i++)
  {
    Serial.printf("%d, ", RX_Buffer[i]);
    RX_Buffer[i] = 0; // clear buffer entry
  }
  // e.g. [2, 3, 4, 5, 6, 7, 8, 9] if data = 1
  Serial.println();
}
