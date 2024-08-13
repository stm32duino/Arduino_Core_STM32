/**
 * @brief This sketch is a demonstration of Smart Vision IoT for Wild fire detection.
 *
 * The device gathers & sends information of the integrated AI Camera, GNSS position & sensors
 * to EchoStar satellite network for every NO_FIRE_PACKET_SENDING_PERIOD_S.
 *
 * Connect Camera TX to PA2 & Camera RX to PA3 to get started.
 *
 * Parameters relating to Data sending period (NO_FIRE_PACKET_SENDING_PERIOD_S), GNSS configurations, etc. are defined & modified in project_configuration.h
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

#include "es_camera_parser_v2.h"
#include "es_sensors.h"
#include "es_log.h"
#include "es_em2050.h"
#include "es_led.h"

uint8_t camera_payload_event[6];        // 24-frame
uint8_t camera_payload_probability[24]; // 24-frame

STM32RTC &rtc = STM32RTC::getInstance();
static uint32_t atime = 600;

uint32_t last_packet_send_timestamp = 0;

char nmeaBuffer[100];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

float gnss_lat;
float gnss_lon;
long alt;
uint8_t num_of_satellite_in_view;

bool fire_detected_flag;
uint32_t next_uplink_packet_timestamp_s = 0;
uint32_t next_gps_update_timestamp_s = 0;

void setup(void)
{
  LED.init();
  LED.long_blink(3);

  HEADER_SERIAL.begin(115200);
  LOG.init();

  LOG.println("[INFO] main::setup() | ===== Sketch: wildfire_camera_demo_v2.ino =====");
  HEADER_SERIAL.flush();

  mcu_sleep_init();
  sensor_init();
#ifndef DEBUGGING_OPTION_GNSS_DISABLE
  gnss_init();
#endif /* DEBUGGING_OPTION_GNSS_DISABLE */
  EM2050.init();
  EM2050.get_device_info_on_log();

  delay(1000);
  LED.long_blink(2);

  fire_detected_flag = false;
  next_uplink_packet_timestamp_s = 0; // Send first status
  next_gps_update_timestamp_s = rtc.getEpoch() + GNSS_UPDATING_PERIOD_S;

  LOG.println("[INFO] main::setup() | Setup DONE");
#ifdef DISABLE_BUILTIN_LED_AFTER_INIT
  LED.disable();
  LOG.println("[INFO] main::setup() | Disable LED");
#endif /* DISABLE_BUILTIN_LED_AFTER_INIT */
}

void loop(void)
{
  LOG.println("[INFO] main::loop() | Device wake up !");

  if (rtc.getEpoch() >= next_gps_update_timestamp_s)
  {
    LOG.println("[INFO] main::loop() | Updating GNSS Data");

#ifndef DEBUGGING_OPTION_GNSS_DISABLE
    get_gnss_data(false);
#endif /* DEBUGGING_OPTION_GNSS_DISABLE */

    next_gps_update_timestamp_s = rtc.getEpoch() + GNSS_UPDATING_PERIOD_S;
    LOG.print("[INFO] main::loop() | Scheduling next GNSS Update on ");
    LOG.println((unsigned int)next_gps_update_timestamp_s);
  }

  LOG.println("[INFO] main::loop() | Gathering Camera Data");
  get_camera_data();
  bool current_read_fire_detected = CAMERA_DATA_PARSER.is_fire_detected();
  if (current_read_fire_detected ^ fire_detected_flag) // If fire_detected state changed?
  {
    fire_detected_flag = current_read_fire_detected;
    if (fire_detected_flag)
    {
      next_uplink_packet_timestamp_s = rtc.getEpoch(); // Send immidiately if there is a new detection of fire

      LOG.println("[INFO] main::loop() | Fire detected, switched to faster uplink mode");
      LOG.println("[INFO] main::loop() | Next uplink packet is NOW");
    }
    else
    {
      LOG.println("[INFO] main::loop() | Fire put out, switched to slow uplink mode");
    }
  }

  delay(1000);

  if (rtc.getEpoch() >= next_uplink_packet_timestamp_s)
  {
    LOG.println("[INFO] main::loop() | Sending data to network");
    send_data();

    if (fire_detected_flag)
    {
      next_uplink_packet_timestamp_s = rtc.getEpoch() + FIRE_DETECTED_PACKET_SENDING_PERIOD_S;
    }
    else
    {
      next_uplink_packet_timestamp_s = rtc.getEpoch() + NO_FIRE_PACKET_SENDING_PERIOD_S;
    }
    LOG.print("[INFO] main::loop() | Next uplink is scheduled at ");
    LOG.println((unsigned int)next_uplink_packet_timestamp_s);
  }

  delay(1000);

  LOG.print("[INFO] main::loop() | Going to sleep mode for ");
  LOG.print(TIME_BETWEEN_CAMERA_READ_S);
  LOG.println(" seconds.");
  mcu_sleep(TIME_BETWEEN_CAMERA_READ_S);
}

