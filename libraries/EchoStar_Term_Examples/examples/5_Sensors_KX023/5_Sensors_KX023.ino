#include <Wire.h>
#include <Kionix_KX023.h> // https://github.com/nguyenmanhthao996tn/Kionix_KX023

KX023 myIMU(Wire, SENSORS_KX023_ADDRESS);
float kx_x, kx_y, kx_z;

void gpio_init(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(SENSORS_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(SENSORS_PWR_ENABLE_PIN, HIGH);
}

void inline led_blink(uint8_t num_of_blink = 1)
{
  for (; num_of_blink > 0; num_of_blink--)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
  }
}

void setup(void)
{
  USB_SERIAL.begin(9600);

  gpio_init();

  Wire.setSDA(SENSORS_I2C_SDA_PIN);
  Wire.setSCL(SENSORS_I2C_SCL_PIN);
  Wire.begin();

  while (!USB_SERIAL && millis() < 5000)
    ;
  USB_SERIAL.println("****** KX023-1025 Asynchronous Read Back Acceleration Data for Echo Star Term 6 ******");

  KX023_Status_t status = myIMU.begin();
  if (status == KX023_STATUS_OK)
  {
    USB_SERIAL.println("KX023-1025: OK");
  }
  else
  {
    USB_SERIAL.println(kx023_get_status_string(status));
  }

  myIMU.configAsynchronousReadBackAccelerationData(KX023_ACCLERATION_RANGE_2G, KX023_ODR_25HZ);

  myIMU.setOperatingMode();
  delay(50);
}

void loop(void)
{
  myIMU.readAsynchronousReadBackAccelerationData(&kx_x, &kx_y, &kx_z);
  USB_SERIAL.print(kx_x);
  USB_SERIAL.print(", ");
  USB_SERIAL.print(kx_y);
  USB_SERIAL.print(", ");
  USB_SERIAL.print(kx_z);
  USB_SERIAL.println("");

  led_blink();
}
