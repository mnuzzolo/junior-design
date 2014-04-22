int value = 0;
int hit = 0;
int lastInterrupt = 0;

// Globals for motor
int DUTY_CYCLE = 255;

// Globals from colission detection
int colissionFlag = 0;
int hit_front = 0;
int hit_left = 0;
int hit_right = 0;
int hit_back = 0;

// GLOBALS from color recognition
int findColorFlag = 0;
int LED_blink_time = 20;
String last_dir_checked = "RIGHT";

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

String last_color = "BLUE";

void setup() {
  Serial.begin(9600);
  // setup LEDs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  // setup motor
  pinMode(4, OUTPUT); //hBridge pin 2
  pinMode(10, OUTPUT);//hbridge pin 7
  pinMode(A2, OUTPUT); // h bridge enable 1 (pin1)
  pinMode(7, OUTPUT); //hBridge pin 15
  pinMode(8, OUTPUT); //hbridge pin 10
  pinMode(A3, OUTPUT); // h bridge enable 2 (pin 9)

  pinMode(21, INPUT);
  attachInterrupt(2, hasColission, RISING);

  // setup colission pins
  pinMode(46, INPUT);
  pinMode(47, INPUT);
  pinMode(48, INPUT);
  pinMode(49, INPUT);
  pinMode(50, INPUT);
  pinMode(51, INPUT);
  pinMode(52, INPUT);
  pinMode(53, INPUT);

  //setup collision sensor (debugging)
  pinMode(A8, INPUT);

  // setup sensor
  pinMode(A0, INPUT);
  pinMode(28, OUTPUT); // blue LED out
  pinMode(30, OUTPUT); // red LED out

  delay(2000);
  // get first values for red/blue
  LED_check();
  forward(0);
  Serial.println("go!");
}

// main loop
void loop() {

  if(colissionFlag && !findColorFlag) {
    if(hit_front) {
      Serial.println("hit front");
      stop_motor(50);
      reverse(450);
      if(last_color == "RED")
        left(1100);
      else {
        right(1100);
      }
      forward(0);
      findColorFlag = true;
      colissionFlag = false;
      hit_front = false;
    }
    else if(hit_left) {
      Serial.print("hit left");
      stop_motor(50);
      reverse(450);
      right(900);
      forward(0);
      findColorFlag = true;
      colissionFlag = false;
      hit_left = false;
      last_dir_checked = "RIGHT";
    }    
    else if(hit_right) {
      Serial.println("hit right");
      stop_motor(50);
      reverse(450);
      left(900);
      forward(0);
      findColorFlag = true;
      colissionFlag = false;
      hit_right = false;
      last_dir_checked = "LEFT";
    }
    else if (hit_back) {
      //forward(150);
      colissionFlag = false;
      hit_back = false;
      //stop_motor(0);
    }
  }
  else if(colissionFlag) {
      Serial.println("doing a 180");
      stop_motor(50);
      reverse(450);
      if(last_color == "RED")
        left(1100);
      else {
        right(1100);
      }
      forward(0);
      colissionFlag = false;
  }

  LED_check();

  if(findColorFlag) {

    LED_check();

    if(on_blue)
    {
      last_color = "BLUE";
      while(on_blue) 
      {
        LED_check();

        if(colissionFlag)
          break;

        forward(0); 
      }
      if(lost_blue)
      {
        LED_check();
        delay(50);
        reverse(50);
        stop_motor(0);

        delay(250);

        if(sweep_find_blue() == true)
        {
          Serial.println("***SUCCESSFUL SWEEP***");
          lost_blue = false;
          start_motor();
        }
        else {
          stop_motor(0);
          findColorFlag = false;
        }          
      }
    }

    if(on_red)
    {
      last_color = "RED";
      
      Serial.println("found red");
      stop_motor(0);
      //forward(0);
    }
  }
}


