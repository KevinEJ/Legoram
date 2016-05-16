int outPin = 9;
int val = 0;

int sensePin = 0;
int counter = 0;
int value = 0;

void setup() {
  analogReference(DEFAULT);
  //pinMode(sensePin,INPUT);
  Serial.begin(9600);
}

void loop() {
  counter++;
  if(counter==50){
    //value /= counter;
    value = analogRead(sensePin);
    int ID = (value-2)/4;
    Serial.println(ID);
    //delay(100);
  }
  else if(counter==100)
    counter=0;
  delay(10);
}
