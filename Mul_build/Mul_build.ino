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

#define INPin 2
#define OUTPin 6
#define inLED 13

#define THIS_ADDR 1
#define MASTER_ADDR 0

bool dataSent = false;

void setup() {
 pinMode(inLED, OUTPUT);
 digitalWrite(inLED, LOW);
 pinMode(INPin, INPUT);
 pinMode(OUTPin, OUTPUT);
 digitalWrite(OUTPin, LOW);
 
 Wire.begin(THIS_ADDR);
 Wire.onReceive(receiveEvent);
 dataSent = false;
}

void loop() {
 if (digitalRead(INPin) == HIGH && dataSent == false){
   Wire.beginTransmission(MASTER_ADDR);
   Wire.write("2h  ");
   Wire.endTransmission();
   dataSent = true;
   digitalWrite(OUTPin,HIGH);
   digitalWrite(inLED,HIGH);
   delay(1000);
   digitalWrite(inLED,LOW);
 }
 else if(dataSent = true){
  digitalWrite(OUTPin,HIGH);
  digitalWrite(inLED,LOW);
 }
 else{
  digitalWrite(OUTPin,LOW);
  digitalWrite(inLED,LOW);
 }
}

void receiveEvent(int howMany){
 while (Wire.available() > 0){
   Wire.read();
   //do receive stuff
   digitalWrite(inLED,HIGH);
   delay(500);
   digitalWrite(inLED,LOW);
   delay(500);
   digitalWrite(inLED,HIGH);
   delay(500);
   digitalWrite(inLED,LOW);
 }
}
