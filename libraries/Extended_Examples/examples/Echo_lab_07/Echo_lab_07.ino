/**
 * @brief This example demonstrates how to use use the GNSS and echostar network for tracking application
 * This code can also be used to test Echostar AT commands, GNSS UART and I2C sensors (BME680 and KX025)
 * The terminal try to get a GNSS fix and send to Echo network its position + sensing information
 * 
 * @author mtnguyen, fferrero
 * @version 1.0.5 for Echo 7 board version
 * 
 */

 #define DATA_INTERVAL 5000 //ms
 #define ADC_AREF 3.3f
 #define BATVOLT_R1 1.0f
 #define BATVOLT_R2 1.0f
 #define SLEEP 1

#define SWITCH_REVERSING_CONTROL_DEFAULT_VALUE false
volatile int switch_reversing_control = SWITCH_REVERSING_CONTROL_DEFAULT_VALUE;

 // max. 250 seconds for GPS fix
#define FIXTIME 180
// Perdio to send GNSS position to sat network
#define PERIOD 180

#include <Wire.h>
#include <Kionix_KX023.h> // https://github.com/nguyenmanhthao996tn/Kionix_KX023
#include <Wire.h>
#include <Adafruit_Sensor.h> // https://github.com/adafruit/Adafruit_BME280_Library
//#include <Adafruit_BME280.h> // https://github.com/adafruit/Adafruit_Sensor
#include <MicroNMEA.h> // https://github.com/stevemarple/MicroNMEA
#include "STM32LowPower.h"
#include <STM32RTC.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h" // https://github.com/adafruit/Adafruit_BME680

KX023 myIMU(Wire, SENSORS_KX023_ADDRESS);
float kx_x, kx_y, kx_z;
Adafruit_BME680 bme;
#define SEALEVELPRESSURE_HPA (1013.25)
char nmeaBuffer[100];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));
String revString;
char revChar[1000];
int len = 0;
uint8_t is_fixing = 0;
int t2f=0;
uint8_t it=0;
int ttf = 0; // time to fix
int lowpower=0;
int NMEA=0;
int Sleeptime=10000;

bool gnss_fix_status = false;

uint32_t start_timestamp = 0;
uint32_t stop_timestamp = 0;
uint8_t button = 0;
uint8_t mode = 0;

long currentMillis = 0, getSensorDataPrevMillis = 0;
boolean lora_sending=true;
int timezone = 7;
int year, mon, day, hr, minute;
double sec;

struct DLresults {
    int8_t SNR, RSSI, freq_error;
};

void swctrl_change_isr(void)
{
  do_switch_ctrl_update();
}

void do_switch_ctrl_update(void)
{
  if (digitalRead(ECHOSTAR_SWCTRL_PIN) == LOW)
  {
    digitalWrite(DPDT_CTRL_PIN, switch_reversing_control ? HIGH : LOW);    
  }
  else
  {
    digitalWrite(DPDT_CTRL_PIN, switch_reversing_control ? LOW : HIGH);    
  }
}

