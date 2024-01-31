/**
 * @brief This example demonstrates how to use use the GNSS and echostar network for tracking applicaiton
 * The terminal try to get a GNSS fix and send to Echo network its position + sensing information
 * 
 * @author mtnguyen, fferrero
 * @version 1.0.4
 * 
 */

 #define DATA_INTERVAL 5000 //ms
 #define ADC_AREF 3.3f
 #define BATVOLT_R1 1.0f
 #define BATVOLT_R2 1.0f
 #define BATVOLT_PIN PA2
 #define LED_1_PIN PA13
#define BTN_1_PIN PC2

#define ECHOSTAR_TXD_PIN PC0
#define ECHOSTAR_RXD_PIN PC1

#define GNSS_TXD_PIN PB7
#define GNSS_RXD_PIN PA9

#define ECHOSTAR_GNSS_EN PA1
#define ECHOSTAR_SENSOR_EN PA14

#define ECHOSTAR_SWCTRL_PIN PB4
#define DPDT_CTRL_PIN PB8

#define SENSORS_I2C_SDA_PIN PA10
#define SENSORS_I2C_SCL_PIN PB6

#define SWITCH_REVERSING_CONTROL_DEFAULT_VALUE true
volatile int switch_reversing_control = SWITCH_REVERSING_CONTROL_DEFAULT_VALUE;

 // max. 250 seconds for GPS fix
#define FIXTIME 180
#define PERIOD 150

#include <Wire.h>
#include <Kionix_KX023.h> // https://github.com/nguyenmanhthao996tn/Kionix_KX023
#include <Wire.h>
#include <Adafruit_Sensor.h> // https://github.com/adafruit/Adafruit_BME280_Library
#include <Adafruit_BME280.h> // https://github.com/adafruit/Adafruit_Sensor
#include <MicroNMEA.h> // https://github.com/stevemarple/MicroNMEA
//#include "STM32LowPower.h"
//#include <STM32RTC.h>


KX023 myIMU(Wire, SENSORS_KX023_ADDRESS);
float kx_x, kx_y, kx_z;
Adafruit_BME280 bme;
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

bool gnss_fix_status = false;

uint32_t start_timestamp = 0;
uint32_t stop_timestamp = 0;
uint8_t button = 0;
uint8_t mode = 0;

unsigned long currentMillis = 0, getSensorDataPrevMillis = 0;
boolean lora_sending=true;
int timezone = 7;
int year;
int mon;
int day;
int hr;
int minute;
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
  pinMode(GNSS_ENABLE_PIN, OUTPUT);
  digitalWrite(GNSS_ENABLE_PIN, LOW);
  pinMode(GNSS_V_BCKP_PIN, OUTPUT);
  digitalWrite(GNSS_V_BCKP_PIN, LOW);
  pinMode(USER_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(USER_BTN), button_1_isr, RISING);
  pinMode(SENSORS_ENABLE_PIN, OUTPUT);
  digitalWrite(SENSORS_ENABLE_PIN, HIGH);
  pinMode(DPDT_CTRL_PIN, OUTPUT);
  digitalWrite(DPDT_CTRL_PIN, HIGH);
  pinMode(ECHOSTAR_SWCTRL_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ECHOSTAR_SWCTRL_PIN), swctrl_change_isr, CHANGE);
  Wire.setSDA(SENSORS_I2C_SDA_PIN);
  Wire.setSCL(SENSORS_I2C_SCL_PIN);
  Wire.begin();
    delay(200);

     switch_reversing_control = SWITCH_REVERSING_CONTROL_DEFAULT_VALUE;


  unsigned status = bme.begin(SENSORS_BME280_ADDRESS, &Wire);
  if (myIMU.begin())
  {
    Serial.println("Could not find KX023-1025? Check wiring");
  }
  else
  {
    Serial.println("KX023-1025: OK");
  }
  myIMU.configAsynchronousReadBackAccelerationData(KX023_ACCLERATION_RANGE_2G, KX023_ODR_25HZ);
      myIMU.setOperatingMode();
      

  getSensorDataPrevMillis = millis();

