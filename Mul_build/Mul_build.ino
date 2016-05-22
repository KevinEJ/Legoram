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

#define INPin 3
#define OUTPin 5
#define inLED 13
#define rLED 9
#define gLED 8
#define bLED 7

#define THIS_ADDR 6
#define MASTER_ADDR 0

bool dataSent = false;

void setup() {
 pinMode(inLED, OUTPUT);
 digitalWrite(inLED, LOW);
 pinMode(INPin, INPUT);
 pinMode(OUTPin, OUTPUT);
 digitalWrite(OUTPin, LOW);
 pinMode(rLED, OUTPUT);
 digitalWrite(rLED, LOW);
 pinMode(gLED, OUTPUT);
 digitalWrite(gLED, LOW);
 pinMode(bLED, OUTPUT);
 digitalWrite(bLED, LOW);
 
 Wire.begin(THIS_ADDR);
 Wire.onReceive(receiveEvent);
 dataSent = false;
}

void loop() {
 if (digitalRead(INPin) == HIGH && dataSent == false){
   Wire.beginTransmission(MASTER_ADDR);
   Wire.write("2h  ");
   Wire.write(THIS_ADDR);
   Wire.endTransmission();
   dataSent = true;
   digitalWrite(inLED,HIGH);
   delay(1000);
   digitalWrite(inLED,LOW);
   digitalWrite(OUTPin,HIGH);
 }
 else if(dataSent = true){
  digitalWrite(OUTPin,HIGH);
  digitalWrite(inLED,LOW);
 }
 else{
  digitalWrite(OUTPin,LOW);
  digitalWrite(inLED,LOW);
 }
 /*digitalWrite(rLED,HIGH);
 delay(500);
 digitalWrite(rLED,LOW);
 digitalWrite(gLED,HIGH);
 delay(500);
 digitalWrite(gLED,LOW);
 digitalWrite(bLED,HIGH);
 delay(500);
 digitalWrite(rLED,HIGH);
 digitalWrite(gLED,HIGH);
 digitalWrite(bLED,LOW);
 delay(500);
 digitalWrite(rLED,HIGH);
 digitalWrite(gLED,LOW);
 digitalWrite(bLED,HIGH);
 delay(500);
 digitalWrite(rLED,LOW);
 digitalWrite(gLED,HIGH);
 digitalWrite(bLED,HIGH);
 delay(500);
 digitalWrite(rLED,HIGH);
 digitalWrite(gLED,HIGH);
 digitalWrite(bLED,HIGH);
 delay(500);
 digitalWrite(rLED,LOW);
 digitalWrite(gLED,LOW);
 digitalWrite(bLED,LOW);*/
}

void receiveEvent(int howMany){
 while (Wire.available() > 0){
   Wire.read();
   //do receive stuff
   /*digitalWrite(inLED,HIGH);
   delay(500);
   digitalWrite(inLED,LOW);
   delay(500);
   digitalWrite(inLED,HIGH);
   delay(500);
   digitalWrite(inLED,LOW);*/
 }
}
