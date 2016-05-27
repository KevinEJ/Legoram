#include <Wire.h>

#define INPin 3
#define OUTPin 5
#define UINPin 2
#define UOUTPin 4
#define paraNum 1
#define rLED 9
#define gLED 8
#define bLED 7

#define THIS_ADDR 50
#define MASTER_ADDR 8

bool dataSent = false;
bool loopEnd = false;

char loop_cmd[26] = {'l','o','o','p',' ',' ',
                  ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                  ' ',' ',' ',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};

void setup() {
 pinMode(INPin, INPUT);
 pinMode(UINPin, INPUT);
 pinMode(DINPin, INPUT);
 pinMode(paraPinUp, INPUT);
 pinMode(paraPinDown, INPUT);
 pinMode(OUTPin, OUTPUT);
 digitalWrite(OUTPin, LOW);
 pinMode(UOUTPin, OUTPUT);
 digitalWrite(UOUTPin, LOW);
 pinMode(DOUTPin, OUTPUT);
 digitalWrite(DOUTPin, LOW);
 pinMode(rLED, OUTPUT);
 digitalWrite(rLED, LOW);
 pinMode(gLED, OUTPUT);
 digitalWrite(gLED, LOW);
 pinMode(bLED, OUTPUT);
 digitalWrite(bLED, LOW);
 
 Wire.begin(THIS_ADDR);
 Wire.onReceive(receiveEvent);
 dataSent = false;
 elseStart = false;
 elseEnd = false;
}

bool whetherHIGH_ori(int pin){
  bool allTrue = false;
  if(digitalRead(pin)==HIGH)
    allTrue = true;
  int i = 0;
  for(;i<1499;i++){
    delay(1);
    if(allTrue == true && digitalRead(pin)==HIGH)
      allTrue = true;
    else{
      allTrue = false;
      break;
    }
  }
  return allTrue;
}

bool whetherHIGH_end(int pin){
  bool allTrue = false;
  if(digitalRead(pin)==HIGH)
    allTrue = true;
  digitalWrite(bLED,HIGH);
  digitalWrite(rLED,HIGH);
  delay(200);
  digitalWrite(bLED,LOW);
  digitalWrite(rLED,LOW);
  int i = 0;
  for(;i<1499;i++){
    delay(1);
    if(allTrue == true && digitalRead(pin)==HIGH)
      allTrue = true;
    else{
      allTrue = false;
      break;
    }
  }
  delay(1499-i);
  digitalWrite(bLED,LOW);
  digitalWrite(rLED,LOW);
  return allTrue;
}

void loop() {
  if(loopEnd == false && dataSent == true && whetherHIGH_end(UINPin) ){
    Wire.beginTransmission(MASTER_ADDR);
    Wire.write(else_end_cmd);
    Wire.endTransmission();
    digitalWrite(DOUTPin,HIGH);
    elseEnd = true;
    for(int i =1; i<=3;i++){
      digitalWrite(gLED,HIGH);
      delay(250);
      digitalWrite(gLED,LOW);
      delay(250);
    }
 }
 else if (whetherHIGH_ori(INPin)){
   char num = analogRead(paraNum);
   loop_cmd[5] = num;
   Wire.beginTransmission(MASTER_ADDR);
   Wire.write(loop_cmd);
   Wire.endTransmission();
   digitalWrite(OUTPin,HIGH);
   dataSent = true;
   for(int i =1; i<=3;i++){
    digitalWrite(gLED,HIGH);
    delay(250);
    digitalWrite(gLED,LOW);
    delay(250);
   }
}

void receiveEvent(int howMany){
 while (Wire.available() > 0){
   char c = Wire.read();
   if(c == 'R'){
      LEDrun();
   }
   else if(c == 'W'){
      LEDwin(); 
   }
 }
}

void LEDrun(){
   digitalWrite(rLED,LOW);
   digitalWrite(gLED,HIGH);
   digitalWrite(bLED,HIGH);
   delay(200);
   digitalWrite(rLED,LOW);
   digitalWrite(gLED,LOW);
   digitalWrite(bLED,HIGH);
   delay(200);
   digitalWrite(rLED,LOW);
   digitalWrite(gLED,HIGH);
   digitalWrite(bLED,LOW);
   delay(200);
   digitalWrite(rLED,LOW);
   digitalWrite(gLED,LOW);
   digitalWrite(bLED,LOW);
}

void LEDwin(){
   digitalWrite(rLED,HIGH);
   digitalWrite(gLED,LOW);
   digitalWrite(bLED,LOW);
   delay(100);
   digitalWrite(rLED,HIGH);
   digitalWrite(gLED,HIGH);
   digitalWrite(bLED,LOW);
   delay(100);
   digitalWrite(rLED,LOW);
   digitalWrite(gLED,HIGH);
   digitalWrite(bLED,LOW);
   delay(100);
   digitalWrite(rLED,LOW);
   digitalWrite(gLED,HIGH);
   digitalWrite(bLED,HIGH);
   delay(100);
   digitalWrite(rLED,LOW);
   digitalWrite(gLED,LOW);
   digitalWrite(bLED,HIGH);
   delay(100);
   digitalWrite(rLED,HIGH);
   digitalWrite(gLED,LOW);
   digitalWrite(bLED,HIGH);
   delay(100);
   digitalWrite(rLED,LOW);
   digitalWrite(gLED,LOW);
   digitalWrite(bLED,LOW);
}
