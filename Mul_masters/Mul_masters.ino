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

#define OUTPin 6
#define inLED 13

#define THIS_ADDR 0

void setup() {
 pinMode(inLED, OUTPUT);
 digitalWrite(inLED, LOW);
 pinMode(OUTPin, OUTPUT);
 digitalWrite(OUTPin, HIGH);
 
 Wire.begin(THIS_ADDR);
 Wire.onReceive(receiveEvent);
 Serial.begin(9600);
}

void loop() {
 digitalWrite(OUTPin, HIGH);
 digitalWrite(inLED, LOW);
}

void receiveEvent(int howMany){
 while (Wire.available()){
   char c = Wire.read();
   Serial.print(c);
   digitalWrite(inLED, HIGH);
 }
 Serial.println();
 delay(1000);
 digitalWrite(inLED, LOW);
}
