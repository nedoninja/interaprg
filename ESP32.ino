void setup() {
  Serial.begin(9600);
  pinMode(13, INPUT);
}

void loop() {
  int temp = analogRead(13);
  delay(500);
}
