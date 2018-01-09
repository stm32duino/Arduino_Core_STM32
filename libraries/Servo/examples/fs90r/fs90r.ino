/*
 Use servo library to control a FS90R motor

 Motor information : 
   http://www.feetechrc.com/product/analog-servo/micro-1-3kg-cm-360-degree-continuous-rotation-servo-fs90r/
   Must respect the pulse range in order not to damage servo.
   
*/

#include <Servo.h>

Servo fs90r;  // create servo object to control a servo

int potpin = 0;   // analog pin used to connect the potentiometer
int val;          // variable to read the value from the analog pin
int servopin = 9; // pin used to connect the servo

void setup() {
  Serial.begin(115200);

  fs90r.attach(servopin, 900, 2100); // attaches the servo on pin 9 to the servo object
                                     // Be carefull to min and max values...
}

void loop() {
  val = analogRead(potpin);        // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180, at 90, 
                                   // motor is stopped)

  Serial.print("val = ");
  Serial.println(val);

  fs90r.write(val);                // sets the servo speed according to the scaled value
  delay(15);
}

