void setup() {
  Serial.begin(9600);
  pinMode(13, INPUT);
}

void loop() {
  int tempo = analogRead(13);
  float temp = float(27.68 * tempo) / float(4096);
  Serial.print("\nTemp = ");
  Serial.print(temp);
  delay(500);
}
