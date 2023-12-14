/**
 * @brief This example will forward serial / UART signal from the USB to
 *        the GNSS LC76F module and vice versa. In another word, it will by pass the MCU.
 * 
 * @author mtnguyen
 * @version 1.0.0
 * 
 */

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(GNSS_ENABLE_PIN, OUTPUT);
  digitalWrite(GNSS_ENABLE_PIN, HIGH);
  pinMode(GNSS_V_BCKP_PIN, OUTPUT);
  digitalWrite(GNSS_V_BCKP_PIN, HIGH);
  
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Starting...");

  Serial1.begin(9600);
  delay(1000);
}

void loop()
{
  if (Serial1.available())
  {
    Serial.write(Serial1.read());
  }

  if (Serial.available())
  {
    char c = Serial.read();
    Serial1.write(c);
  }
}
