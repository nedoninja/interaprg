void setup() {
  pinMode(14, OUTPUT);
  int a = 255;
}

void loop() {
  analogWrite(14, a);
  delay(100);
  int a = a - 1;
  if(a = 0) a = 255;
}