void setup()
{
  gnss_fix_status = false;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

#if defined(ECHOSTAR_PWR_ENABLE_PIN)
  pinMode(ECHOSTAR_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_PWR_ENABLE_PIN, HIGH);
#endif


  pinMode(GNSS_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(GNSS_PWR_ENABLE_PIN, LOW);
  pinMode(GNSS_V_BCKP_PIN, OUTPUT);
  digitalWrite(GNSS_V_BCKP_PIN, HIGH);
  pinMode(USER_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(USER_BTN), button_1_isr, RISING);
  pinMode(SENSORS_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(SENSORS_PWR_ENABLE_PIN, HIGH);
  pinMode(DPDT_CTRL_PIN, OUTPUT);
  digitalWrite(DPDT_CTRL_PIN, LOW);  
  
  pinMode(ECHOSTAR_SWCTRL_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ECHOSTAR_SWCTRL_PIN), swctrl_change_isr, CHANGE);
  Wire.setSDA(SENSORS_I2C_SDA_PIN);
  Wire.setSCL(SENSORS_I2C_SCL_PIN);
  Wire.begin();
    delay(200);

  switch_reversing_control = SWITCH_REVERSING_CONTROL_DEFAULT_VALUE;

#if defined(ECHOSTAR_PWR_ENABLE_PIN)
  pinMode(ECHOSTAR_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_PWR_ENABLE_PIN, HIGH);
#endif

#if defined(DPDT_PWR_ENABLE_PIN)
  pinMode(DPDT_PWR_ENABLE_PIN, OUTPUT);
  digitalWrite(DPDT_PWR_ENABLE_PIN, HIGH);
#endif
  pinMode(DPDT_CTRL_PIN, OUTPUT);
  digitalWrite(DPDT_CTRL_PIN, HIGH);

  pinMode(ECHOSTAR_SWCTRL_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ECHOSTAR_SWCTRL_PIN), swctrl_change_isr, CHANGE);


  pinMode(ECHOSTAR_BOOT_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_BOOT_PIN, HIGH);

   
  pinMode(ECHOSTAR_RTS_PIN, OUTPUT);
  digitalWrite(ECHOSTAR_RTS_PIN, LOW);

  USB_SERIAL.begin(115200);
  while (!USB_SERIAL && ((millis()-getSensorDataPrevMillis)>5000)){
delay(10);
  }  

  
  if (myIMU.begin())
  {
    USB_SERIAL.println("Could not find KX023-1025? Check wiring");
  }
  else
  {
    USB_SERIAL.println("KX023-1025: OK");
  }
  myIMU.configAsynchronousReadBackAccelerationData(KX023_ACCLERATION_RANGE_2G, KX023_ODR_25HZ);
      myIMU.setOperatingMode();      

  getSensorDataPrevMillis = millis();   

   if((millis()-getSensorDataPrevMillis)>5000){
    lora_sending=true;}

   USB_SERIAL.println("Starting...");
  GNSS_SERIAL.begin(115200); // UART GNSS
  ECHOSTAR_SERIAL.begin(115200); // UART EM2050

  if (!bme.begin(SENSORS_BME680_ADDRESS))
  {
    USB_SERIAL.println(F("Could not find a valid BME680 sensor, check wiring!"));
    while (1)
      ;
  }
    // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  //bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  //bme.setGasHeater(320, 150); // 320*C for 150 ms

  LowPower.begin();

  getSensorDataPrevMillis=millis()-PERIOD*1000+10000; 

  delay(600);
  ECHOSTAR_SERIAL.println("AT+TXPMSS=23"); // Set max Tx power MSS
   delay(200);
   ECHOSTAR_SERIAL.println("AT+ADR=1"); // Activate or desactivate Adaptative Data rate mode
   delay(200);
  ECHOSTAR_SERIAL.println("AT+JOIN"); // Join network
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{

 if (button > 0){
   blink(200);
  //  lora_sending=!lora_sending;
  //  getSensorDataPrevMillis=millis()-PERIOD*1000+2000;
  lowpower=0;
      gnss(1);
      mode=2;
      NMEA=1;
   USB_SERIAL.println("Push button");
  button=0;    
  }

  if(lowpower==1 && (currentMillis - getSensorDataPrevMillis >3000)){
   // currentMillis = millis();  
  USB_SERIAL.println("Sleeping");  
  delay(20);
   // USB_SERIAL.end();
   //GNSS_SERIAL.end(); // UART GNSS
 //ECHOSTAR_SERIAL.end(); // UART EM2050
 //digitalWrite(SENSORS_PWR_ENABLE_PIN, LOW);
 //digitalWrite(ECHOSTAR_BOOT_PIN, LOW);
 digitalWrite(ECHOSTAR_BOOT_PIN, LOW);
//digitalWrite(ECHOSTAR_RTS_PIN, LOW);

 blink(50);

#if SLEEP
 LowPower.sleep(Sleeptime);
 getSensorDataPrevMillis = getSensorDataPrevMillis- Sleeptime; // adjust the Millis counter to consider the sleep time
 delay(20);
#else
delay(Sleeptime);
 #endif

digitalWrite(ECHOSTAR_BOOT_PIN, HIGH);
//bme.begin(SENSORS_BME680_ADDRESS);
 //USB_SERIAL.begin(115200);
 //GNSS_SERIAL.begin(115200); // UART GNSS
 //ECHOSTAR_SERIAL.begin(115200); // UART EM2050       
  }

  if (lora_sending==1){
      currentMillis = millis();      
      if (currentMillis - getSensorDataPrevMillis > PERIOD*1000){

        //digitalWrite(SENSORS_PWR_ENABLE_PIN, HIGH);
        
        bme.beginReading();
        //getSensorDataPrevMillis=currentMillis;  
        mode=0;
        nmea.clear(); // reset NMEA
        gnss(1); // Power ON GNSS LDO
        delay(100);
        ttf = gnss_fix()/1000;
        gnss(0); // Power OFF GNSS LDO
        mode=1;
        // digitalWrite(ECHOSTAR_RTS_PIN, LOW);
        // delay(500);     
        // while (ECHOSTAR_SERIAL.available())
        // {
        // USB_SERIAL.write(ECHOSTAR_SERIAL.read());        
        // }
        SendLoRa(1);        
        lowpower=1;      
        getSensorDataPrevMillis=currentMillis;          
                  
      }
  }
  
if (mode==1) {
  while (ECHOSTAR_SERIAL.available())
        {
        USB_SERIAL.write(ECHOSTAR_SERIAL.read());
        }
}

if(mode == 2) {
  if (GNSS_SERIAL.available())
        {
        currentMillis = millis();  
      // Print sensor & gps data
      if (currentMillis - getSensorDataPrevMillis > DATA_INTERVAL){
        getSensorDataPrevMillis = currentMillis;
        // GPS         
        GPS_showData(); // print GPS info
        print_line(); // print line        
      }
       
    revString = GNSS_SERIAL.readStringUntil(0x0D);
    len = revString.length() + 1;
    revString.toCharArray(revChar, len);
    if (NMEA==1) {
        Serial.print(revString);}
    for (int i = 0; i < len; i++) {
      nmea.process(*(revChar + i));      
    }
  }
  if (NMEA==1 &&  USB_SERIAL.available()) {
       revString =  USB_SERIAL.readStringUntil(0x0D);       
        GNSS_SERIAL.println(revString);
      }
}

  if (NMEA != 1 &&  USB_SERIAL.available()) {      // If anything comes in Serial (USB),
    char c =  USB_SERIAL.read();    
  
  if(c=='$'){     
    blink(50);
    
    String CMD= USB_SERIAL.readStringUntil('\r');
    USB_SERIAL.println(CMD);           
    if(CMD.equalsIgnoreCase("GNSS")){
      lowpower=0;
      gnss(1);
      mode=2;
      NMEA=0;
      USB_SERIAL.println("Mode GNSS");
      }
    else if(CMD.equalsIgnoreCase("NMEA")){
      lowpower=0;
      gnss(1);
      mode=2;
      NMEA=1;
      USB_SERIAL.println("Mode NMEA");
      }  
    else if(CMD.equalsIgnoreCase("BME")){
      meas_bme();
      }  
    else if(CMD.equalsIgnoreCase("KX")){
      meas_kx();
      } 
    else if(CMD.equalsIgnoreCase("LORA")){
      mode=1;
      lowpower=0;
      USB_SERIAL.println("Mode LoRA");
      }
    else if(CMD.equalsIgnoreCase("SENDLORA")){
      mode=1;
    SendLoRa(1);
    }
    else if(CMD.equalsIgnoreCase("RESET")){
      lowpower=0;
      mode=0;
      NMEA=0;
      digitalWrite(GNSS_PWR_ENABLE_PIN, LOW);
      USB_SERIAL.println("Reset");
      }
    else if(CMD.equalsIgnoreCase("setEU868")){
      mode=1;
      ECHOSTAR_SERIAL.print("AT+REGION=EU868");
      USB_SERIAL.println("Set EU868 mode");
      } 
    else if(CMD.equalsIgnoreCase("pwr")){
       USB_SERIAL.println(readpwr());      
      } 
     else if(CMD.equalsIgnoreCase("dl")){
      DLresults dl = readDL();
       USB_SERIAL.print(dl.SNR);
       USB_SERIAL.print(" "); 
       USB_SERIAL.print(dl.RSSI);
       USB_SERIAL.print(" ");  
       USB_SERIAL.print(dl.freq_error);     
      }   
     else if(CMD.equalsIgnoreCase("setMSS")){
      mode=1;
      ECHOSTAR_SERIAL.print("AT+REGION=MSS-S");
      USB_SERIAL.println("Set MSS-S mode");
      }    
    else if(CMD.equalsIgnoreCase("Periodic")){
      mode=0;
      lora_sending=!lora_sending;
      USB_SERIAL.print(" Periodic is : ");
      USB_SERIAL.print(lora_sending);
      getSensorDataPrevMillis=millis()-PERIOD*1000+2000;
      }
    
    else{
     USB_SERIAL.println("Wrong Command");
        }  
  }
    else{
      if(mode==1){
        ECHOSTAR_SERIAL.write(c);        
      }
      else if(mode==2) {
        GNSS_SERIAL.write(c);        
      }
      else if(mode==0){
        }    
    }  
  }
}

void button_1_isr(void)
{
  button++;  
}

void blink(int blinktime){
digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(blinktime);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
} 


void meas_kx(void) {
myIMU.readAsynchronousReadBackAccelerationData(&kx_x, &kx_y, &kx_z);
  USB_SERIAL.print("KX023-1025: ");
  USB_SERIAL.print(kx_x);
  USB_SERIAL.print(", ");
  USB_SERIAL.print(kx_y);
  USB_SERIAL.print(", ");
  USB_SERIAL.print(kx_z);
  USB_SERIAL.println("");
}

void meas_bme(void) {
// Tell BME680 to begin measurement.
  unsigned long endTime = bme.beginReading();
 while (!bme.endReading()) {
  delay(50);
 }

USB_SERIAL.print("Temperature = ");
  USB_SERIAL.print(bme.temperature);
  USB_SERIAL.println(" °C");

  USB_SERIAL.print("Pressure = ");
  USB_SERIAL.print(bme.pressure / 100.0F);
  USB_SERIAL.println(" hPa");

  USB_SERIAL.print("Approx. Altitude = ");
  USB_SERIAL.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  USB_SERIAL.println(" m");

  USB_SERIAL.print("Humidity = ");
  USB_SERIAL.print(bme.humidity);
  USB_SERIAL.println(" %");

  USB_SERIAL.println();
}

void gnss(int state) {

if(state == 1){
digitalWrite(GNSS_PWR_ENABLE_PIN, HIGH);
digitalWrite(GNSS_V_BCKP_PIN, HIGH);
  start_timestamp = millis();
  GNSS_SERIAL.begin(115200); // UART GNSS
}
else{
digitalWrite(GNSS_PWR_ENABLE_PIN, LOW);
  }
}
// Send LoRaWan packet with Board sensor values
bool SendLoRa(uint8_t mode){

int16_t rx_delay=0;
  unsigned long endTime = bme.beginReading();
 while (!bme.endReading()) {
  delay(50);
 }
myIMU.readAsynchronousReadBackAccelerationData(&kx_x, &kx_y, &kx_z);
int16_t t=(int16_t) 100*bme.temperature; // return temperature in cents of degree
uint8_t h=(uint8_t)2*bme.humidity; // return humidity in percent
uint16_t p =(uint16_t)(bme.pressure/10);
int8_t x = (int8_t) 50*kx_x;
int8_t y = (int8_t) 50*kx_y;
int8_t z = (int8_t) 50*kx_z;
long lat= nmea.getLatitude(); //Latitude : 0.0001 ° Signed MSB
long lon= nmea.getLongitude(); //Longitude : 0.0001 ° Signed MSB
int8_t speed = (int8_t) (nmea.getSpeed()/1000);
float gnss_lat= (float)lat/1E6;
float gnss_lon= (float)lon/1E6;
long alt;
nmea.getAltitude(alt);
int32_t AltitudeBinary= alt/100; // Altitude : 0.01 meter Signed MSB
uint8_t s= nmea.getNumSatellites(); // nb of satellite in view with GNSS
uint16_t bat = read_bat();
DLresults dl = readDL();
int8_t pwr = (int8_t) readpwr();

  uint32_t LatitudeBinary = ((gnss_lat + 90) / 180) * 16777215;
  uint32_t LongitudeBinary =  ((gnss_lon + 180) / 360) * 16777215;
  int16_t  altitudeGps = alt; 

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
  USB_SERIAL.print(gnss_lat,4);
  USB_SERIAL.print(", Lon = ");
  USB_SERIAL.print(gnss_lon,4);
  USB_SERIAL.print(", alt = ");
  USB_SERIAL.print(alt/1e3);
  USB_SERIAL.print(", TTF = ");
  USB_SERIAL.print(ttf);
  USB_SERIAL.print(", Bat = ");
  USB_SERIAL.println(bat);

//int blocks=7;
int i=0;
unsigned char mydata[64];
mydata[i++] = t >> 8;
mydata[i++] = t & 0xFF;
mydata[i++] = h;
mydata[i++] = p >> 8;
mydata[i++] = p & 0xFF;
mydata[i++] = x;
mydata[i++] = y;
mydata[i++] = z;
mydata[i++] = ( LatitudeBinary >> 16 ) & 0xFF;
mydata[i++] = ( LatitudeBinary >> 8 ) & 0xFF;
mydata[i++] = LatitudeBinary & 0xFF;
mydata[i++] = ( LongitudeBinary >> 16 ) & 0xFF;
mydata[i++] = ( LongitudeBinary >> 8 ) & 0xFF;
mydata[i++] = LongitudeBinary & 0xFF;
mydata[i++] = ( AltitudeBinary >> 16 ) & 0xFF;
mydata[i++] = ( AltitudeBinary >> 8 ) & 0xFF;
mydata[i++] = AltitudeBinary & 0xFF;
mydata[i++] = s;
mydata[i++] = bat >> 8;
mydata[i++] = bat & 0xFF;
mydata[i++] = ttf;
mydata[i++] = speed;
mydata[i++] = pwr;
mydata[i++] = (int8_t)dl.SNR/4;
mydata[i++] = (int8_t)-dl.RSSI;

char str[32];
array_to_string(mydata, i, str);

ECHOSTAR_SERIAL.print("AT+SENDB=1,0,1,0,");
ECHOSTAR_SERIAL.println(str);

return true;
}

void array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}

