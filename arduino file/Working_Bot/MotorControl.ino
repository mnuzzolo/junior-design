
void forward(int time){
  digitalWrite(6, HIGH); //enable driver 1 on
  digitalWrite(9, HIGH); //enable driver 2 on
  analogWrite(4, DUTY_CYCLE); 
  analogWrite(10, 0);
  analogWrite(7, DUTY_CYCLE-20); 
  analogWrite(8, 0);  
  delay(time);
}

void reverse(int time){
  digitalWrite(6, HIGH); //enable driver 1 on
  digitalWrite(9, HIGH); //enable driver 2 on
  analogWrite(4, 0); 
  analogWrite(10, DUTY_CYCLE);
  analogWrite(7, 0); 
  analogWrite(8, DUTY_CYCLE); 
  delay(time);
}

void left(int time){
  digitalWrite(6, HIGH); //enable driver 1 on
  digitalWrite(9, HIGH); //enable driver 2 on
  analogWrite(4, DUTY_CYCLE); //right wheel forward
  analogWrite(10, 0);
  analogWrite(7, 0); //left wheel reverse
  analogWrite(8, DUTY_CYCLE);  
  delay(time);
}

void right(int time){
  digitalWrite(6, HIGH); //enable driver 1 on
  digitalWrite(9, HIGH); //enable driver 2 on
  analogWrite(4, 0); //right wheel reverse 
  analogWrite(10, DUTY_CYCLE);
  analogWrite(7, DUTY_CYCLE); //left wheel forward
  analogWrite(8, 0);  
  delay(time);
}

void pivot_right_forward(int time){
  digitalWrite(6, LOW); //enable driver 1 off
  digitalWrite(9, HIGH); //enable driver 2 on
  analogWrite(4, 0); //right wheel reverse 
  analogWrite(10, DUTY_CYCLE);
  analogWrite(7, DUTY_CYCLE); //left wheel forward
  analogWrite(8, 0);  
  delay(time);
}

void pivot_right_backward(int time){
  digitalWrite(6, LOW); //enable driver 1 off
  digitalWrite(9, HIGH); //enable driver 2 on
  analogWrite(4, 0); //right wheel reverse 
  analogWrite(10, DUTY_CYCLE);
  analogWrite(7, 0); //left wheel backwards
  analogWrite(8, DUTY_CYCLE);  
  delay(time);
}

void stop_motor(int time){
  //digitalWrite(6, LOW); //enable driver 1 off
  //digitalWrite(9, LOW); //enable driver 2 off
  analogWrite(4, 0); //right wheel reverse 
  analogWrite(10, 0);
  analogWrite(7, 0); //left wheel backwards
  analogWrite(8, 0);  
  delay(time);
}
