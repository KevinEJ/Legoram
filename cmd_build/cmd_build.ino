byte addr = 1;
bool dataTransmitted = false;
int turnIn = 2;
int turnOut = 6;

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
  if(digitalRead(turnIn)==HIGH && dataTransmitted==false){//only if my turn
    Wire.write("1h  ");
    dataTransmitted = true;
  }
}
