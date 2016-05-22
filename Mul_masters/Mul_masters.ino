/**
*
* Sample Multi Master I2C implementation.  Sends a button state over I2C to another
* Arduino, which flashes an LED correspinding to button state.
* 
* Connections: Arduino analog pins 4 and 5 are connected between the two Arduinos, 
* with a 1k pullup resistor connected to each line.  Connect a push button between 
* digital pin 10 and ground, and an LED (with a resistor) to digital pin 9.
* 
*/

#include <Wire.h>

#define OUTPin 5
#define inLED 13
#define rLED 9
#define gLED 8
#define bLED 7

#define THIS_ADDR 0

void setup() {
 pinMode(inLED, OUTPUT);
 digitalWrite(inLED, LOW);
 pinMode(rLED, OUTPUT);
 digitalWrite(rLED, LOW);
 pinMode(gLED, OUTPUT);
 digitalWrite(gLED, LOW);
 pinMode(bLED, OUTPUT);
 digitalWrite(bLED, LOW);
 pinMode(OUTPin, OUTPUT);
 digitalWrite(OUTPin, HIGH);
 
 Wire.begin(THIS_ADDR);
 Wire.onReceive(receiveEvent);
 Serial.begin(9600);
}

void loop() {
 digitalWrite(OUTPin, HIGH);
 digitalWrite(inLED, LOW);
 digitalWrite(rLED, LOW);
 digitalWrite(gLED, LOW);
 digitalWrite(bLED, LOW);
 delay(500);
 digitalWrite(gLED,HIGH);
 delay(500);
}

void receiveEvent(int howMany){
 while (Wire.available()){
   char c = Wire.read();
   Serial.print(c);
 }
 digitalWrite(inLED, HIGH);
 Serial.println();
 delay(1000);
 digitalWrite(inLED, LOW);
}
