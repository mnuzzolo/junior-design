
void forward(int time){
  analogWrite(A2, DUTY_CYCLE); //enable driver 1 on
  analogWrite(A3, DUTY_CYCLE); //enable driver 2 on
  digitalWrite(4, HIGH); 
  digitalWrite(10, LOW);
  digitalWrite(7, HIGH); 
  digitalWrite(8, LOW);  
  delay(time);
}

void reverse(int time){
  analogWrite(A2, DUTY_CYCLE); //enable driver 1 on
  analogWrite(A3, DUTY_CYCLE); //enable driver 2 on
  digitalWrite(4, LOW); 
  digitalWrite(10, HIGH);
  digitalWrite(7, LOW); 
  digitalWrite(8, HIGH); 
  delay(time);
}

void left(int time){
  analogWrite(A2, DUTY_CYCLE); //enable driver 1 on
  analogWrite(A3, DUTY_CYCLE); //enable driver 2 on
  digitalWrite(4, HIGH); //right wheel forward
  digitalWrite(10, LOW);
  digitalWrite(7, LOW); //left wheel reverse
  digitalWrite(8, HIGH);  
  delay(time);
}

void right(int time){
  analogWrite(A2, DUTY_CYCLE); //enable driver 1 on
  analogWrite(A3, DUTY_CYCLE); //enable driver 2 on
  digitalWrite(4, LOW); //right wheel reverse 
  digitalWrite(10, HIGH);
  digitalWrite(7, HIGH); //left wheel forward
  digitalWrite(8, LOW);  
  delay(time);
}

void pivot_right_forward(int time){
  analogWrite(A2, 0); //enable driver 1 off
  analogWrite(A3, DUTY_CYCLE); //enable driver 2 on
  digitalWrite(4, LOW); //right wheel reverse 
  digitalWrite(10, HIGH);
  digitalWrite(7, HIGH); //left wheel forward
  digitalWrite(8, LOW);  
  delay(time);
}

void pivot_right_backward(int time){
  analogWrite(A2, 0); //enable driver 1 off
  analogWrite(A3, DUTY_CYCLE); //enable driver 2 on
  digitalWrite(4, LOW); //right wheel reverse 
  digitalWrite(10, HIGH);
  digitalWrite(7, LOW); //left wheel backwards
  digitalWrite(8, HIGH);  
  delay(time);
}

void stop_motor(int time){
  analogWrite(A2, 0); //enable driver 1 off
  analogWrite(A3, 0); //enable driver 2 off
  delay(time);
}
