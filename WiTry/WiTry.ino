#include<ESP8266Wifi.h>

const char* ssid = "Lenovo";
const char* password = "Krisbiswas";

WifiServer server(20);
void setup() {
  // put your setup code here, to run once:
  Wifi.begin(ssid,password);
  Serial.begin(115200);
  while(Wifi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.print("ESP Connected to "+ssid);
  Serial.print("Local IP"+Wifi.localIP());
  server.start();
}

void loop() {
  // put your main code here, to run repeatedly:

}
