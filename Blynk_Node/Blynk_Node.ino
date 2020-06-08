#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "0DBtrkKnfwnLagnlf115KTHhpJ3OEj1g";

char ssid[] = "SSID";
char pass[] = "PASSWORD";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
//  Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    Blynk.begin(auth, ssid, pass);
    delay(500);
    Serial.print(".");
  }
  Serial.println(analogRead(A0));
  
  Blynk.run();
}
