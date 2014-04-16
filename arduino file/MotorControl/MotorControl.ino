void setup() {

pinMode(4, OUTPUT); //hBridge pin 2
pinMode(10, OUTPUT);//hbridge pin 7
pinMode(6, OUTPUT); // h bridge enable 1 (pin1)
pinMode(7, OUTPUT); //hBridge pin 15
pinMode(8, OUTPUT); //hbridge pin 10
pinMode(9, OUTPUT); // h bridge enable 2 (pin 9)

}
void loop() {
//forward(1000);
//reverse(1000); 
left(900);
//right(900);
stop_motor(2000);

}

void forward(int time){
  digitalWrite(6, HIGH); //enable driver 1 on
  digitalWrite(9, HIGH); //enable driver 2 on
  digitalWrite(4, HIGH); 
  digitalWrite(10, LOW);
  digitalWrite(7, HIGH); 
  digitalWrite(8, LOW);  
  delay(time);
}

void reverse(int time){
  digitalWrite(6, HIGH);//enable driver 1 on
  digitalWrite(9, HIGH);//enable driver 2 on
  digitalWrite(4, LOW); 
  digitalWrite(10, HIGH);
  digitalWrite(7, LOW); 
  digitalWrite(8, HIGH); 
  delay(time);
}

void right(int time){
  digitalWrite(6, HIGH);//enable driver 1 on
  digitalWrite(9, HIGH);//enable driver 2 
  digitalWrite(4, HIGH); //right wheel forward
  digitalWrite(10, LOW);
  digitalWrite(7, LOW); //left wheel reverse
  digitalWrite(8, HIGH);  
  delay(time);
}

void left(int time){
  digitalWrite(6, HIGH);//enable driver 1 on
  digitalWrite(9, HIGH);//enable driver 2 
  digitalWrite(4, LOW); //right wheel reverse 
  digitalWrite(10, HIGH);
  digitalWrite(7, HIGH); //left wheel forward
  digitalWrite(8, LOW);  
  delay(time);
}

void stop_motor(int time){
    digitalWrite(6, LOW);//enable driver 1 on
    digitalWrite(9, LOW);//enable driver 2 
    delay(time);
}
