#include <Wire.h>

#define INPin 3
#define OUTPin 5
#define UINPin 2
#define UOUTPin 4
#define DINPin 12
#define DOUTPin 10 
#define paraPinUp 2
#define paraPinDown 0
#define rLED 9
#define gLED 8
#define bLED 7

#define THIS_ADDR 42
#define MASTER_ADDR 8

bool dataSent = false;
bool elseStart = false;
bool elseEnd = false;

char eman_man_cmd[26] = {'e','_','i','f',' ','e',
                  '_','m','a','n',' ','>',' ','m','_','m',
                  'a','n',' ',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};
char man_eman_cmd[26] = {'e','_','i','f',' ','m',
                  '_','m','a','n',' ','>',' ','e','_','m',
                  'a','n',' ',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};

char eman_wal_cmd[26] = {'e','_','i','f',' ','e',
                  '_','m','a','n',' ','>',' ','m','_','w',
                  'a','l','l',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};
char man_ewal_cmd[26] = {'e','_','i','f',' ','m',
                  '_','m','a','n',' ','>',' ','e','_','w',
                  'a','l','l',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};
                  
char eman_can_cmd[26] = {'e','_','i','f',' ','e',
                  '_','m','a','n',' ','>',' ','m','_','c',
                  'a','n','n','o','n',' ',' ',' ',
                  '\n',THIS_ADDR};
char man_ecan_cmd[26] = {'e','_','i','f',' ','m',
                  '_','m','a','n',' ','>',' ','e','_','c',
                  'a','n','n','o','n',' ',' ',' ',
                  '\n',THIS_ADDR};

char ewal_man_cmd[26] = {'e','_','i','f',' ','e',
                  '_','w','a','l','l',' ','>',' ','m','_',
                  'm','a','n',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};
char wal_eman_cmd[26] = {'e','_','i','f',' ','m',
                  '_','w','a','l','l',' ','>',' ','e','_',
                  'm','a','n',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};

char ewal_wal_cmd[26] = {'e','_','i','f',' ','e',
                  '_','w','a','l','l',' ','>',' ','m','_',
                  'w','a','l','l',' ',' ',' ',' ',
                  '\n',THIS_ADDR};
char wal_ewal_cmd[26] = {'e','_','i','f',' ','m',
                  '_','w','a','l','l',' ','>',' ','e','_',
                  'w','a','l','l',' ',' ',' ',' ',
                  '\n',THIS_ADDR};

char ewal_can_cmd[26] = {'e','_','i','f',' ','e',
                  '_','w','a','l','l',' ','>',' ','m','_',
                  'c','a','n','n','o','n',' ',' ',
                  '\n',THIS_ADDR};
char wal_ecan_cmd[26] = {'e','_','i','f',' ','m',
                  '_','w','a','l','l',' ','>',' ','e','_',
                  'c','a','n','n','o','n',' ',' ',
                  '\n',THIS_ADDR};

char ecan_man_cmd[26] = {'e','_','i','f',' ','e',
                  '_','c','a','n','n','o','n',' ','>',' ',
                  'm','_','m','a','n',' ',' ',' ',
                  '\n',THIS_ADDR};
char can_eman_cmd[26] = {'e','_','i','f',' ','m',
                  '_','c','a','n','n','o','n',' ','>',' ',
                  'e','_','m','a','n',' ',' ',' ',
                  '\n',THIS_ADDR};

char ecan_wal_cmd[26] = {'e','_','i','f',' ','e',
                  '_','c','a','n','n','o','n',' ','>',' ',
                  'm','_','w','a','l','l',' ',' ',
                  '\n',THIS_ADDR};
char can_ewal_cmd[26] = {'e','_','i','f',' ','m',
                  '_','c','a','n','n','o','n',' ','>',' ',
                  'e','_','w','a','l','l',' ',' ',
                  '\n',THIS_ADDR};

char ecan_can_cmd[26] = {'e','_','i','f',' ','e',
                  '_','c','a','n','n','o','n',' ','>',' ',
                  'm','_','c','a','n','n','o','n',
                  '\n',THIS_ADDR};
char can_ecan_cmd[26] = {'e','_','i','f',' ','m',
                  '_','c','a','n','n','o','n',' ','>',' ',
                  'e','_','c','a','n','n','o','n',
                  '\n',THIS_ADDR};

char else_cmd[26] = {'e','_','e','l','s','e',
                  ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                  ' ',' ',' ',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};

char else_end_cmd[26] = {'e','n','d',' ',' ',' ',
                  ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
                  ' ',' ',' ',' ',' ',' ',' ',' ',
                  '\n',THIS_ADDR};

char invalid_cmd[26] = {'E','r','r','o','r',' ',
                  'p','a','r','a','m','e','t','e','r',' ',
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

bool whetherHIGH(int pin){
  bool allTrue = false;
  if(digitalRead(pin)==HIGH)
    allTrue = true;
  digitalWrite(bLED,HIGH);
  delay(200);
  digitalWrite(bLED,LOW);
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
 if (whetherHIGH_ori(INPin) && dataSent == false){
   Wire.beginTransmission(MASTER_ADDR);
   if(analogRead(paraPinUp)<380 && analogRead(paraPinUp)>=300 && analogRead(paraPinDown)>=938)
    Wire.write(ewal_can_cmd);
   else if(analogRead(paraPinUp)<380 && analogRead(paraPinUp)>=300 && analogRead(paraPinDown)<=85)
    Wire.write(ewal_man_cmd);
   else if(analogRead(paraPinUp)<380 && analogRead(paraPinUp)>=300 &&  analogRead(paraPinDown)<597 && analogRead(paraPinDown)>427)
    Wire.write(ewal_wal_cmd);
   else if(analogRead(paraPinDown)<380 && analogRead(paraPinDown)>=300 && analogRead(paraPinUp)>=938)
    Wire.write(can_ewal_cmd);
   else if(analogRead(paraPinDown)<380 && analogRead(paraPinDown)>=300 && analogRead(paraPinUp)<=85)
    Wire.write(man_ewal_cmd);
   else if(analogRead(paraPinDown)<380 && analogRead(paraPinDown)>=300 &&  analogRead(paraPinUp)<597 && analogRead(paraPinUp)>427)
    Wire.write(wal_ewal_cmd);
   else
    Wire.write();
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
 else if(dataSent == true && elseStart == false && whetherHIGH(UINPin) ){
  Wire.beginTransmission(MASTER_ADDR);
  Wire.write(else_cmd);
  Wire.endTransmission();
  digitalWrite(UOUTPin,HIGH);
  elseStart = true;
  for(int i =1; i<=3;i++){
    digitalWrite(gLED,HIGH);
    delay(250);
    digitalWrite(gLED,LOW);
    delay(250);
   }
 }
 else if(elseStart == true && elseEnd == false && whetherHIGH_end(DINPin)){
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
 else
    digitalWrite(gLED,LOW);
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
