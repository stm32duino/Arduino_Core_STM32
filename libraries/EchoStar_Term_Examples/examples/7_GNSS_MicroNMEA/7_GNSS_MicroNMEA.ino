/**
 * @brief This example demonstrates how to read data from the GNSS module - Quectel LC76F.
 *
 *        The example reset the GNSS at the beginning by cut off the power to the
 *        GNSS module for 5 seconds. After the GNSS get fixed with 4 satellite (or more),
 *        the USB_SERIAL will stop printing NMEA sentences and how time-to-first-fix & GNSS data.
 * 
 * @author mtnguyen
 * @version 1.1.0
 */

#include <MicroNMEA.h> // https://github.com/stevemarple/MicroNMEA

char nmeaBuffer[100];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

bool gnss_fix_status = false;

uint32_t start_timestamp = 0;
uint32_t stop_timestamp = 0;

void setup(void)
{
  gnss_fix_status = false;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(GNSS_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(GNSS_PWR_ENABLE_PIN, LOW);
  pinMode(GNSS_V_BCKP_PIN, OUTPUT);
  digitalWrite(GNSS_V_BCKP_PIN, LOW);

  USB_SERIAL.begin(115200);
  while (!USB_SERIAL)
    ;

  USB_SERIAL.println("Starting...");

  GNSS_SERIAL.begin(115200);

  delay(5000);
  digitalWrite(GNSS_PWR_ENABLE_PIN, HIGH);
  digitalWrite(GNSS_V_BCKP_PIN, HIGH);
  start_timestamp = millis();
}

void loop(void)
{
  if (GNSS_SERIAL.available())
  {
    char c = GNSS_SERIAL.read();

    if (gnss_fix_status == false)
      USB_SERIAL.print(c);
    nmea.process(c);
  }

  if (USB_SERIAL.available())
  {
    char c = USB_SERIAL.read();
    GNSS_SERIAL.write(c);
  }

  if ((nmea.isValid() == true) && (nmea.getNumSatellites() > 4))
  {
    if (!gnss_fix_status)
    {
      gnss_fix_status = true;
      stop_timestamp = millis();

      USB_SERIAL.println("\n\nGNSS Module fixed!");
      USB_SERIAL.print("Time-to-first-fix (milliseconds): ");
      USB_SERIAL.println(stop_timestamp - start_timestamp);

      USB_SERIAL.print("Nav. system: ");
      if (nmea.getNavSystem())
        USB_SERIAL.println(nmea.getNavSystem());
      else
        USB_SERIAL.println("none");

      USB_SERIAL.print("Num. satellites: ");
      USB_SERIAL.println(nmea.getNumSatellites());

      USB_SERIAL.print("HDOP: ");
      USB_SERIAL.println(nmea.getHDOP() / 10., 1);

      USB_SERIAL.print("Date/time: ");
      USB_SERIAL.print(nmea.getYear());
      USB_SERIAL.print('-');
      USB_SERIAL.print(int(nmea.getMonth()));
      USB_SERIAL.print('-');
      USB_SERIAL.print(int(nmea.getDay()));
      USB_SERIAL.print('T');
      USB_SERIAL.print(int(nmea.getHour()));
      USB_SERIAL.print(':');
      USB_SERIAL.print(int(nmea.getMinute()));
      USB_SERIAL.print(':');
      USB_SERIAL.println(int(nmea.getSecond()));

      long latitude_mdeg = nmea.getLatitude();
      long longitude_mdeg = nmea.getLongitude();
      USB_SERIAL.print("Latitude (deg): ");
      USB_SERIAL.println(latitude_mdeg / 1000000., 6);

      USB_SERIAL.print("Longitude (deg): ");
      USB_SERIAL.println(longitude_mdeg / 1000000., 6);

      long alt;
      USB_SERIAL.print("Altitude (m): ");
      if (nmea.getAltitude(alt))
        USB_SERIAL.println(alt / 1000., 3);
      else
        USB_SERIAL.println("not available");

      USB_SERIAL.print("Speed: ");
      USB_SERIAL.println(nmea.getSpeed() / 1000., 3);
      USB_SERIAL.print("Course: ");
      USB_SERIAL.println(nmea.getCourse() / 1000., 3);
    }
  }
}
