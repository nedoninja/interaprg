#include <Arduino.h>
#include <WiFi.h>

// 1 плата улица

WiFiClient localClient;

const char* ssid = "smartpark_service";
const char* password = "smartpark_2021";

const int port = 4242;
const char* ip = "192.168.88.245";

String myPacket;

void sendRequest() {

  if (localClient.connect(ip, port)) {

      if (localClient.connected()) {
        localClient.println(myPacket);
        Serial.print("sended: ");
        Serial.println(myPacket);
      }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Connect Wlan");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  pinMode(13, INPUT);
}

void loop() {
  int tempo = analogRead(13);
  float temp = float(27.68 * tempo) / float(4096);
  String s;
  s = s + "1;" + String(temp) + '\n';
  myPacket = s;
  sendRequest();
  delay(200);
}
