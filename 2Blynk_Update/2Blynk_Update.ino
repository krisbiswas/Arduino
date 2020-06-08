#include <BlynkSimpleSerialBLE.h>
#include<SoftwareSerial.h>
char auth[] = "511305cce4754ceda359a4f27dc2826d";
//char auth2[] = "78a30d0b6ca94152a22f16cc71227c21";
SoftwareSerial mySerial(3,2);     //(Rx,Tx)
BlynkTimer timer;

#define kBulb 8
#define fan 9
#define roomBulb 10
#define oBulb 11
#define Temp  A0
#define PIR  A1
#define LDR  A2
void TempSense();
void KBULB();
void OBULB();
void timerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  float sensorData = analogRead(A0);
  sensorData*=(500.0/1024);
  Blynk.virtualWrite(V1, sensorData);
}
//BLYNK_WRITE(V1)
//{
//  int sensorData = analogRead(Temp);
//  //sensorData*=(500/1024);
//  Blynk.virtualWrite(V1, sensorData);
//}
int Tstate2;
BLYNK_WRITE(V0){      //Temperature AutoSense
  int Tstate = param.asInt();
  if(digitalRead(fan)==1){
    if(Tstate == 1){
      TempSense();
      Tstate2=1;
    }
    else if(Tstate == 0){
      analogWrite(fan,100);
      Tstate2=0;
    }
  }
}
BLYNK_WRITE(V9){      //FAN
  float Speed = param.asFloat();
  if(digitalRead(fan)==1){
    analogWrite(fan,Speed);
  }
}
BLYNK_WRITE(V10){     //RoomBULB
  float intensity = param.asFloat();
  if(digitalRead(roomBulb)==1){
    analogWrite(roomBulb,intensity);
  }
}
int Kstate;
BLYNK_WRITE(V8){      //KBULB
  int v = param.asInt();
  if(v!=0){
    Kstate = 1;
  }if(v == 0){
    Kstate = 0;
  }
}
int Ostate;
BLYNK_WRITE(V11){      //OBULB
  int v = param.asInt();
  if(v!=0){
    Ostate = 1;
  }if(v==0){
    Ostate = 0;
  }
}

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Blynk.begin(mySerial,auth);
    
  pinMode(kBulb,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(roomBulb,OUTPUT);
  pinMode(oBulb,OUTPUT);
  pinMode(Temp,INPUT);
  pinMode(PIR,INPUT);
  pinMode(LDR,INPUT);
  
  Serial.println("Waiting for connections...");
  timer.setInterval(1000L, timerEvent);
}

void loop() {
  Blynk.run();
  timer.run();
  if(Tstate2 == 1){
    TempSense();
  }
  if(Kstate == 1){
    KBULB();
  }
  if(Kstate == 0){
    digitalWrite(kBulb,LOW);
  }
  if(Ostate == 1){
    OBULB();
  }
  if(Ostate == 0){
    digitalWrite(oBulb,LOW);
  }
}
//             KBULB
void KBULB(){
  int pirValue = digitalRead(PIR);
  if (pirValue == 1) {
    digitalWrite(kBulb, HIGH);
    Serial.println("Motion detected!");
  } 
  else if(pirValue == 0){
    digitalWrite(kBulb, LOW);
    Serial.println("Motion ended!");
  }
}
//             OBULB
void OBULB(){
  int ldr = analogRead(LDR);
  float ldr8bit = ldr/4.0;
  Serial.print(ldr8bit);
  if(ldr8bit>135){
    digitalWrite(oBulb,LOW);
  }
  else if(ldr8bit>100 && ldr8bit<=120){
    analogWrite(oBulb,125);
  }
  else if(ldr8bit>50 && ldr8bit<=100){
   analogWrite(oBulb,180);
  }
  else if(ldr8bit<80){
    analogWrite(oBulb,255);
  }
}
//      TEMP SENSE
void TempSense(){                 //Function for Temperature calc. & speed regulation
  if(digitalRead(fan)==1){
    float TempValue = analogRead(Temp);
    float cel = (TempValue/1024.0)*500.0;
    Serial.print(cel);Serial.println(" C");
      analogWrite(fan,TempValue/4.0);
//    if(cel<=12){
//      analogWrite(fan,0);
//    }
//    else if(cel>12 && cel<=15){
//      analogWrite(fan,51);
//    }
//    else if(cel>15 && cel<=22){
//      analogWrite(fan,75);
//    }
//    else if(cel>22 && cel<=17){
//      analogWrite(fan,100);
//    }
//    else if(cel>27 && cel<=32){
//      analogWrite(fan,135);
//    }
//    else if(cel>32 && cel<=40){
//      analogWrite(fan,165);
//    }
//    else if(cel>40 && cel<=46){
//      analogWrite(fan,200);
//    }
//    else{
//      analogWrite(fan,255);
//    }
  }
  else if(digitalRead(fan)==0){
    digitalWrite(fan,LOW);
  }
}
