#include <ArduinoSTL.h>
#include <stack>
using namespace std;
#define IR_FRONT A0
#define IR_LEFT A1
#define IR_RIGHT A2
#define MOTORA1 9  //PB1
#define MOTORA2 10  //PB2
#define MOTORB1 11  //PB3
#define MOTORB2 12  //PB4

int front_input;
int left_input;
int right_input;
enum directions{LEFT=-1,RIGHT=1,FORWARD=0,UTURN};
stack<directions> trace;
bool take_uturn = false;

void setup() {
  Serial.begin(9600);
  pinMode(MOTORA1,OUTPUT);
  pinMode(MOTORA2,OUTPUT);
  pinMode(MOTORB1,OUTPUT);
  pinMode(MOTORB2,OUTPUT);
  pinMode(IR_FRONT,INPUT);
  pinMode(IR_LEFT,INPUT);
  pinMode(IR_RIGHT,INPUT);
  trace = new stack();
}

void go(directions dir){
  switch(dir){
    case LEFT:
      break;
    case UTURN:
      break;
    case RIGHT:
      break;
    default:
      break;
  }
}
void loop() {
   front_input = digitalRead(IR_FRONT);
   left_input = digitalRead(IR_LEFT);
   right_input = digitalRead(IR_RIGHT);
   //Stack Left-->Front-->Right
   if(left_input!=1 && right_input!=1){
     go(FORWARD);
   }else{
     if(!take_uturn){
       if(left_input){
          trace.push(LEFT);
          go(LEFT);
       }
       else if(front_input){
          trace.push(FORWARD);
          go(FORWARD);
       }
       else if(right_input){
          trace.push(RIGHT);
          go(RIGHT);
       }
       else{
          take_uturn = true;
       }
     }else{
       if(left_input){
          if(trace.top() == RIGHT){
            trace.pop();
          }
          else if(trace.top()==FORWARD){
            //trace.pop();
            take_uturn=false;
          }
          else if(trace.top()==LEFT){
            take_uturn =false;
          }
          go(LEFT);
       }else if(front_input){
          if(trace.top()==LEFT){
            take_uturn=false;
          }
          go(FORWARD);
       }
       else if(right_input){
          if(trace.top() == LEFT){
            trace.pop();
          }
          go(RIGHT);
       }
     }
   }
   
}
