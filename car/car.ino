#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;
const int FL = 8;
const int BL = 3;
const int H = 2;
const int En = 9;


#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name
int s=0;
char t;

void moveForward();
void moveStop();
void turnLeft();
void turnRight();
void moveBackward();
void moveForwardA();
void moveStopA();
void turnLeftA();
void turnRightA();
void moveBackwardA();

void setup() {
  
 pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(11); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

Serial.begin(9600);
 
}
 
void loop() {
  int y = map(s,0,100,0,255);
  Serial.print(y);
  Serial.print("      ");
  analogWrite(En,y);
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
if(Serial.available()){
  t = Serial.read();
  Serial.print(t);
  Serial.print("      ");
}
if(t=='x'){
  if(t == 'F'){            //move forward(all motors rotate in forward direction)
  moveForwardA();
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  moveBackwardA();
  
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  turnLeftA();
  
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  turnRightA();
 
}
 
else if(t == 'S'){      //STOP (all motors stop)
  moveStopA();
}
else{
  moveStopA();
}
delay(10);
}
else if(t == 'X'){
  if (distance <= 20){
    Serial.println(distance);
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      
      moveStop();
    }
    else{
      turnLeft();
      
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
  }
else{
  moveStop();
}
  if(t == 'W'){digitalWrite(FL,HIGH);}
  else if(t == 'w'){digitalWrite(FL,LOW);} else{digitalWrite(FL,LOW);}
  if(t == 'U'){digitalWrite(BL,HIGH);}
  else if(t == 'u'){digitalWrite(BL,LOW);}else{digitalWrite(BL,LOW);}
  if(t == 'V'){digitalWrite(H,HIGH);}
  else if(t == 'v'){digitalWrite(H,LOW);}else{digitalWrite(H,LOW);}
  if(t == '0'){s=0;}
  else if(t == '1'){s=10;}
  else if(t == '2'){s=20;}
  else if(t == '3'){s=30;}
  else if(t == '4'){s=40;}
  else if(t == '5'){s=50;}
  else if(t == '6'){s=60;}
  else if(t == '7'){s=70;}
  else if(t == '8'){s=80;}
  else if(t == '9'){s=90;}
  else if(t == 'q'){s=100;}
  else{s=70;}
  
delay(10);
}

int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStopA(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForwardA(){

    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }


void moveBackwardA(){


  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}

void turnRightA(){

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
    
}

void turnLeftA(){

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);  
}

void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }
}

void moveBackward(){

  goesForward=false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}

void turnRight(){

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
 
  
  
}

void turnLeft(){

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
