const int motoPin = 14;     // номер контакта вентилятора
const int freq = 4500;      // частота ШИМ, Гц
const int ledChannel = 0;   // канал ШИМ на ESP32 (разобраться)
const int res = 8;          // квантование ШИМ, бит

void setup() {
  ledcSetup(ledChannel, freq, res);     // настройка ШИМ для вентилятора
  ledcSetup(1, freq, res);              // настройка ШИМ для встроенного светодиода (только для проверки работоспособности ШИМ)
  ledcAttachPin(ledPin, ledChannel);    // "инициализация" канала для ШИМ
  ledcAttachPin(2, 1);                  // "инициализация" канала для ШИМ для встроенного светодиода
}

void loop() {
  // пробная программа управления вентилятором
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {   
    ledcWrite(ledChannel, dutyCycle);       // ШИМ на вентилятор
    ledcWrite(1, dutyCecle);       // ШИМ на встроенный светодиод
    delay(15);
  }

  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    ledcWrite(ledChannel, dutyCycle);       // ШИМ на вентилятор
    ledcWrite(1, dutyCecle);       // ШИМ на встроенный светодиод
    delay(15);
  }
}
