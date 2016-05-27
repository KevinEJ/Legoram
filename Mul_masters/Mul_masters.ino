#include <Wire.h>

#define OUTPin 5
#define INPin 3
#define inLED 13
#define rLED 9

#define gLED 8
#define bLED 7

#define THIS_ADDR 8

byte blockCount = 0;
char data[20][26];
bool maybeFinished = false;

void setup() {
 pinMode(INPin, INPUT);
 digitalWrite(INPin,LOW);
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
 data[20][26] = {'-'};
 blockCount = 0;
 
 Wire.begin(THIS_ADDR);
 Wire.onReceive(receiveEvent);
 Serial.begin(9600);
}

void loop() {
 int LEDblock = int(Serial.read());
 if(LEDblock == 0){
    for(int i =0;i<3;i++){
       digitalWrite(gLED,HIGH);
       delay(250);
       digitalWrite(gLED,LOW);
       delay(250);
    }
    for(int j=0;j<20;j++){
      for(int i=0;i<26;i++){
        Serial.write(data[j][i]);
      }
    }
 }
 else if(LEDblock == -1){
    for(int i =0;i<3;i++){
       digitalWrite(rLED,HIGH);
       delay(250);
       digitalWrite(rLED,LOW);
       delay(250);
    }
 }
 else{
    digitalWrite(rLED,HIGH);
    digitalWrite(bLED,HIGH);
    delay(250);
    digitalWrite(rLED,LOW);
    digitalWrite(bLED,LOW);
    delay(250);
    char LED_ADDR = data[LEDblock-1][25];
    Wire.beginTransmission(LED_ADDR);
    Wire.write("run");
    Wire.endTransmission();
 }
}

void receiveEvent(int howMany){
 int No = 0;
 blockCount++;
 while (Wire.available()){
   char c = Wire.read();
   if(No<26){
    data[blockCount-1][No] = c;
    No++;
   }
   else{
    //Serial.println("Out of bound(>26)");
   }
 }
 digitalWrite(inLED, HIGH);
 /*for(int j =1; j<=blockCount; j++){
  for(int i =0; i<25; i++){
    Serial.print(data[j-1][i]);
  }
  Serial.print(int(data[j-1][25]));
  Serial.println();
  Serial.print(j);
  Serial.println();
 }
 Serial.println();
 Serial.println();
 Serial.println();*/
 delay(1000);
 digitalWrite(inLED, LOW);
}

/*void checkFinished(){
 bool allTrue = false;
 if(digitalRead(INPin)==HIGH)
   allTrue = true;
 digitalWrite(gLED,HIGH);
 delay(200);
 digitalWrite(gLED,LOW);
 int i = 0;
 for(;i<1499;i++){
  delay(1);
  if(allTrue == true && digitalRead(INPin)==HIGH)
    allTrue = true;
  else{
    allTrue = false;
    break;
  }
 }
 delay(1499-i);
 digitalWrite(gLED,LOW);
 if(allTrue == true){
  data
  /*if(blockCount==0)
      Serial.println("Error end with 0 block");
  else
      Serial.println("Finished");
 }
}*/
