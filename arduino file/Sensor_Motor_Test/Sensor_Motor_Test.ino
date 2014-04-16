
int input = 0;

int lastR_read = 1023;
int currR_read = 0;
int lastB_read = 1023;
int currB_read = 0;

int blue_change = 0;
int red_change = 0; 

int on_blue = false;
int on_red = false;

int lost_blue = false;
int lost_red = false;

void setup() {
  // setup motor
  pinMode(4, OUTPUT); //hBridge pin 2
  pinMode(10, OUTPUT);//hbridge pin 7
  pinMode(6, OUTPUT); // h bridge enable 1 (pin1)
  pinMode(7, OUTPUT); //hBridge pin 15
  pinMode(8, OUTPUT); //hbridge pin 10
  pinMode(9, OUTPUT); // h bridge enable 2 (pin 9)
  
  // setup sensor
  pinMode(A0, INPUT);
  pinMode(2, OUTPUT); // blue LED out
  pinMode(3, OUTPUT); // red LED out
  Serial.begin(9600);

  LED_check();
  start_motor();
}

// main loop
void loop(){
  
  LED_check();
  
  if(on_blue)
  {
     while(on_blue) 
     {
        LED_check();
        forward(0); 
     }
     if(lost_blue)
     {
        LED_check();
        reverse(350);
        stop_motor(0);
        
        delay(500);
        
        if(sweep_find() == true)
        {
          Serial.println("***SUCCESSFUL SWEEP***");
          lost_blue = false;
          start_motor();
        }
        else {
          stop_motor(0);
        }
        
     }
  }
  
  if(on_red)
  {
     right(1000); 
     stop_motor(0);
  }
  
}

void LED_check() {
  
  // get sensor info
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  delay(75);
  currB_read = analogRead(A0);
  Serial.print("BLUE: ");
  Serial.println(currB_read);
  delay(75);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  delay(75);
  currR_read = analogRead(A0);
  Serial.print("RED: ");
  Serial.println(currR_read);
  delay(75);
  
  // calculate change in readings
  blue_change = currB_read - lastB_read;
  red_change = currR_read - lastR_read;
  
  // store the current read for comparison
  lastB_read = currB_read;
  lastR_read = currR_read;

  // set color flags
  if(blue_change > 100 && blue_change > red_change)
  {
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
    Serial.println("***LOST BLUE***");
    on_blue = false;
    on_red = false;
    lost_blue = true;
    lost_red = false;
  }
  // check if red is lost
  else if(on_red && red_change < -100)
  {
   Serial.println("***LOST RED***");
   on_red = false;
   on_blue = false;
   lost_blue = false;
   lost_red = true;
  }
}

// look for blue path and try to follow!
int sweep_find () {
  int found = false;
  
  // sweep left
  Serial.println("***SWEEP LEFT***");
  for(int i = 0; i < 15; i++)
  {
    left(100);
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
    return true;
  }
  
  right(100*15);
  
  // sweep right
  Serial.println("***SWEEP RIGHT***");
  for(int j = 0; j < 15; j++)
  {
    right(100);
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
    return true;
  }
 
  return false;
 
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


