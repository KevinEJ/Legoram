// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
#include <Wire.h>

int turnPin = 3;

void setup()
{
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}

void loop()
{
  byte error, address;
  int nDevices = 0;

  digitalWrite(turnPin,HIGH);
  
  Serial.println("Scanning...");
  for(address = 1; address < 32; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found,requesting data from address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(":");

      Wire.requestFrom(address, 4);
      while (Wire.available()) { // slave may send less than requested
        char c = Wire.read(); // receive a byte as character
        Serial.print(c);         // print the character
      }


      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("\nNo I2C devices found\n");
  else
    Serial.println("\ndone\n");

  delay(250);           // wait 0.25 seconds for next scan
}
