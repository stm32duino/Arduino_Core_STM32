/**
 * @brief This sketch is a demonstration of Smart Vision IoT for Wild fire detection.
 * 
 * The device gathers & sends information of the integrated AI Camera, GNSS position & sensors
 * to EchoStar satellite network for every LORA_SENDING_PERIOD_S.
 * 
 * Connect Camera TX to PA2 & Camera RX to PA3 to get started.
 * 
 * Parameters relating to Data sending period (LORA_SENDING_PERIOD_S), GNSS configurations, etc. are defined & modified in project_configuration.h
 * 
 * NOTE: Sensors data is not available in this version due to the diversity of sensors type implementation on different batch.
 * 
 * @author mtnguyen, fferrero
 * @version 1.0.0 for Echo 7 board version
 * 
 */

#include "project_configuration.h"

#include "STM32LowPower.h"
#include <STM32RTC.h>
#include <MicroNMEA.h> // https://github.com/stevemarple/MicroNMEA

#include "es_camera_parser.h"

extern CameraParser_t CAMERA_DATA_PARSER;
uint8_t camera_payload[6]; // 24-frame

STM32RTC &rtc = STM32RTC::getInstance();
static uint32_t atime = 600;

uint32_t last_packet_send_timestamp = 0;

char nmeaBuffer[100];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

struct DLresults {
  int8_t SNR, RSSI, freq_error;
};

void setup(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  HEADER_SERIAL.begin(115200);
  USB_SERIAL.begin(115200);
  while ((!USB_SERIAL) && (millis() < 5000))
    ;

  USB_SERIAL.println("===== Sketch: wildfire_camera_demo_v2.ino =====");
  HEADER_SERIAL.flush();

  mcu_sleep_init();
  sensor_init();
  gnss_init();
  em2050_init();

  // Force to MSS Satellite mode
  ECHOSTAR_SERIAL.println("AT+REGION=MSS-S");

  delay(1000);
  digitalWrite(LED_BUILTIN, LOW); // Done initialization
}

void loop(void)
{
  USB_SERIAL.println("INFO: Device wake up !");

  USB_SERIAL.println("INFO: Gathering GNSS Data");
  get_gnss_data();
  
  USB_SERIAL.println("INFO: Gathering Sensors Data");
  get_sensor_data();
  
  USB_SERIAL.println("INFO: Gathering Camera Data");
  get_camera_data();
  delay(100);

  USB_SERIAL.println("INFO: Sending data to network");
  send_data();

  delay(1000);

  USB_SERIAL.println("INFO: Going to sleep mode");
  mcu_sleep(LORA_SENDING_PERIOD_S);
}

void get_camera_data(void)
{
  CAMERA_DATA_PARSER.clear_frame_data();

  uint32_t camera_start_reading_timestamp_ms = millis();
  while ((millis() - camera_start_reading_timestamp_ms <= 60000) && (!CAMERA_DATA_PARSER.is_all_frame_data_ready_flag()))
  {
    if (HEADER_SERIAL.available())
    {
      char c = HEADER_SERIAL.read();
      USB_SERIAL.write(c);

      CAMERA_DATA_PARSER.process_char(c);
    }
  }

  CAMERA_DATA_PARSER.get_frame_data_u2(camera_payload, 6);
}

void EM2050_soft_sleep_enable(void)
{
  pinMode(ECHOSTAR_RTS_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_RTS_PIN, HIGH);
  delay(50);
}

void EM2050_soft_sleep_disable(void)
{
  pinMode(ECHOSTAR_RTS_PIN, INPUT);
  delay(50);
}

void mcu_sleep_init(void)
{
  // Low-power library initialization
  rtc.begin();
  LowPower.begin();
  LowPower.enableWakeupFrom(&rtc, alarmMatch, &atime);
}

void mcu_sleep(uint32_t sleep_duration_s)
{
  rtc.setAlarmEpoch(rtc.getEpoch() + sleep_duration_s);
  LowPower.deepSleep();
}

void alarmMatch(void *data)
{
}

