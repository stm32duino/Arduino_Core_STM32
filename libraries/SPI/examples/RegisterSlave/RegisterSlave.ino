/* 
 *  This code demonstrates register-based SPI slave support in the stm32 arduino library.
 *  An example python script is included to show the master side running on a RPi.
 *  Since this is a software implementation of a SPI slave the max data rate will be
 *  significantly slower than a typical hardware-based SPI slave.  I have found 100kHz 
 *  to be a reliable max clock speed.
 *  
 *  You must install STM32duino FreeRTOS library (Sketch -> Include Library -> Manage Libraries)
 *  
 * This code was tested on a NUCLEO-F401RE dev board using the Arduino IDE.
 *   Set Board to Nucleo-64 and board number to F401RE
 *   Set USART support to Enable (generic Serial)
 *   Set USB support to None
 *   Upload method STM32CubeProgrammer (SWD) -> Requires installing STM32_Programmer_CLI.exe and adding it to your PATH
 *   Optimize for smallest
 *
 *  The following pins should be connected to the corresponding pins on the master
 *     PA4 - NSS
 *     PA5 - SCK
 *     PA6 - MISO
 *     PA7 - MOSI
 *     GND - GND
 *
 *  In this example we implement a register-based SPI slave.   Twenty 16-bit registers  
 *  (addressed 0 through 19) are implemented. All registers are read/write except as noted.
 *  The following registers have special functions:
 *     Address      Function
 *     -------      --------
 *     0            Returns the elapsed time in millis (read only)
 *     1            Returns the state of the blue User button on the Nucleo (read only)
 *     10           The LSB controls a GPIO on D4
 *     11           Returns the inverse of the value written 
 *
 *  the remaining registers simply read back whatever value was written.
  */
#include <STM32FreeRTOS.h>
//#define SPI_TRANSFER_TIMEOUT HAL_MAX_DELAY // Disable SPI timeouts
#include <SPI.h>

#define NUM_REG     20
#define DEBUG_GPIO  D4

// USE TASK NOTIFICATION INSTEAD OF SEMAPHORE FOR SPEED
/* Store the handle of the task that will be notified when the ISR fires */
static TaskHandle_t xTaskToNotify = NULL;

// Shadow storage for 16 bit register values
uint16_t Registers[NUM_REG];  

// Globals used by ISRs
volatile int xTaskErr = 0;
volatile int CatchupCnt = 0;


void SPI_ISR() {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;  

  // At this point xTaskToNotify should not be NULL 
  // If this happens it means we are falling behind. 
  // Increment an error count so the main task can take action to get back in sync
  if (xTaskToNotify == NULL)
  {
    xTaskErr++;
    return;
  }

  // Signal SPI thread  
  vTaskNotifyGiveFromISR( xTaskToNotify, &xHigherPriorityTaskWoken ); 

  xTaskToNotify = NULL;  

  /* If xHigherPriorityTaskWoken is now set to pdTRUE then a context switch  
   should be performed to ensure the interrupt returns directly to the highest  
   priority task. The macro used for this purpose is dependent on the port in  
   use and may be called portEND_SWITCHING_ISR(). */  
  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );  
}

// Handle the 3-byte transaction from master
//  *read - True for read transactions, False for writes
//  *address - Returns the register address
//  *value - returns the value sent by a write
// Returns false on error.  
bool process_transaction(bool *read, uint8_t *address, uint16_t *value) {
  uint8_t rx, tx;

  // Read the first byte from master to get the address and read/write bit
  tx = 0xBB; // Send dummy 0xBB since the master will ignore the first byte we send
  if (!SPI.read_write_byte(tx, &rx)) { 
    return(false);
  }

  *read = (rx & 0x80) == 0x80;
  *address = rx & 0x7F;
  if (*address >= NUM_REG) {
    return(false);
  }

  // if the read bit is set, look up the value and send it to the master
  if (*read) {
    *value = Registers[*address];
    // Return value in the next two bytes of the transaction 
    tx = (*value >> 8) & 0xFF; 
    if (!SPI.read_write_byte(tx, &rx)) {
      return(false);
    }
    
    tx = *value & 0xFF; 
    if (!SPI.read_write_byte(tx, &rx)) {
      return(false);
    }
  } 
  else { 
    // If this is a write, read the next two bytes to get the value to write to the register
    tx = 0xFF; // Don't care
    if (!SPI.read_write_byte(tx, &rx)) {
      return(false);
    }
    *value = rx << 8;

    tx = 0xFF;
    if (!SPI.read_write_byte(tx, &rx)) {
      return(false);
    }
    *value |= rx;
  }
  return(true);
}


/*
 * SPI Thread, process SPI when triggered by ISR  
 *
 * This function is used to send/receive data as a slave
 *         It implements a register set with 16-bit registers/words
 *         It supports reading or writing one word per 3-byte SPI transaction.  
 *         It will automatically check the R/W bit in the first word and act accordingly. 
 *         For read, the address will be used as an
 *         index into the register array and the corresponding value will be returned to the 
 *         master.  For writes the address is used to select an appropriate action.
 */