Serial.begin(115200);
  while (!Serial && ((millis()-getSensorDataPrevMillis)>5000))
     ;

   Serial.println("Starting...");
  Serial1.begin(9600); // UART GNSS
  SerialLP1.begin(115200); // UART EM2050

  //LowPower.begin();

  getSensorDataPrevMillis=millis(); 
 

  delay(600);
  SerialLP1.println("AT+TXPMSS=23");
   delay(200);
   SerialLP1.println("AT+ADR=0");
   delay(200);
  SerialLP1.println("AT+JOIN");
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);

}

void loop()
{

 if (button > 0){

   blink(200);
   lora_sending=!lora_sending;
   getSensorDataPrevMillis=millis()-PERIOD*1000+2000;
   Serial.println("Push button");


  button=0;    
  }
  if(lowpower==1 && (currentMillis - getSensorDataPrevMillis >3000)){
  Serial.println("Sleeping");
  //delay(20);
  //  Serial.end();
  // Serial1.end(); // UART GNSS
  // SerialLP1.end(); // UART EM2050
  // blink(50);
  // LowPower.sleep(10000);
  // delay(100);
  // Serial.begin(115200);
  // Serial1.begin(9600); // UART GNSS
  // SerialLP1.begin(115200); // UART EM2050
  delay(10000);
 
  }

  if (lora_sending==1){
      currentMillis = millis();      
      if (currentMillis - getSensorDataPrevMillis > PERIOD*1000){
        getSensorDataPrevMillis=currentMillis;  
        mode=0;
        nmea.clear(); // reset NMEA
        gnss(1);
        delay(100);
        ttf = gnss_fix()/1000;
        gnss(0);
        mode=1;
        SendLoRa(1);        
        lowpower=1;
        mode=0;
        getSensorDataPrevMillis=currentMillis; 
        //LowPower.deepSleep(3000);        
        
        //delay(10000);           
      }
  }
  
if (mode==1) {
  while (SerialLP1.available())
        {
        Serial.write(SerialLP1.read());
        }

}

if(mode == 2) {
  if (Serial1.available())
        {
        currentMillis = millis();  
      // Print sensor & gps data
      if (currentMillis - getSensorDataPrevMillis > DATA_INTERVAL){
        getSensorDataPrevMillis = currentMillis;
        // GPS         
        GPS_showData(); // print GPS info
        print_line(); // print line        
      }
    revString = Serial1.readStringUntil(0x0D);

    len = revString.length() + 1;
    revString.toCharArray(revChar, len);
    if (NMEA==1) {
        Serial.println(revString);}
    for (int i = 0; i < len; i++) {
      nmea.process(*(revChar + i));      
    }
  }
}



  if (Serial.available()) {      // If anything comes in Serial (USB),

    char c = Serial.read();    
  
  if(c=='$'){     
    blink(50);
    
    String CMD=Serial.readStringUntil('\r');
    Serial.println(CMD);           
    if(CMD.equalsIgnoreCase("GNSS")){
      lowpower=0;
      gnss(1);
      mode=2;
      NMEA=0;
      Serial.println("Mode GNSS");
      }
      if(CMD.equalsIgnoreCase("NMEA")){
      lowpower=0;
      gnss(1);
      mode=2;
      NMEA=1;
      Serial.println("Mode NMEA");
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
      Serial.println("Mode LoRA");
      }
    else if(CMD.equalsIgnoreCase("SENDLORA")){
      mode=1;
    SendLoRa(1);
    }
    else if(CMD.equalsIgnoreCase("RESET")){
      lowpower=0;
      mode=0;
      NMEA=0;
      digitalWrite(GNSS_ENABLE_PIN, LOW);
      Serial.println("Reset");
      }
    else if(CMD.equalsIgnoreCase("setEU868")){
      mode=1;
      SerialLP1.print("AT+REGION=EU868");
      Serial.println("Set EU868 mode");
      } 
    else if(CMD.equalsIgnoreCase("pwr")){
       Serial.println(readpwr());      
      } 
     else if(CMD.equalsIgnoreCase("dl")){
      DLresults dl = readDL();
       Serial.print(dl.SNR);
       Serial.print(" "); 
       Serial.print(dl.RSSI);
       Serial.print(" ");  
       Serial.print(dl.freq_error);     
      }   
     else if(CMD.equalsIgnoreCase("setMSS")){
      mode=1;
      SerialLP1.print("AT+REGION=MSS-S");
      Serial.println("Set MSS-S mode");
      }    
    else if(CMD.equalsIgnoreCase("Periodic")){
      mode=0;
      lora_sending=!lora_sending;
      getSensorDataPrevMillis=millis()-PERIOD*1000+2000;
      }
    
    else{
     Serial.println("Wrong Command");
        }  
  }
    else{

      if(mode==1){

        SerialLP1.write(c);        
      }
      else if(mode==2) {
        Serial1.write(c);        
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
  Serial.print("KX023-1025: ");
  Serial.print(kx_x);
  Serial.print(", ");
  Serial.print(kx_y);
  Serial.print(", ");
  Serial.print(kx_z);
  Serial.println("");
}

void meas_bme(void) {
Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}

void gnss(int state) {

if(state == 1){
digitalWrite(GNSS_ENABLE_PIN, HIGH);
digitalWrite(GNSS_V_BCKP_PIN, HIGH);
  start_timestamp = millis();
}
else{
digitalWrite(GNSS_ENABLE_PIN, LOW);
//digitalWrite(GNSS_V_BCKP_PIN, LOW);
}

}


bool SendLoRa(uint8_t mode){

int16_t rx_delay=0;
myIMU.readAsynchronousReadBackAccelerationData(&kx_x, &kx_y, &kx_z);
int16_t t=(int16_t) 100*bme.readTemperature(); // return temperature in cents of degree
uint8_t h=(uint8_t)2*bme.readHumidity(); // return humidity in percent
uint16_t p =(uint16_t)(bme.readPressure()/10);
int8_t x = (int8_t) 50*kx_x;
int8_t y = (int8_t) 50*kx_y;
int8_t z = (int8_t) 50*kx_z;
int16_t b = meas_bat();
long lat= nmea.getLatitude(); //Latitude : 0.0001 ° Signed MSB
long lon= nmea.getLongitude(); //Longitude : 0.0001 ° Signed MSB
int8_t speed = (int8_t) (nmea.getSpeed()/1000);
int8_t pwr = (int8_t) readpwr();
float gnss_lat= (float)lat/1E6;
float gnss_lon= (float)lon/1E6;
long alt;
nmea.getAltitude(alt);
int32_t AltitudeBinary= alt/100; // Altitude : 0.01 meter Signed MSB
uint8_t s= nmea.getNumSatellites(); // nb of satellite in view with GNSS
//uint16_t bat = measure_bat();
uint16_t bat = read_bat();
DLresults dl = readDL();

  uint32_t LatitudeBinary = ((gnss_lat + 90) / 180) * 16777215;
  uint32_t LongitudeBinary =  ((gnss_lon + 180) / 360) * 16777215;
  int16_t  altitudeGps = alt; 

  Serial.print("  Temp = ");
  Serial.print(t);
  Serial.print("  Hum = ");
  Serial.print(h);
   Serial.print("  Pressure = ");
  Serial.print(p);
  Serial.print("  x = ");
  Serial.print(x);
  Serial.print(", y = ");
  Serial.print(y);
  Serial.print(", z = ");
  Serial.println(z);
  Serial.print("Lat = ");
  Serial.print(gnss_lat,4);
  Serial.print(", Lon = ");
  Serial.print(gnss_lon,4);
  Serial.print(", alt = ");
  Serial.print(alt/1e3);
     Serial.print(", TTF = ");
  Serial.print(ttf);
   Serial.print(", Bat = ");
  Serial.println(bat);

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

SerialLP1.print("AT+SENDB=1,0,1,0,");
SerialLP1.println(str);

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
{ /*
  Serial.print("Valid fix: ");
  Serial.println(nmea.isValid() ? "yes" : "no");
  if(nmea.isValid()){ */
   Serial.print("Nav. system: ");
   if (nmea.getNavSystem())
      Serial.print(nmea.getNavSystem());
    else
      Serial.print("none");
    Serial.print(", Sat in view: ");
    Serial.print(nmea.getNumSatellites());

    Serial.print(", Time to Fix: ");
    Serial.println(t2f/1000);
    
    
    double latitude = nmea.getLatitude();
    double longitude = nmea.getLongitude();
    long alt;
    
    Serial.print("GPS position: ");
    Serial.print(latitude / 1.0e6, 4);
    Serial.print(", ");
    Serial.print(longitude / 1.0e6, 4);
     Serial.print(", ");
    if (nmea.getAltitude(alt)){
      Serial.print(alt / 1000., 3);}
      Serial.println();
      
    Serial.print("Speed: ");
    Serial.print(nmea.getSpeed() / 1000., 3);
    Serial.print(" Course: ");
    Serial.print(nmea.getCourse() / 1000., 3); 
    uint32_t unixt = unixTimestamp(nmea.getYear(), nmea.getMonth(), nmea.getDay(), nmea.getHour(), nmea.getMinute(), nmea.getSecond());
    Serial.print("  Unix time: ");
    Serial.println(unixt);      
}


void print_line(void)
{ 
Serial.print(it);
Serial.print("***********************");
Serial.print(it);
Serial.print("*************************");
Serial.println(it);
it++;

     }

int16_t meas_bat(void) {
  return 0;
}

uint16_t read_bat(void){
  uint16_t  voltage_adc = (uint16_t)analogRead(BATVOLT_PIN);
  uint16_t  voltage = (uint16_t)((ADC_AREF / 1.024) * (BATVOLT_R1 + BATVOLT_R2) / BATVOLT_R2 * (float)voltage_adc);
    
    return voltage;

}

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
    revString = Serial1.readStringUntil(0x0D);
    len = revString.length() + 1;
    revString.toCharArray(revChar, len);
    for (int i = 0; i < len; i++) {
      nmea.process(*(revChar + i));
    }
}
long delay =millis();
while((millis() - delay) <2300){
revString = Serial1.readStringUntil(0x0D);
    len = revString.length() + 1;
    revString.toCharArray(revChar, len);
    for (int i = 0; i < len; i++) {
      nmea.process(*(revChar + i));
    }
}

return millis() - startTime;

}

int readpwr(void){
while (SerialLP1.available())
        {
        SerialLP1.read();
        }
      SerialLP1.println("AT+CTP?");
      String temp= SerialLP1.readStringUntil('\n');
      //Serial.println(temp);
      temp= SerialLP1.readStringUntil(':');
      //Serial.println(temp);
            temp= SerialLP1.readStringUntil('\n');
     // Serial.println(temp);
     // temp= SerialLP1.readStringUntil('\n');
      //Serial.println(temp);
      return temp.toInt();

}

DLresults readDL(void){
  DLresults read;
while (SerialLP1.available())
        {
        SerialLP1.read();
        }
      SerialLP1.println("AT+PKTST?");
      String temp= SerialLP1.readStringUntil('\n');
      //Serial.println(temp);
      temp= SerialLP1.readStringUntil(':');
      //Serial.println(temp);
      temp = SerialLP1.readStringUntil(',');
      //Serial.println(temp);
            read.SNR=temp.toInt();
            temp = SerialLP1.readStringUntil(',');
        //    Serial.println(temp);
            read.RSSI=temp.toInt();
            temp = SerialLP1.readStringUntil('\n');
          //  Serial.println(temp);
            read.freq_error=temp.toInt();
     // Serial.println(temp);
     // temp= SerialLP1.readStringUntil('\n');
      //Serial.println(temp);
      return read;

}



