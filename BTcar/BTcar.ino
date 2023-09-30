char t;
int s =120; 
void setup() {
pinMode(12,OUTPUT);   //left motors forward
pinMode(11,OUTPUT);   //left motors reverse
pinMode(10,OUTPUT);   //right motors forward
pinMode(9,OUTPUT);   //right motors reverse
pinMode(6,OUTPUT);

Serial.begin(9600);
 
}
 
void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
  digitalWrite(12,HIGH);
  digitalWrite(10,HIGH);
  analogWrite(6,s);
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(11,HIGH);
  digitalWrite(9,HIGH);
  analogWrite(6,s);
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  analogWrite(6,s);
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(12,HIGH);
  digitalWrite(9,HIGH);
  analogWrite(6,s);
}
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  digitalWrite(9,LOW);
}
delay(100);
}