static void SPIThread(void* arg) {
  UNUSED(arg);
  bool read;
  uint8_t address;
  uint16_t value;
  bool rval;

  Serial.println("SPI Thread started");
  
  while (1) { 
    // Wait for signal from ISR.
    // At this point xTaskToNotify should be NULL  
    // If it's no try to reset the interface instead
    if (xTaskToNotify != NULL)
    {
      Serial.println("SPI notification out of sync.  Resetting...");
      Serial.flush();
      // Wait for transaction to finish before resetting. SS is active low so wait until it goes high
      unsigned long end_time = millis() + 100;
      while (digitalRead(SS) == LOW) {
        if (millis() > end_time) {
            Serial.println("Timed out waiting for SS to go high");
            Serial.flush();
            break;
        }
      }
    }

    // Store this task's handle so the ISR knows who to signal   
    xTaskToNotify = xTaskGetCurrentTaskHandle();  

    // Block until ISR signals us.  This is faster than using a semaphore
    ulTaskNotifyTake( pdFALSE, portMAX_DELAY ); // Block without timeout, decrement (don't clear)

    SPI.reset();  // Reset the SPI hardware interface to flush any stale data: 

    if (xTaskErr > CatchupCnt) {
      Serial.println("Fell behind");
      Serial.flush();
      // Wait for transaction to finish before resetting. SS is active low so wait until it goes high
      unsigned long end_time = millis() + 100;
      while (digitalRead(SS) == LOW) {
        if (millis() > end_time) {
            Serial.println("Timed out waiting for SS to go high");
            Serial.flush();
            break;
        }
      }
      CatchupCnt = xTaskErr; // Don't block to process the missed interrupt.  
      continue;
    }

    // We must process the transaction as quickly as possible in order to keep up with the master.
    // If you have other interrupts in your system, you can use a critical section to prevent 
    // the transsaction getting interrupted, but you must disable the timeouts in the SPI library
    // by defining the SPI_TRANSFER_TIMEOUT macro to HAL_MAX_DELAY before including the SPI library
    // Be cafeful though as, without timeouts, the code can get stuck in an infinite loop under certain
    // error conditions.
    //taskENTER_CRITICAL();  
    rval = process_transaction(&read, &address, &value);
    //taskEXIT_CRITICAL();

    if (!rval) {
     Serial.println("Error in SPI transfer.  Aborting transaction...");
     continue;
    }

    if (!read) { // Handle Write actions outside of the critical section
      switch(address) {
        case 0:
        case 1:
          // Read only, no action
          break;
        case 10:
          if (value & 0x0001) {
            Serial.println("GPIO on");
            digitalWrite(DEBUG_GPIO, LOW);  // turn the LED on 
          }
          else {
            Serial.println("GPIO off");
            digitalWrite(DEBUG_GPIO, HIGH);  // turn the LED off 
          }
          Registers[10] = value;
          break;
        case 11:
          Registers[11] = ~value;
          break;
        default:
          Registers[address] = value;
      }
    } // write
  } // while forever
}


/*
 * Thread 2, Just a busy loop representing lower priority worker task.
 */
static void Thread2(void* arg) {
  UNUSED(arg);
  static int old_err = 0; 
  static int old_cnt = 0;

  Serial.println("low priority task started");

  while(1)
  {
    // Load Reg 0 with the value from millis()
    Registers[0] = millis() & 0xFFFF;

    // Load Reg 1 with the state of the blue User button
    Registers[1] = digitalRead(PC13); 

    // Check for error from SPI ISR - only print on change to avoid collision with other prints
    if (xTaskErr != old_err || CatchupCnt != old_cnt)
    {
      old_err = xTaskErr;
      old_cnt = CatchupCnt;
      Serial.printf("xTaskErr = %d,  CatchupCnt = %d\n", xTaskErr, CatchupCnt);
      Serial.flush();
    }
    delay(100);
  }
}


void setup() {
  portBASE_TYPE s1, s2;

  Serial.begin(115200); 
  // Wait for the serial port to actually open
  while (!Serial) { 
    delay(10); 
  }
  Serial.println("In setup");

  // initialize digital pin DEBUG_GPIO as an output.
  pinMode(DEBUG_GPIO, OUTPUT);
  pinMode(PC13, INPUT_PULLUP); // Configure the blue button as an input with internal pull-up resistor

  SPI.begin(SPI_PERIPHERAL);
  // Add an ISR to the SS pin to detect device selection by SPI master
  SPI.attachSlaveInterrupt(SS, SPI_ISR);  

  // create task at priority two (higher priority)
  s1 = xTaskCreate(SPIThread, NULL, 1024, NULL, 2, NULL); 
  // create task at priority one (lower priority)
   s2 = xTaskCreate(Thread2, NULL, 1024, NULL, 1, NULL);
  // check for creation errors
  if (s1 != pdPASS || s2 != pdPASS ) {
    Serial.println("Task Creation problem!  Halting.");
    Serial.flush();
    while(1); 
  }
  Serial.println("Threads started");

  Serial.println("Done setup");
  // start scheduler
  vTaskStartScheduler();
  Serial.println("Insufficient RAM");
  Serial.flush();
  while(1); 
}


//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
  // Not used.
}

