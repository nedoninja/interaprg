#include <Arduino.h>
#include <WiFi.h>

// 1 плата улица

WiFiClient localClient;

const char* ssid = "rasp3";
const char* password = "";

const int port = 80;
const char* ip = "10.42.0.1";

void sendRequest(String myPacket) {

  if (localClient.connect(ip, port)) {

      if (localClient.connected()) {
        localClient.println(myPacket);
        Serial.print("sended: ");
        Serial.println(myPacket);
      }
  }
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

void setup() {
  Serial.begin(9600);
  pinMode(34, INPUT);
  beg();
}

void loop() {
  int tempo = analogRead(34);
  float temp = float(27.68 * tempo) / float(4096);
  Serial.println(temp);
  String s = "";
  s = s + "1;" + String(temp);
  sendRequest(s);
  delay(1000);
}
