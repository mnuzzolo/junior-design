void LED_check() {

  // get sensor info
  digitalWrite(28, HIGH);
  digitalWrite(30, LOW);
  delay(LED_blink_time);
  currB_read = analogRead(A0);
  //Serial.print("BLUE: ");
  //Serial.println(currB_read);
  delay(LED_blink_time);
  digitalWrite(28, LOW);
  digitalWrite(30, HIGH);
  delay(LED_blink_time);
  currR_read = analogRead(A0);
  //Serial.print("RED: ");
  //Serial.println(currR_read);
  delay(LED_blink_time);

  // calculate change in readings
  blue_change = currB_read - lastB_read;
  red_change = currR_read - lastR_read;

  // store the current read for comparison
  lastB_read = currB_read;
  lastR_read = currR_read;

  // set color flags
  if(blue_change > 100 && blue_change > red_change)
  {
    last_color = "BLUE";
    Serial.println("***FOUND BLUE***");
    currR_read = 1023; // prevents a double "find"
    on_blue = true;
    on_red = false;
    lost_blue = false;
    lost_red = false;
  }
  // check if red is found
  else if(red_change > 100 && red_change > blue_change)
  {
    last_color = "RED";
    Serial.println("***FOUND RED***");
    currB_read = 1023; // prevents a double "find"
    on_red = true;
    on_blue = false;
    lost_red = false;
    lost_blue = false;
  }
  // check if blue is lost
  else if(on_blue && blue_change < -100)
  {
    last_color = "BLUE";
    Serial.println("***LOST BLUE***");
    on_blue = false;
    on_red = false;
    lost_blue = true;
    lost_red = false;
  }
  // check if red is lost
  else if(on_red && red_change < -100)
  {
    last_color = "RED";
    Serial.println("***LOST RED***");
    on_red = false;
    on_blue = false;
    lost_blue = false;
    lost_red = true;
  }
}

// look for blue path and try to follow!
int sweep_find_blue () {

  if(last_dir_checked == "RIGHT") { 
    last_dir_checked = "LEFT";
    if(sweep_left_blue()) {    
      return true;   
    }
    else {
      last_dir_checked = "RIGHT";
      if( sweep_right_blue() )
        return true;
      else {
        reverse(150);
      }
    }
  }
  else {
    last_dir_checked = "RIGHT";
    if(sweep_right_blue()) {
      return true;
    }
    else {
      last_dir_checked = "LEFT";
      if( sweep_left_blue() ) 
        return true;
      else {
        reverse(150);
      }
    }
  }

  stop_motor(0);
  return false;
}

int sweep_right_blue() {
  int found = false;

  Serial.println("***SWEEP RIGHT***");
  for(int j = 0; j < 6; j++)
  {
    right(100);

    stop_motor(0);

    if(colissionFlag)
      break;

    LED_check();
    if(on_blue)
    {
      Serial.println("***FOUND BLUE***");
      found = true;
      stop_motor(0);
      break; 
    }  
  }

  if(found)
  {
    right(75);
    return true;
  }
  else {
    left(100*3);
    return false;
  }
}

int sweep_left_blue() {  
  int found = false;

  Serial.println("***SWEEP LEFT***");
  for(int i = 0; i < 6; i++)
  {
    left(100);

    if(colissionFlag)
      break;

    stop_motor(0);
    LED_check();

    if(on_blue)
    {
      Serial.println("***FOUND BLUE***");
      found = true;
      stop_motor(0);
      break; 
    }  
  }

  if(found)
  {
    left(75);
    return true;
  }

  right(100*3);
}

// sweep find for red path
int sweep_find_red () {

  if(last_dir_checked == "RIGHT") { 

    last_dir_checked = "LEFT";
    if(sweep_left_red()) {    
      return true;   
    }
    else {
      last_dir_checked = "RIGHT";
      if( sweep_right_red() )
        return true;
      else {
        reverse(200);
      }
    }
  }
  else {
    last_dir_checked = "RIGHT";
    if(sweep_right_red()) {
      return true;
    }
    else {
      last_dir_checked = "LEFT";
      if( sweep_left_red() ) 
        return true;
      else {
        reverse(200);
      }
    }
  }

  stop_motor(0);
  return false;
}

int sweep_right_red() {
  int found = false;

  Serial.println("***SWEEP RIGHT***");
  for(int j = 0; j < 6; j++)
  {
    right(100);
    stop_motor(0);
    LED_check();
    if(on_red)
    {
      Serial.println("***FOUND RED***");
      found = true;
      stop_motor(0);
      break; 
    }  
  }

  if(found)
  {
    right(75);
    return true;
  }
  else {
    left(100*3);
    return false;
  }
}

int sweep_left_red() {  
  int found = false;

  Serial.println("***SWEEP LEFT***");
  for(int i = 0; i < 6; i++)
  {
    left(100);
    stop_motor(0);
    LED_check();

    if(on_red)
    {
      Serial.println("***FOUND RED***");
      found = true;
      stop_motor(0);
      break; 
    }  
  }

  if(found)
  {
    left(75);
    return true;
  }

  right(100*3);
}

void start_motor() {
  // turn on motor
  digitalWrite(6, HIGH); //enable driver 1 on
  digitalWrite(9, HIGH); //enable driver 2 on
  digitalWrite(4, HIGH); 
  digitalWrite(5, LOW);
  digitalWrite(7, HIGH); 
  digitalWrite(8, LOW);  
}

void turn_off() {
  digitalWrite(6, LOW);//disable driver 1 
  digitalWrite(9, LOW);//disable driver 2
}