void led_blink(unsigned int num_of_blink, unsigned int on_period_ms, unsigned int off_period_ms)
{
  while (num_of_blink > 0)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(on_period_ms);
    digitalWrite(LED_BUILTIN, LOW);
    delay(off_period_ms);
  }
}

void sensor_init(void)
{
  // TODO: EchoV7 rev003 has different sensors
}

void em2050_init(void)
{
  pinMode(ECHOSTAR_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_PWR_ENABLE_PIN, HIGH);

  pinMode(ECHOSTAR_BOOT_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_BOOT_PIN, HIGH);

  pinMode(ECHOSTAR_RTS_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_RTS_PIN, HIGH);
}

void gnss_on(void)
{
  digitalWrite(GNSS_PWR_ENABLE_PIN, HIGH);
  digitalWrite(GNSS_V_BCKP_PIN, HIGH);
}

void gnss_off(void)
{
  digitalWrite(GNSS_PWR_ENABLE_PIN, LOW);
  digitalWrite(GNSS_V_BCKP_PIN, HIGH);
}

void gnss_init(void)
{
  pinMode(GNSS_PWR_ENABLE_PIN, OUTPUT);
  pinMode(GNSS_V_BCKP_PIN, OUTPUT);

  gnss_on();
  GNSS_SERIAL.begin(115200); // UART GNSS
}

void get_sensor_data(void)
{
  // Battery voltage

  // Accelerometer

  // Humidity / Temperature
}

void get_gnss_data(void)
{
  nmea.clear();
  gnss_on();

  mcu_sleep(GNSS_WAITING_TIME_S);

  uint32_t gnss_reading_start_timestamp = millis();
  while ((millis() - gnss_reading_start_timestamp <= (GNSS_MIN_READING_TIME_S * 1000)) && ((nmea.getNumSatellites() < 8) || (nmea.getLatitude() == 0)))
  {
    if (GNSS_SERIAL.available())
    {
      char c = GNSS_SERIAL.read();
      nmea.process(c);
    }
  }

  gnss_off();
}

uint16_t read_bat(void)
{
  uint16_t voltage_adc = (uint16_t)analogRead(SENSORS_BATERY_ADC_PIN);
  uint16_t voltage = (uint16_t)((ADC_AREF / 1.024) * (BATVOLT_R1 + BATVOLT_R2) / BATVOLT_R2 * (float)voltage_adc);
  return voltage;
}

