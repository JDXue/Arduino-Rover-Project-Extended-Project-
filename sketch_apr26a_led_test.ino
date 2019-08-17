int led = 7;
int del = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  Serial.println("LED on");
  digitalWrite(led, HIGH);
  //delay(del);
  //Serial.println("LED off");
  //digitalWrite(led, LOW);
  //delay(del);
}
