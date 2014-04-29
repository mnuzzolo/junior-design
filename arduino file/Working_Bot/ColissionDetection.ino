// colission ISR
void hasColission() {  

  int timeSince = millis() - lastInterrupt;

  if(timeSince > 300) {
    lastInterrupt = millis();
    if(digitalRead(53) == HIGH) {
      Serial.println("Front left");
      hit_left = true;
    }
    else if(digitalRead(47) == HIGH) {
      Serial.println("Front right");
      hit_right = true;
    }
    else if(digitalRead(46) == HIGH) {
      Serial.println("Front");
      hit_front = true;
    }  
    else if(digitalRead(52) == HIGH) {
      Serial.println("Left side");
      hit_back = true;
    }
    else if(digitalRead(51) == HIGH) {
      Serial.println("Left back");
      hit_back = true;
    }
    else if(digitalRead(50) == HIGH) {
      Serial.println("Back");
      hit_back = true;
    }
    else if(digitalRead(49) == HIGH) {
      Serial.println("Right back");
      hit_back = true;
    }
    else if(digitalRead(48) == HIGH) {
      Serial.println("Right side");
      hit_back = true;
    }
    else {
      Serial.println("ERR: Unknown colisison."); 
      hit_front = true;
    }

    //reverse(500);
    colissionFlag++;
    //stop_motor(0); 
  }
}

