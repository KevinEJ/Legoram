#include <Wire.h>

#define OUTPin 5
#define inLED 13
#define rLED 9
#define gLED 8
#define bLED 7

#define THIS_ADDR 8

byte blockCount = 1;
char data[20][26];
bool dataSent = false;

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
 dataSent = false;
 data[20][26] = {'-'};
 
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
 int No = 0;
 while (Wire.available()){
   char c = Wire.read();
   if(No<26){
    data[blockCount-1][No] = c;
    No++;
   }
   else{
    Serial.println("Out of bound(>26)");
   }
 }
 digitalWrite(inLED, HIGH);
 for(int j =1; j<=blockCount; j++){
  for(int i =0; i<26; i++){
    Serial.print(data[j-1][i]);
  }
  Serial.print(j);
  Serial.println();
 }
 Serial.println();
 Serial.println();
 Serial.println();
 blockCount++;
 delay(1000);
 digitalWrite(inLED, LOW);
}