unsigned long unixTimestamp(int year, int month, int day, int hour, int min, int sec)
{
  const short days_since_beginning_of_year[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  int leap_years = ((year - 1) - 1968) / 4 - ((year - 1) - 1900) / 100 + ((year - 1) - 1600) / 400;
  long days_since_1970 = (year - 1970) * 365 + leap_years + days_since_beginning_of_year[month - 1] + day - 1;
  if ((month > 2) && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
    days_since_1970 += 1; /* +leap day, if year is a leap year */
  return sec + 60 * (min + 60 * (hour + 24 * days_since_1970));
}

void GPS_showData(void)
{ 
   USB_SERIAL.print("Nav. system: ");
   if (nmea.getNavSystem())
      USB_SERIAL.print(nmea.getNavSystem());
    else
      USB_SERIAL.print("none");
    USB_SERIAL.print(", Sat in view: ");
    USB_SERIAL.print(nmea.getNumSatellites());

    USB_SERIAL.print(", Time to Fix: ");
    USB_SERIAL.println(t2f/1000);    
    
    double latitude = nmea.getLatitude();
    double longitude = nmea.getLongitude();
    long alt;
    
    USB_SERIAL.print("GPS position: ");
    USB_SERIAL.print(latitude / 1.0e6, 4);
    USB_SERIAL.print(", ");
    USB_SERIAL.print(longitude / 1.0e6, 4);
     USB_SERIAL.print(", ");
    if (nmea.getAltitude(alt)){
      USB_SERIAL.print(alt / 1000., 3);}
      USB_SERIAL.println();
      
    USB_SERIAL.print("Speed: ");
    USB_SERIAL.print(nmea.getSpeed() / 1000., 3);
    USB_SERIAL.print(" Course: ");
    USB_SERIAL.print(nmea.getCourse() / 1000., 3); 
    uint32_t unixt = unixTimestamp(nmea.getYear(), nmea.getMonth(), nmea.getDay(), nmea.getHour(), nmea.getMinute(), nmea.getSecond());
    USB_SERIAL.print("  Unix time: ");
    USB_SERIAL.println(unixt);      
}


void print_line(void)
{ 
USB_SERIAL.print(it);
USB_SERIAL.print("***********************");
USB_SERIAL.print(it);
USB_SERIAL.print("*************************");
USB_SERIAL.println(it);
it++;
     }


uint16_t read_bat(void){
  uint16_t  voltage_adc = (uint16_t)analogRead(SENSORS_BATERY_ADC_PIN);
  uint16_t  voltage = (uint16_t)((ADC_AREF / 1.024) * (BATVOLT_R1 + BATVOLT_R2) / BATVOLT_R2 * (float)voltage_adc);    
    return voltage;
}


// Fix with the GNSS module, wait up to get a valid Fix position
long gnss_fix(void) {  
   long startTime = millis(); 
while (((nmea.getNumSatellites()<8) || (nmea.getLatitude()==0)) && (millis() - startTime < (FIXTIME*1000))) {
  
  currentMillis = millis();  
      // Print sensor & gps data
      if (currentMillis - getSensorDataPrevMillis > DATA_INTERVAL){
        getSensorDataPrevMillis = currentMillis;
        // GPS
        blink(100);
        GPS_showData(); // print GPS info
        print_line(); // print line
      }
    revString = GNSS_SERIAL.readStringUntil(0x0D);
    //Serial.print(revString);
    len = revString.length() + 1;
    revString.toCharArray(revChar, len);
    for (int i = 0; i < len; i++) {
      nmea.process(*(revChar + i));
    }
}
long delay =millis();
while((millis() - delay) <2300){
revString = GNSS_SERIAL.readStringUntil(0x0D);
    len = revString.length() + 1;
    revString.toCharArray(revChar, len);
    for (int i = 0; i < len; i++) {
      nmea.process(*(revChar + i));
    }
}

return millis() - startTime;
}
// Read uplink Tx power (usefull when ADR is activated)
int readpwr(void){
while (ECHOSTAR_SERIAL.available())
        {
        ECHOSTAR_SERIAL.read();
        }
      ECHOSTAR_SERIAL.println("AT+CTP?");
      delay(10);
      String temp= ECHOSTAR_SERIAL.readStringUntil('\n');
      temp= ECHOSTAR_SERIAL.readStringUntil(':');      
            temp= ECHOSTAR_SERIAL.readStringUntil('\n');
         return temp.toInt();
}
// Read Downlink RSSI from EM2050
DLresults readDL(void){
  DLresults read;
while (ECHOSTAR_SERIAL.available())
        {
        ECHOSTAR_SERIAL.read();
        }
      ECHOSTAR_SERIAL.println("AT+PKTST?");
      String temp= ECHOSTAR_SERIAL.readStringUntil('\n');     
      temp= ECHOSTAR_SERIAL.readStringUntil(':');      
      temp = ECHOSTAR_SERIAL.readStringUntil(',');      
            read.SNR=temp.toInt();
            temp = ECHOSTAR_SERIAL.readStringUntil(',');       
            read.RSSI=temp.toInt();
            temp = ECHOSTAR_SERIAL.readStringUntil('\n');         
            read.freq_error=temp.toInt();    
      return read;
}



