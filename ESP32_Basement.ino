#include <ESP32_Servo.h>
#include <Arduino.h>
#include <WiFi.h>

// 2 плата дом             /// Код вроде должен работать

WiFiClient localClient;

const char* ssid = "smartpark_service";
const char* password = "smartpark_2021";

const int port = 80;
const char* ip = "192.168.88.245";

String myPacket;

void sendRequest() {

  if (localClient.connect(ip, port)) {            

      if (localClient.connected()) {
        localClient.println(myPacket);                
        Serial.print("Sended packet: ");
        Serial.println(myPacket);
      }
  }
  
}

String getPacket(){
  
       while (!localClient.available());         
      
      String str = localClient.readStringUntil('\n'); 
      Serial.print("Got packet: ");
      Serial.println(str);
}

void beg(){
  Serial.println("Connect Wlan");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}

Servo myServo;              // объявление "форточки"

const int motoPin = 14;     // номер контакта вентилятора
const int freq = 800;       // частота ШИМ, Гц
const int ledChannel = 0;   // канал ШИМ на ESP32 (разобраться)
const int res = 8;          // квантование ШИМ, бит

void setup() {
  Serial.begin(9600);
  pinMode(34, INPUT);                   // объявление порта термодатчика
  myServo.attach("30");                   // "инициализация" "форточки"                                             ///  Нужно поставить нормальный пин

  beg();

  ledcSetup(ledChannel, freq, res);     // настройка ШИМ для вентилятора
  ledcSetup(1, freq, res);              // настройка ШИМ для встроенного светодиода (индикация скорости работы вентилятора)
  ledcAttachPin(motoPin, ledChannel);   // "инициализация" канала для ШИМ
  ledcAttachPin(2, 1);                  // "инициализация" канала для ШИМ для встроенного светодиода
}

void loop() {
  int temp_datchik = analogRead(34);                           // считывание данных с термодатчика
  float temp1 = float(27.68 * temp_datchik) / float(4096);     // расчёт температуры в "подвале"
  String s = "";
  s = s + "2;" + String(temp1);
  sendRequest();

  String pack = getPacket();

  /// Pack состоит из "Состояние форточки; Скорость вентилятора"
  if(pack[0] == 1)
    myServo.write(179)      // открыли форточку
  else myServo.write(0)     // Закрыли форточку

  int spd = 0;
  for(int i=2; i<pack.size(); i++){
    spd *= 10;
    spd += pack[i];
  }

  spd = map(spd, 0, 20, 0, 255);
  
  // пробная программа управления вентилятором  
  ledcWrite(ledChannel, spd);       // ШИМ на вентилятор
  ledcWrite(1, spd);       // ШИМ на встроенный светодиод
  
  delay(250);
}
