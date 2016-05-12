int outPin = 3;
int ledPin = 13;
int brightness = 255;
int light=1;

void setup() {
  pinMode(outPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  analogWrite(outPin, brightness);
  digitalWrite(ledPin, light);
  //Serial.println(brightness);
  delay(50);
  if(brightness>=255)
    brightness=0;
  else
    brightness+=5;
  if(light==1)
    light=0;
  else
    light=1;
}
