/**
 * @brief This example will forward serial / UART signal from the USB to
 *        the GNSS LC76F module and vice versa. In another word, it will by pass the MCU.
 * 
 * @author mtnguyen
 * @version 1.1.0
 * 
 */

void setup(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(GNSS_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(GNSS_PWR_ENABLE_PIN, HIGH);
  pinMode(GNSS_V_BCKP_PIN, OUTPUT);
  digitalWrite(GNSS_V_BCKP_PIN, HIGH);
  
  USB_SERIAL.begin(115200);
  while (!USB_SERIAL)
    ;

  USB_SERIAL.println("Starting...");

  GNSS_SERIAL.begin(115200);
  delay(1000);
}

void loop(void)
{
  if (GNSS_SERIAL.available())
  {
    USB_SERIAL.write(GNSS_SERIAL.read());
  }

  if (USB_SERIAL.available())
  {
    char c = USB_SERIAL.read();
    GNSS_SERIAL.write(c);
  }
}
