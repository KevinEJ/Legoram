#include <Wire.h>
#include <String.h>

#define INPin 3
#define OUTPin 5
#define inLED 13
#define rLED 9
#define gLED 8
#define bLED 7

#define THIS_ADDR 22
#define MASTER_ADDR 8

bool dataSent = false;
/*char mycmd[26] = {'b','u','i','l','d',' ',' ',' ',
                  'c','a','n','n','o','n',' ',' ',
                  ' ',' ',' ',' ',' ',' ',' ',' ',
                  '\n','!'};*/
char mycmd[26] = {'b','u','i','l','d',' ',' ',' ',
                  'w','a','l','l',' ',' ',' ',' ',
                  ' ',' ',' ',' ',' ',' ',' ',' ',
                  '\n','!'};

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
   Wire.write(mycmd);
   Wire.endTransmission();
   dataSent = true;
   for(int i =1; i<=3;i++){
    digitalWrite(gLED,HIGH);
    delay(250);
    digitalWrite(gLED,LOW);
    delay(250);
   }
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