void send_data(void)
{
  int16_t t = 0; // TODO: Read temperature
  uint8_t h = 0; // TODO: Read humidity
  uint16_t p = 0; // TODO: Read pressure
  int8_t x = 0; // TODO: Read accelerometer
  int8_t y = 0; // TODO: Read accelerometer
  int8_t z = 0; // TODO: Read accelerometer
  long lat = nmea.getLatitude();  // Latitude : 0.0001 ° Signed MSB
  long lon = nmea.getLongitude(); // Longitude : 0.0001 ° Signed MSB
  int8_t speed = (int8_t)(nmea.getSpeed() / 1000);
  int8_t pwr = (int8_t)em2050_readpwr();
  float gnss_lat = (float)lat / 1E6;
  float gnss_lon = (float)lon / 1E6;
  long alt;
  nmea.getAltitude(alt);
  int32_t AltitudeBinary = alt / 100;  // Altitude : 0.01 meter Signed MSB
  uint8_t s = nmea.getNumSatellites(); // nb of satellite in view with GNSS
  // uint16_t bat = measure_bat();
  uint16_t bat = read_bat();
  DLresults dl = em2050_readDL();

  uint32_t LatitudeBinary = ((gnss_lat + 90) / 180) * 16777215;
  uint32_t LongitudeBinary = ((gnss_lon + 180) / 360) * 16777215;
  int16_t altitudeGps = alt;

  USB_SERIAL.print("  Temp = ");
  USB_SERIAL.print(t);
  USB_SERIAL.print("  Hum = ");
  USB_SERIAL.print(h);
  USB_SERIAL.print("  Pressure = ");
  USB_SERIAL.print(p);
  USB_SERIAL.print("  x = ");
  USB_SERIAL.print(x);
  USB_SERIAL.print(", y = ");
  USB_SERIAL.print(y);
  USB_SERIAL.print(", z = ");
  USB_SERIAL.println(z);
  USB_SERIAL.print("Lat = ");
  USB_SERIAL.print(gnss_lat, 4);
  USB_SERIAL.print(", Lon = ");
  USB_SERIAL.print(gnss_lon, 4);
  USB_SERIAL.print(", alt = ");
  USB_SERIAL.print(alt / 1e3);
  USB_SERIAL.print(", Bat = ");
  USB_SERIAL.println(bat);

  // int blocks=7;
  int i = 0;
  unsigned char mydata[64];
  mydata[i++] = t >> 8;
  mydata[i++] = t & 0xFF;
  mydata[i++] = h;
  mydata[i++] = p >> 8;
  mydata[i++] = p & 0xFF;
  mydata[i++] = x;
  mydata[i++] = y;
  mydata[i++] = z;
  mydata[i++] = (LatitudeBinary >> 16) & 0xFF;
  mydata[i++] = (LatitudeBinary >> 8) & 0xFF;
  mydata[i++] = LatitudeBinary & 0xFF;
  mydata[i++] = (LongitudeBinary >> 16) & 0xFF;
  mydata[i++] = (LongitudeBinary >> 8) & 0xFF;
  mydata[i++] = LongitudeBinary & 0xFF;
  mydata[i++] = (AltitudeBinary >> 16) & 0xFF;
  mydata[i++] = (AltitudeBinary >> 8) & 0xFF;
  mydata[i++] = AltitudeBinary & 0xFF;
  mydata[i++] = s;
  mydata[i++] = bat >> 8;
  mydata[i++] = bat & 0xFF;
  mydata[i++] = 0;
  mydata[i++] = speed;
  mydata[i++] = pwr;
  mydata[i++] = (int8_t)dl.SNR / 4;
  mydata[i++] = (int8_t)-dl.RSSI;

  // Camera data
  mydata[i++] = camera_payload[0];
  mydata[i++] = camera_payload[1];
  mydata[i++] = camera_payload[2];
  mydata[i++] = camera_payload[3];
  mydata[i++] = camera_payload[4];
  mydata[i++] = camera_payload[5];

  char str[32];
  array_to_string(mydata, i, str);

  ECHOSTAR_SERIAL.print("AT+SENDB=1,0,1,0,");
  ECHOSTAR_SERIAL.println(str);
}

void array_to_string(byte array[], unsigned int len, char buffer[])
{
  for (unsigned int i = 0; i < len; i++)
  {
    byte nib1 = (array[i] >> 4) & 0x0F;
    byte nib2 = (array[i] >> 0) & 0x0F;
    buffer[i * 2 + 0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
    buffer[i * 2 + 1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
  }
  buffer[len * 2] = '\0';
}

int em2050_readpwr(void)
{
  while (ECHOSTAR_SERIAL.available())
  {
    ECHOSTAR_SERIAL.read();
  }

  ECHOSTAR_SERIAL.println("AT+CTP?");
  String temp = ECHOSTAR_SERIAL.readStringUntil('\n');
  temp = ECHOSTAR_SERIAL.readStringUntil(':');
  temp = ECHOSTAR_SERIAL.readStringUntil('\n');
  return temp.toInt();
}

// Read Downlink RSSI from EM2050
DLresults em2050_readDL(void) {
  DLresults read;
  while (ECHOSTAR_SERIAL.available())
  {
    ECHOSTAR_SERIAL.read();
  }
  ECHOSTAR_SERIAL.println("AT+PKTST?");
  String temp = ECHOSTAR_SERIAL.readStringUntil('\n');
  temp = ECHOSTAR_SERIAL.readStringUntil(':');
  temp = ECHOSTAR_SERIAL.readStringUntil(',');
  read.SNR = temp.toInt();
  temp = ECHOSTAR_SERIAL.readStringUntil(',');
  read.RSSI = temp.toInt();
  temp = ECHOSTAR_SERIAL.readStringUntil('\n');
  read.freq_error = temp.toInt();
  return read;
}
