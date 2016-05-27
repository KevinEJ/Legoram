#include <Wire.h>

#define INPin 3
#define OUTPin 5
#define paraPin 1
#define rLED 9
#define gLED 8
#define bLED 7

#define THIS_ADDR 36
#define MASTER_ADDR 8

bool dataSent = false;
char can_cmd[26] = {'b','u','i','l','d',' ',
                  'c','a','n','n','o','n',' ',' ',' ',' ',
                  ' ',' ',' ',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};
char wal_cmd[26] = {'b','u','i','l','d',' ',
                  'w','a','l','l',' ',' ',' ',' ',' ',' ',
                  ' ',' ',' ',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};
char man_cmd[26] = {'b','u','i','l','d',' ',
                  'm','a','n',' ',' ',' ',' ',' ',' ',' ',
                  ' ',' ',' ',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};

char invalid_cmd[26] = {'E','r','r','o','r',' ',
                  'p','a','r','a','m','e','t','e','r',' ',
                  ' ',' ',' ',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};

void setup() {
 pinMode(INPin, INPUT);
 pinMode(paraPin, INPUT);
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

bool whetherHIGH(int pin){
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

void loop() {
 if (whetherHIGH(INPin) && dataSent == false){
   Wire.beginTransmission(MASTER_ADDR);
   if(analogRead(paraPin)>=938)
    Wire.write(can_cmd);
   else if(analogRead(paraPin)<=85)
    Wire.write(man_cmd);
   else if(analogRead(paraPin)<597 && analogRead(paraPin)>427)
    Wire.write(wal_cmd);
   else
    Wire.write(invalid_cmd);
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
 else if(dataSent = true){
  digitalWrite(OUTPin,HIGH);
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
