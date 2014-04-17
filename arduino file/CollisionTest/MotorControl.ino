
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

void pivot_right_forward(int time){
  digitalWrite(6, LOW);//enable driver 1 on
  digitalWrite(9, HIGH);//enable driver 2 
  digitalWrite(4, LOW); //right wheel reverse 
  digitalWrite(10, HIGH);
  digitalWrite(7, HIGH); //left wheel forward
  digitalWrite(8, LOW);  
  delay(time);
}

void pivot_right_backward(int time){
  digitalWrite(6, LOW);//enable driver 1 on
  digitalWrite(9, HIGH);//enable driver 2 
  digitalWrite(4, LOW); //right wheel reverse 
  digitalWrite(10, HIGH);
  digitalWrite(7, LOW); //left wheel backwards
  digitalWrite(8, HIGH);  
  delay(time);
}

void stop_motor(int time){
    digitalWrite(6, LOW);//enable driver 1 on
    digitalWrite(9, LOW);//enable driver 2 
    delay(time);
}
