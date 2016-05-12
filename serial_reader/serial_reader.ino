int sensePin = 0;
int counter = 0;
int value = 0;

void setup() {
  analogReference(DEFAULT);
  Serial.begin(9600);
}

void loop() {
  value += analogRead(sensePin);
  counter++;
  if(counter==10){
    value /= counter;
    Serial.println(value);
    counter = 0;
    value = 0;
  }
  delay(5);
}
