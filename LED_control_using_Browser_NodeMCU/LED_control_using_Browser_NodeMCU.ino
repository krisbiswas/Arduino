//Visit www.roboshala.com for more details on NodeMCU and other projects.

#include <ESP8266WiFi.h>
 
const char* ssid = "WiFi_SSID"; // SSID i.e. Service Set Identifier is the name of your WIFI
const char* password = "PASSWORD"; // Your Wifi password, in case you have open network comment the whole statement.
 
//int ledPin = 13; // GPIO13 or for NodeMCU you can directly write D7 
WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in this case port is 80.
int leftMotor1 = D5;
int leftMotor2 = D6;
int rightMotor1 = D7;
int rightMotor2 = D8;
int onState = 0;
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
//  pinMode(ledPin, OUTPUT);
//  digitalWrite(ledPin, LOW);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT); 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //Gets the WiFi shield's IP address and Print the IP address on serial monitor
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
//  int value = LOW;
  String value = "";
  if (request.indexOf("/start") != -1)  {
    digitalWrite(LED_BUILTIN, HIGH);
    value = "STARTED";
    onState = 1;
  }
  if (request.indexOf("/stop") != -1)  {
    digitalWrite(LED_BUILTIN, LOW);
    value = "STOPPED";
    onState = 0;
  }
  if(onState == 1){
    if (request.indexOf("/left") != -1)  {
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, HIGH);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      value = "LEFT";
    }
    if (request.indexOf("/right") != -1)  {
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, HIGH);
      value = "RIGHT";
    }
    if (request.indexOf("/up") != -1)  {
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      value = "FORWORD";
    }
    if (request.indexOf("/down") != -1)  {
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, HIGH);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, HIGH);
      value = "BACKWORD";
    }
  }else{
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return HTTP the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
//  client.print("Led pin is now: ");
  client.print("Its moving: ");
  client.print(value);
//  if(value == HIGH) {
//    client.print("On");
//  } else {
//    client.print("Off");
//  }
  client.println("<br><br>");
  client.println("<a href=\"/left\"\"><button> LEFT </button></a>");
  client.println("<a href=\"/right\"\"><button> RIGHT </button></a><br />");
  client.println("<a href=\"/up\"\"><button> UP </button></a>");
  client.println("<a href=\"/down\"\"><button> DOWN </button></a><br />");
  client.println("<a href=\"/start\"\"><button> START </button></a>");
  client.println("<a href=\"/stop\"\"><button> STOP </button></a><br />");
//  client.println("5% <input type=\"range" "min=\"5" "max=\"200" "step=\"5" "value=\"100" "onchange=\"updateSlider(this.value)"> "200%<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
