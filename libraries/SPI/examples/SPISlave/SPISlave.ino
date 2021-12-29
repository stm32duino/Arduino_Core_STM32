/*
  SPI Slave

  This example implements a SPI Slave device for the SPI Master example.
  The data is received from the SPI Master, incremented by one and sent back.

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

// amount of data being sent by the SPI Master device
#define BUFFER_SIZE       8

uint8_t RX_Buffer[BUFFER_SIZE] = {0};

uint32_t prevTime = 0;    //< previous timestamp of printing received data
uint32_t interval = 1000; //< [ms] interval at which to print received data

volatile uint32_t tmpCounterRx = 0, tmpCounterTx = 0;

spi_t _spi;

void setup() {
  // put your setup code here, to run once:
  pinMode(DEBUG_LED, OUTPUT);

  // setup serial communication at 115200 baud
  Serial.begin(115200);

  // wait for 1 second in order to let the Master be ready before the slave
  delay(1000);

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

  // set the default CS pin as an input
  pinMode(PIN_SPI_SS, INPUT);

  _spi.pin_mosi = digitalPinToPinName(PIN_SPI_MOSI);
  _spi.pin_miso = digitalPinToPinName(PIN_SPI_MISO);
  _spi.pin_sclk = digitalPinToPinName(PIN_SPI_SCK);
  _spi.pin_ssel = NC;       // set later manually

  _spi.mode = SPI_SLAVE;    //< slave mode

  _spi.handle.State = HAL_SPI_STATE_RESET;

  spi_init(&_spi, clk, SPI_MODE_0, MSBFIRST);

#ifdef DEBUG_OUTPUT
  Serial.printf("SPI State: %d\n", _spi.handle.State);
  // should be in state "1": Peripheral Initialized and ready for use
#endif

  // attach an interrupt as last step to avoid calls before a full SPI setup

  // to receive only data from a Master, use the "receive_data" function
  // attachInterrupt(PIN_SPI_SS, receive_data, FALLING);

  // to receive data and transmit a response back to the Master use this
  attachInterrupt(PIN_SPI_SS, receive_and_respond_data, FALLING);
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
    Serial.printf("RX Counter: %d\n", tmpCounterRx);
    Serial.printf("TX Counter: %d\n", tmpCounterTx);
#endif

    // print the data in the received buffer in DEC format
    for (uint8_t i = 0; i < BUFFER_SIZE; i++)
    {
      Serial.printf("%d, ", RX_Buffer[i]);
      RX_Buffer[i] = 0; // clear buffer entry
    }
    Serial.println();
  }
}

void receive_data()
{
  // put received data from SPI into the RX_Buffer
  // return from function if no data is received within 10 ticks (10 ms)
  HAL_SPI_Receive(&(_spi.handle), RX_Buffer, sizeof(RX_Buffer), 10);
  tmpCounterRx++;

  // this is for demo purpose only, try to keep IRQ functions short and quick
#ifdef DEBUG_OUTPUT
  // print received data directly after receiving it
  for (uint8_t i = 0; i < BUFFER_SIZE; i++)
  {
    Serial.printf("%d, ", RX_Buffer[i]);
  }
  Serial.println();
#endif
}

void receive_and_respond_data()
{
  // put received data from SPI into the RX_Buffer
  // return from function if no data is received within 10 ticks (10 ms)
  HAL_SPI_Receive(&(_spi.handle), RX_Buffer, sizeof(RX_Buffer), 10);
  tmpCounterRx++;
  // e.g. [1, 2, 3, 4, 5, 6, 7, 8]

  // response data shall be available as soon as possible
  // avoid long intermediate processing or other functions
  uint8_t TX_Buffer[BUFFER_SIZE] = {0};
  for (uint8_t i = 0; i < BUFFER_SIZE; i++)
  {
    // create response message, which is the received data + 1
    TX_Buffer[i] = RX_Buffer[i] + 1;
  }
  // e.g. [2, 3, 4, 5, 6, 7, 8, 9]

  // send response as the data of the TX_Buffer to the SPI Master
  // return from function within 10 ticks (10 ms)
  HAL_SPI_Transmit(&(_spi.handle), TX_Buffer, sizeof(TX_Buffer), 10);
  tmpCounterTx++;
}