void get_camera_data(void)
{
  LOG.println("[DEBUG] main::get_camera_data() | Clearing previous camera frame data");
  CAMERA_DATA_PARSER.clear_frame_data();

  uint32_t camera_start_reading_timestamp_s = rtc.getEpoch();
  LOG.print("[DEBUG] main::get_camera_data() | Start reading now, timeout (seconds) is ");
  LOG.println((int)CAMERA_MAX_READING_TIME_S);
  while (!CAMERA_DATA_PARSER.is_all_frame_data_ready_flag())
  {
    if (HEADER_SERIAL.available())
    {
      char c = HEADER_SERIAL.read();
      CAMERA_DATA_PARSER.process_char(c);
    }

    if (rtc.getEpoch() - camera_start_reading_timestamp_s > (CAMERA_MAX_READING_TIME_S))
    {
      LOG.println("[DEBUG] main::get_camera_data() | Camera reading TIMEOUT");
      break;
    }
  }

  LOG.println("[DEBUG] main::get_camera_data() | Camera DONE");

  CAMERA_DATA_PARSER.get_frame_data_u2(camera_payload_event, 6);
  CAMERA_DATA_PARSER.get_frame_data_probability_u8(camera_payload_probability, 24);
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
#ifndef USING_SLEEP_MODE
  delay(sleep_duration_s * 1000); // DEBUG
#else
  rtc.setAlarmEpoch(rtc.getEpoch() + sleep_duration_s);
  LowPower.deepSleep();
#endif
}

void alarmMatch(void *data)
{
}

void sensor_init(void)
{
  SENSORS.init();
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
  gnss_lat = 0;
  gnss_lon = 0;
  alt = 0;
  num_of_satellite_in_view = 0;

  pinMode(GNSS_PWR_ENABLE_PIN, OUTPUT);
  pinMode(GNSS_V_BCKP_PIN, OUTPUT);

  gnss_on();
  GNSS_SERIAL.begin(115200); // UART GNSS

  delay(100);

  get_gnss_data(true); // This will not exit if GNSS is not fix
}

/**
 * @brief Read GNSS data
 * @param force_fix_reading if set to TRUE, the GNSS reading is running until a fix condition met or NO timeout in another word.
 */
