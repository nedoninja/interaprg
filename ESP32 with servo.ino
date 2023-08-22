#include <ESP32_Servo.h>

Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(13, INPUT);
  myServo.attach(12);
}

void loop() {
  int tempobase = analogRead(13);
  float temp1 = float(27.68 * tempobase) / float(4096); // На улице
  const float temp2 = 27; // В комнате

  Serial.print("\nTemp1 = ");
  Serial.print(temp1);

  if(temp2 < temp1)
    myServo.write(179);
  else myServo.write(0);
  
  delay(2000);
}
