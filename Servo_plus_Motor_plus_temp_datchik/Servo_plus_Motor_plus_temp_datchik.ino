#include <ESP32_Servo.h>

Servo myServo;              // объявление "форточки"

const int motoPin = 14;     // номер контакта вентилятора
const int freq = 800;       // частота ШИМ, Гц
const int ledChannel = 0;   // канал ШИМ на ESP32 (разобраться)
const int res = 8;          // квантование ШИМ, бит

void setup() {
  pinMode(13, INPUT);                   // объявление порта термодатчика

  myServo.attach(12);                   // "инициализация" "форточки"

  ledcSetup(ledChannel, freq, res);     // настройка ШИМ для вентилятора
  ledcSetup(1, freq, res);              // настройка ШИМ для встроенного светодиода (индикация скорости работы вентилятора)
  ledcAttachPin(motoPin, ledChannel);   // "инициализация" канала для ШИМ
  ledcAttachPin(2, 1);                  // "инициализация" канала для ШИМ для встроенного светодиода
}

void loop() {
  int temp_datchik = analogRead(13);                           // считывание данных с термодатчика
  float temp1 = float(27.68 * temp_datchik) / float(4096);     // расчёт температуры в "подвале"

  /*
  myServo.write(a)      // команда для "форточки", где 
                        // а = 0 - "закрыто"
                        // a = 179 - "открыто"
  */

  /*
  // пробная программа управления вентилятором
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {   
    ledcWrite(ledChannel, dutyCycle);       // ШИМ на вентилятор
    ledcWrite(1, dutyCycle);       // ШИМ на встроенный светодиод
    delay(15);
  }

  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    ledcWrite(ledChannel, dutyCycle);       // ШИМ на вентилятор
    ledcWrite(1, dutyCycle);       // ШИМ на встроенный светодиод
    delay(15);
  }
  */
}
