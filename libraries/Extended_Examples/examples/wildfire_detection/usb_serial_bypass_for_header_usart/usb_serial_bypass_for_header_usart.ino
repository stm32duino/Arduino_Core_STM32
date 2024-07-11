/**
 * @brief This sketch aims to debug the AI Camera.
 * 
 * Serial data available from the AI Camera will be forwraded to the micro USB.
 * Therefore, only the microUSB connected to PC for powering & retrieving data.
 * 
 * Connect Camera TX to PA2 & Camera RX to PA3 to get started.
 * 
 * @author mtnguyen, fferrero
 * @version 1.0.0 for Echo 7 board version
 * 
 */

void setup(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  

  HEADER_SERIAL.begin(115200);
  USB_SERIAL.begin(115200);
  while (!USB_SERIAL)
    ;

  USB_SERIAL.println("Starting...");
  HEADER_SERIAL.flush();

  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop(void)
{
  if (HEADER_SERIAL.available())
  {
    char c = HEADER_SERIAL.read();
    USB_SERIAL.write(c);
  }

  if (USB_SERIAL.available())
  {
    char c = USB_SERIAL.read();
    HEADER_SERIAL.write(c);
  }
}
