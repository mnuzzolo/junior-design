void LED_check() {

  // get sensor info
  // check blue
  digitalWrite(28, HIGH);
  //if( !(on_lue || lost_blue) )
  digitalWrite(30, LOW);
  delay(LED_blink_time);
  currB_read = analogRead(A0);
  //Serial.print("BLUE: ");
  //Serial.println(currB_read);
  delay(LED_blink_time);
  // check red
  //if( !(onRed || lost_red) )
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
  if(blue_change > 100 && blue_change > red_change && color_to_find != "RED")
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
  else if(red_change > 70 && red_change > (blue_change - 25))
  {
    last_color = "RED";
    Serial.println("***FOUND RED***");
    currB_read = 1023; // prevents a double "find"
    on_red = true;
    on_blue = false;
    lost_red = false;
    lost_blue = false;
  }
  // check if red is lost
  else if(on_red && red_change < -50)
  {
    last_color = "RED";
    Serial.println("***LOST RED***");
    on_red = false;
    on_blue = false;
    lost_blue = false;
    lost_red = true;
  }
  // check if blue is lost
  else if(on_blue && blue_change < -100 && color_to_find != "RED")
  {
    last_color = "BLUE";
    Serial.println("***LOST BLUE***");
    on_blue = false;
    on_red = false;
    lost_blue = true;
    lost_red = false;
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
  for(int j = 0; j < NUM_SWEEPS; j++)
  {
    right(SWEEP_SIZE);

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
    right(OVER_TURN_AMT);
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
  for(int i = 0; i < NUM_SWEEPS; i++)
  {
    left(SWEEP_SIZE);

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
    left(OVER_TURN_AMT);
    return true;
  }
  else {
    right(100*3);
    return false;
  }
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
  for(int j = 0; j < NUM_SWEEPS; j++)
  {
    right(SWEEP_SIZE);
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
    right(OVER_TURN_AMT);
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
  for(int i = 0; i < NUM_SWEEPS; i++)
  {
    left(SWEEP_SIZE);
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
    left(OVER_TURN_AMT);
    return true;
  }
  else {  
    right(100*3);
    return false;
  }
}