void get_gnss_data(bool force_fix_reading)
{
  LOG.println("[DEBUG] main::get_gnss_data() | Set GNSS Power ON");
  nmea.clear();
  gnss_on();

  LOG.print("[DEBUG] main::get_gnss_data() | CPU Sleep, leaving GNSS running for stablizing for ");
  LOG.print(GNSS_WAITING_TIME_S);
  LOG.print(" seconds.");
  uint32_t gnss_waiting_start_timestamp_s = rtc.getEpoch();
  while (rtc.getEpoch() - gnss_waiting_start_timestamp_s <= (GNSS_WAITING_TIME_S))
  {
    LED.short_blink(1);
    LOG.print(".");
    mcu_sleep(5);
  }
  LOG.println();

  LOG.println("[DEBUG] main::get_gnss_data() | Start to read GNSS data");
  uint32_t led_blink_timestamp_s = rtc.getEpoch();
  uint32_t gnss_reading_start_timestamp_s = rtc.getEpoch();
  bool gnss_fix = false;
  while (force_fix_reading ||
         (rtc.getEpoch() - gnss_reading_start_timestamp_s <= (GNSS_MAX_READING_TIME_S * 1000)))
  {
    for (int i = 0; ((i < 64) && (GNSS_SERIAL.available())); i++) // Read maximum 64 character
    {
      char c = GNSS_SERIAL.read();
      nmea.process(c);
    }

    if ((nmea.isValid()) &&
        (nmea.getNumSatellites() >= 8) &&
        (nmea.getLatitude() != 0) &&
        (nmea.getLongitude() != 0))
    {
      LOG.println("\n[DEBUG] main::get_gnss_data() | GNSS Fixed");
      gnss_fix = true;
      break; // Exit the reading loop
    }

    if (rtc.getEpoch() - led_blink_timestamp_s >= 5) // Blink every 5 seconds
    {
      LOG.print(".");
      led_blink_timestamp_s = rtc.getEpoch();
      LED.short_blink(2);
    }
  }

  if (gnss_fix)
  {
    LOG.println("[INFO] main::get_gnss_data() | GNSS fixed. Updating data.");

    long lat = nmea.getLatitude();  // Latitude : 0.0001 ° Signed MSB
    long lon = nmea.getLongitude(); // Longitude : 0.0001 ° Signed MSB
    gnss_lat = (float)(lat / 1.0E6);
    gnss_lon = (float)(lon / 1.0E6);

    nmea.getAltitude(alt);

    num_of_satellite_in_view = nmea.getNumSatellites();

    // ---
    LOG.print("[INFO] main::get_gnss_data() | GNSS Latitude: ");
    LOG.println(gnss_lat);
    LOG.print("[INFO] main::get_gnss_data() | GNSS Longitude: ");
    LOG.println(gnss_lon);
    LOG.print("[INFO] main::get_gnss_data() | GNSS Altitude: ");
    LOG.println(alt / 1.0e3);
    LOG.print("[INFO] main::get_gnss_data() | GNSS num_of_satellite_in_view: ");
    LOG.println(num_of_satellite_in_view);
  }
  else
  {
    LOG.println("[WARNING] main::get_gnss_data() | GNSS reading timeout & does not fixed. Using previous data. Set num_of_satellite_in_view to 0.");
    num_of_satellite_in_view = 0;
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
  EM2050.soft_sleep_disable();

  SENSORS.power_on();
  delay(1000);

  int16_t t = (int16_t)(SENSORS.read_temperature() * 100.0); // TODO: Read temperature
  uint8_t h = (uint8_t)(SENSORS.read_humidity());            // TODO: Read humidity
  uint16_t p = (uint16_t)(SENSORS.read_pressure() / 10.0);   // TODO: Read pressure

  SENSORS.power_off();

  LOG.print("[DEBUG] main::send_data() | Temp = ");
  LOG.print(t);
  LOG.print("  Hum = ");
  LOG.print(h);
  LOG.print("  Pressure = ");
  LOG.println(p);

  uint32_t LatitudeBinary = ((gnss_lat + 90) / 180) * 16777215;
  uint32_t LongitudeBinary = ((gnss_lon + 180) / 360) * 16777215;
  int32_t AltitudeBinary = alt / 100; // Altitude : 0.01 meter Signed MSB

  LOG.print("[DEBUG] main::send_data() | Lat = ");
  LOG.print(gnss_lat);
  LOG.print(", Lon = ");
  LOG.print(gnss_lon);
  LOG.print(", alt = ");
  LOG.println(alt / 1.0e3);

  uint16_t bat = read_bat();

  LOG.print("[DEBUG] main::send_data() | Bat = ");
  LOG.println(bat);

  int8_t pwr = (int8_t)EM2050.readpwr();

  LOG.print("[DEBUG] main::send_data() | pwr = ");
  LOG.println(pwr);

  DLresults dl = EM2050.readDL();

  LOG.print("[DEBUG] main::send_data() | SNR = ");
  LOG.println(dl.SNR / 4);
  LOG.print("[DEBUG] main::send_data() | RSSI = ");
  LOG.println(dl.RSSI);

  // int blocks=7;
  int i = 0;
  unsigned char mydata[64];
  mydata[i++] = t >> 8;
  mydata[i++] = t & 0xFF;
  mydata[i++] = h;
  mydata[i++] = p >> 8;
  mydata[i++] = p & 0xFF;
  mydata[i++] = (LatitudeBinary >> 16) & 0xFF;
  mydata[i++] = (LatitudeBinary >> 8) & 0xFF;
  mydata[i++] = LatitudeBinary & 0xFF;
  mydata[i++] = (LongitudeBinary >> 16) & 0xFF;
  mydata[i++] = (LongitudeBinary >> 8) & 0xFF;
  mydata[i++] = LongitudeBinary & 0xFF;
  mydata[i++] = (AltitudeBinary >> 16) & 0xFF;
  mydata[i++] = (AltitudeBinary >> 8) & 0xFF;
  mydata[i++] = AltitudeBinary & 0xFF;
  mydata[i++] = num_of_satellite_in_view;
  mydata[i++] = bat >> 8;
  mydata[i++] = bat & 0xFF;
  mydata[i++] = pwr;
  mydata[i++] = (int8_t)dl.SNR / 4;
  mydata[i++] = (int8_t)-dl.RSSI;

  // Camera data
  for (int j = 0; j < 6; j++)
  {
    mydata[i++] = camera_payload_event[j];
  }

  for (int j = 0; j < 24; j++)
  {
    mydata[i++] = camera_payload_probability[j];
  }

  if (EM2050.schedule_uplink(mydata, i) == 0)
  {
    LOG.println("[INFO] main::send_data() | Uplink SUCCESS");
  }
  else
  {
    LOG.println("[ERROR] main::send_data() | Uplink FAILED");
  }

  LED.short_blink(2);
  EM2050.soft_sleep_enable();
}
