/**
 * @brief This sketch aims to updating firmware of EM2050 module on EchoStar-Term-7 board.
 * 
 * The sketch requires a USB TTL connect to the header J8 (PA2-USART2_TX & PA3-USART2_RX)
 * USB TTL <-> EchoStar-Term-7's header <-> EM2050 Module
 * 
 * Using TERATERM software to connect to the USB TTL port to upload the firmware according to EchoStar Guide. (NOT the USB_SERIAL of the board)
 * 
 * EchoStar-Term-7 starts with normal Serial forwarding mode. Pressing USER_BTN will switch the EM2050 to Firmware bootloader mode.
 * 
 * The LED indicates the current EM2050 mode. LED ON implies the Bootloader mode. LED OFF implies the normal running mode.
 *
 * @author mtnguyen
 * @version 1.1.0
 */

#if ((LEAT_BOARD_VERSION != 7) || (LEAT_BOARD_VERSION != 7001))
#error This sketch supports only EchoStar-Term-7 Board.
#endif

uint8_t bootloader_enable_flag = 0;
uint32_t button_last_pressed_timestamp = 0;
volatile uint8_t button_press_counter = 0;

void setup()
{
  bootloader_enable_flag = 0;
  button_last_pressed_timestamp = 0;
  button_press_counter = 0;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(USER_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(USER_BTN), button_1_isr, RISING);

  pinMode(ECHOSTAR_BOOT_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_BOOT_PIN, LOW);
  pinMode(ECHOSTAR_nRST_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_nRST_PIN, HIGH);

#if defined(ECHOSTAR_PWR_ENABLE_PIN)
  pinMode(ECHOSTAR_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_PWR_ENABLE_PIN, HIGH);
#endif

  ECHOSTAR_SERIAL.begin(115200);
  Serial2.begin(115200);
  delay(1000);

  EM2050_reset_to_run();
  delay(1000);
}

void loop()
{
  if ((button_press_counter > 0) && (millis() - button_last_pressed_timestamp > 1000))
  {
    button_press_counter = 0;
    button_last_pressed_timestamp = millis();

    bootloader_enable_flag ^= 0x01;
    if (bootloader_enable_flag != 0)
    {
      EM2050_reset_to_bootloader();
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
      EM2050_reset_to_run();
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  if (Serial2.available())
  {
    ECHOSTAR_SERIAL.write(Serial2.read());
  }
  if (ECHOSTAR_SERIAL.available())
  {
    Serial2.write(ECHOSTAR_SERIAL.read());
  }
}

void EM2050_reset_to_bootloader(void)
{
  digitalWrite(ECHOSTAR_nRST_PIN, LOW);
  digitalWrite(ECHOSTAR_BOOT_PIN, LOW);
  delay(200);
  digitalWrite(ECHOSTAR_nRST_PIN, HIGH);
}

void EM2050_reset_to_run(void)
{
  digitalWrite(ECHOSTAR_nRST_PIN, LOW);
  digitalWrite(ECHOSTAR_BOOT_PIN, HIGH);
  delay(200);
  digitalWrite(ECHOSTAR_nRST_PIN, HIGH);
}

inline bool character_filter(char input)
{
  if ((input >= 0x20) && (input <= 0x7E))
  {
    return true;
  }

  if ((input == '\n') || (input == '\r') || (input == '\t'))
  {
    return true;
  }

  if ((input == 0x06 /* ACK */) || (input == 0x15 /* NACK */))
  {
    return true;
  }

  return false;
}

void button_1_isr(void)
{
  button_press_counter++;
}
