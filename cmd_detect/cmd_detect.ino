byte addr = 2;
bool dataTransmitted = false;
int turnPin = 2;
int turnOut = 3;

#include <Wire.h>

void setup() {
  Wire.begin(addr);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  if(dataTransmitted == false)
    digitalWrite(turnOut,LOW);
  else
    digitalWrite(turnOut,HIGH);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  if(digitalRead(turnPin)==HIGH){//only if my turn
    Wire.write("2h  ");
    dataTransmitted = true;
  }
}
