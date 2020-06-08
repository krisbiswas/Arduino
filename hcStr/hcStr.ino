#include<SoftwareSerial.h>
SoftwareSerial Ser(10,11);
String inputString;

void setup(){

    Serial.begin(9600);
    Ser.begin(9600);
    pinMode(13,HIGH);
}
void loop(){
    if(Ser.available()){
        while(Ser.available()){                
            delay(3);
            char inChar = (char)Ser.read();
            inputString += inChar;
        }
        if(inputString.equalsIgnoreCase("ON")){
          digitalWrite(13,HIGH);
        }else if(inputString.equalsIgnoreCase("OFF")){
          digitalWrite(13,LOW);
        }

        Serial.println(inputString);
        inputString = "";
        }
}
