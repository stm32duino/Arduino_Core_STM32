/**
 * @brief This example demonstrates how to read data from the GNSS module - Quectel LC76F.
 *
 *        The example reset the GNSS at the beginning by cut off the power to the
 *        GNSS module for 5 seconds. After the GNSS get fixed with 4 satellite (or more),
 *        the Serial will stop printing NMEA sentences and how time-to-first-fix & GNSS data.
 * 
 * @author mtnguyen
 * @version 1.0.0
 */

#include <MicroNMEA.h> // https://github.com/stevemarple/MicroNMEA

char nmeaBuffer[100];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

bool gnss_fix_status = false;

uint32_t start_timestamp = 0;
uint32_t stop_timestamp = 0;

void setup()
{
  gnss_fix_status = false;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(GNSS_ENABLE_PIN, OUTPUT);
  digitalWrite(GNSS_ENABLE_PIN, LOW);
  pinMode(GNSS_V_BCKP_PIN, OUTPUT);
  digitalWrite(GNSS_V_BCKP_PIN, LOW);

  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Starting...");

  Serial1.begin(9600);

  delay(5000);
  digitalWrite(GNSS_ENABLE_PIN, HIGH);
  digitalWrite(GNSS_V_BCKP_PIN, HIGH);
  start_timestamp = millis();
}

void loop()
{
  if (Serial1.available())
  {
    char c = Serial1.read();

    if (gnss_fix_status == false)
      Serial.print(c);
    nmea.process(c);
  }

  if (Serial.available())
  {
    char c = Serial.read();
    Serial1.write(c);
  }

  if ((nmea.isValid() == true) && (nmea.getNumSatellites() > 4))
  {
    if (!gnss_fix_status)
    {
      gnss_fix_status = true;
      stop_timestamp = millis();

      Serial.println("\n\nGNSS Module fixed!");
      Serial.print("Time-to-first-fix (milliseconds): ");
      Serial.println(stop_timestamp - start_timestamp);

      Serial.print("Nav. system: ");
      if (nmea.getNavSystem())
        Serial.println(nmea.getNavSystem());
      else
        Serial.println("none");

      Serial.print("Num. satellites: ");
      Serial.println(nmea.getNumSatellites());

      Serial.print("HDOP: ");
      Serial.println(nmea.getHDOP() / 10., 1);

      Serial.print("Date/time: ");
      Serial.print(nmea.getYear());
      Serial.print('-');
      Serial.print(int(nmea.getMonth()));
      Serial.print('-');
      Serial.print(int(nmea.getDay()));
      Serial.print('T');
      Serial.print(int(nmea.getHour()));
      Serial.print(':');
      Serial.print(int(nmea.getMinute()));
      Serial.print(':');
      Serial.println(int(nmea.getSecond()));

      long latitude_mdeg = nmea.getLatitude();
      long longitude_mdeg = nmea.getLongitude();
      Serial.print("Latitude (deg): ");
      Serial.println(latitude_mdeg / 1000000., 6);

      Serial.print("Longitude (deg): ");
      Serial.println(longitude_mdeg / 1000000., 6);

      long alt;
      Serial.print("Altitude (m): ");
      if (nmea.getAltitude(alt))
        Serial.println(alt / 1000., 3);
      else
        Serial.println("not available");

      Serial.print("Speed: ");
      Serial.println(nmea.getSpeed() / 1000., 3);
      Serial.print("Course: ");
      Serial.println(nmea.getCourse() / 1000., 3);
    }
  }
}
