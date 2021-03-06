// Globals for communication
const int SAMPLE_TIME = 4000;

const int DATA_PIN = 12;
const int RECIEVER_PIN = 19;

int COMM_TURN_AMT = 75;
int OVER_TURN_AMT = 90;

int leader = true;

// message signals
int commRecievedMsg = 10;
int foundBlueMsg = 20;
int invalidMsg = 30;
int foundRedMsg = 40;
int finishedTrack = 60;

// store last message
int last_message = 0;

// store interrupt information (communication)
int lastMsgInterrupt = 0;
int num_interrupts = 0;

// flags
int messageRecievedFlag = 0;
int findColorFlag = 0;
int finishedTrackFlag = 0;
int achievedCommFlag = 0;

// Globals for motor
int DUTY_CYCLE = 70;

// Globals from colission detection
int lastInterrupt = 0;

int colissionFlag = 0;
int hit_front = 0;
int hit_left = 0;
int hit_right = 0;
int hit_back = 0;

// GLOBALS from color recognition
int LED_blink_time = 20;
String last_dir_checked = "RIGHT";
String color_to_find = "NONE";

int NUM_SWEEPS = 5;
int SWEEP_SIZE = 110;

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
  // setup communication
  pinMode(5, OUTPUT);
  Serial.begin(9575); // computer communication
  Serial1.begin(1200); // carrier signal
  TCCR3A = _BV(COM3A0) | _BV(COM3B0) | _BV(WGM30) | _BV(WGM31);
  // sets COM Output Mode to FastPWM with toggle of OC3A on compare match with OCR3A
  // also sets WGM to mode 15: FastPWM with top set by OCR3A
  TCCR3B = _BV(WGM32) | _BV(WGM33) | _BV(CS31);
  // sets WGM as stated above; sets clock scaling to "divide by 8"
  OCR3A = 39; //approx 25kHz signal
  // above sets the counter value at which register resets to 0x0000;
  // generate 20kHz when OCR3A=50, 20.5kHz OCR3A = 48, 21kHz OCR3A = 46
  // Serial.println(TCCR3A, BIN);Serial.println(TCCR3B, BIN);

  pinMode(DATA_PIN, OUTPUT); // data pin
  pinMode(RECIEVER_PIN, INPUT);
  attachInterrupt(4, getMessage, RISING);

  // enable interrupts
  interrupts();

  Serial.begin(9575);
  // setup LEDs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  // setup motor
  pinMode(4, OUTPUT); //hBridge pin 2
  pinMode(10, OUTPUT);//hbridge pin 7
  pinMode(6, OUTPUT); // h bridge enable 1 (pin 1)
  pinMode(7, OUTPUT); //hBridge pin 15
  pinMode(8, OUTPUT); //hbridge pin 10
  pinMode(9, OUTPUT); // h bridge enable 2 (pin 9)

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

  // pins to 5V 
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  digitalWrite(38, HIGH);
  digitalWrite(39, HIGH);

  // setup sensor
  pinMode(A0, INPUT);
  pinMode(28, OUTPUT); // blue LED out
  pinMode(30, OUTPUT); // red LED out

  // setup signal LEDs
  pinMode(32, OUTPUT); // blue
  pinMode(34, OUTPUT); // red

  digitalWrite(32, HIGH); 
  delay(500);
  digitalWrite(34, HIGH);
  delay(500);
  digitalWrite(32, LOW); 
  delay(500);
  digitalWrite(34, LOW);
  // get first values for red/blue
  LED_check();

  if(leader)
    forward(0);

}

// main loop
void loop() {

  if( messageRecievedFlag ) {
    stop_motor(0);

    digitalWrite(32, HIGH);
    digitalWrite(34, HIGH);
    Serial.print("Message recieved: ");
    Serial.println(messageRecievedFlag);

    if( (messageRecievedFlag >= (foundRedMsg - 5) && messageRecievedFlag <= (foundRedMsg + 5) ) ) {
      color_to_find = "BLUE";
      findColorFlag = true;
      achievedCommFlag = true;
      
      for(int i = 0; i < 5; i++) {
        sendMessage(commRecievedMsg);
        delay(575);
      }
      delay(1000);
      // go left
      right(250);
      forward(0);
    }
    else if( (messageRecievedFlag >= (foundBlueMsg - 5) && messageRecievedFlag <= (foundBlueMsg + 5) ) ) {
      color_to_find = "RED";
      findColorFlag = true;
      achievedCommFlag = true;
      
      for(int i = 0; i < 5; i++) {
        sendMessage(commRecievedMsg);
        delay(575);
      }
      delay(1000);
      // go right
      left(250);
      forward(0);
    }
    else if( (messageRecievedFlag >= (finishedTrack - 5) && messageRecievedFlag <= (finishedTrack + 5) ) ) {
      for(int i = 0; i < 5; i++) {
        sendMessage(commRecievedMsg);
        delay(575);
      }
      for(int i = 0; i < 20; i++) {
        digitalWrite(32, HIGH);
        digitalWrite(34, HIGH);
        delay(500);
        digitalWrite(32, LOW);
        digitalWrite(34, LOW);
      }
      while(1) {
              // stop here
      }
    }

    messageRecievedFlag = 0; 

    delay(1000);
    digitalWrite(32, LOW);
    digitalWrite(34, LOW);
  }

  // FIRST COLISSION 
  if(colissionFlag && !findColorFlag && !finishedTrackFlag) {
    if(hit_front) {
      Serial.println("hit front");
      //stop_motor(50);
      reverse(575);
      if(last_color == "RED")
        left(750);
      else {
        right(750);
      }
      forward(0);
      findColorFlag = true;
      colissionFlag = false;
      hit_front = false;
    }
    else if(hit_left) {
      Serial.print("hit left");
      //stop_motor(50);
      reverse(575);
      right(700);
      forward(0);
      findColorFlag = true;
      colissionFlag = false;
      hit_left = false;
      last_dir_checked = "RIGHT";
    }    
    else if(hit_right) {
      Serial.println("hit right");
      //stop_motor(50);
      reverse(575);
      left(700);
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
  // SECOND AND OTHER COLISSIONS
  else if(colissionFlag && !finishedTrackFlag) {
    if(hit_front) {
      Serial.println("doing a 180");
      //stop_motor(50);
      reverse(575);
      if(last_color == "RED")
        right(1000);
      else {
        left(1000);
      }
      forward(0);
      findColorFlag = true;
      colissionFlag = false;
    }
    else if(hit_left) {
      Serial.print("hit left");
      //stop_motor(50);
      reverse(575);
      right(750);
      forward(0);
      findColorFlag = true;
      colissionFlag = false;
      hit_left = false;
      last_dir_checked = "RIGHT";
    }    
    else if(hit_right) {
      Serial.println("hit right");
      //stop_motor(50);
      reverse(575);
      left(750);
      forward(0);
      findColorFlag = true;
      colissionFlag = false;
      hit_right = false;
      last_dir_checked = "LEFT";
    }
    else if (hit_back) {
      forward(0);
      colissionFlag = false;
      hit_back = false;
      //stop_motor(0);
    }
  }

  LED_check();

  if(findColorFlag) {

    LED_check();

    if(on_blue && color_to_find != "RED") {
      color_to_find = "BLUE";

      if( !achievedCommFlag) {
        stop_motor(0);
        //messageProtocol(foundBlueMsg);
        achievedCommFlag = true;
      }

      forward(0);

      digitalWrite(32, HIGH);
      digitalWrite(34, LOW);
      last_color = "BLUE";

      while(on_blue) {
        LED_check();

        if(colissionFlag)
          break;

        forward(0); 
      }
      if(lost_blue) {
        LED_check();
        delay(50);
        reverse(50);
        stop_motor(0);

        delay(250);

        if(sweep_find_blue() == true) {
          Serial.println("***SUCCESSFUL SWEEP***");
          lost_blue = false;
          forward(0);
        }
        else {
          reverse(200);
          stop_motor(0);
          findColorFlag = false;
          finishedTrackFlag = true;
          if(!leader) {
            //messageProtocol(finishedTrack);
            finishedDisplay();
            while(1) {
              // stop here
            }
          }
        }          
      }
    }

    if(on_red && color_to_find != "BLUE") {
      Serial.println("Found red");
      color_to_find = "RED";

      if( !achievedCommFlag ) {
        stop_motor(0);
        //messageProtocol(foundRedMsg);    
        achievedCommFlag = true;
      }

      forward(0); 

      digitalWrite(34, HIGH);
      digitalWrite(32, LOW);
      last_color = "RED";

      // found blue
      while(on_red) {
        LED_check();

        if(colissionFlag)
          break;

        forward(0); 
      }
      if(lost_red) {
        LED_check();
        delay(50);
        reverse(50);
        stop_motor(0);

        delay(250);

        if(sweep_find_red() == true) {
          Serial.println("***SUCCESSFUL SWEEP***");
          lost_blue = false;
          forward(0);
        }
        else {
          reverse(200);
          stop_motor(0);
          findColorFlag = false;
          finishedTrackFlag = true;
          if(!leader) {
            //messageProtocol(finishedTrack);
            finishedDisplay();
            while(1) {
              // stop here
            }
          }
        }          
      } 
    }
  }
}

void finishedDisplay () {
  for(int i = 0; i < 5; i++) {
    for(int i = 0; i < 20; i++) {
      delayMicroseconds(SAMPLE_TIME*2);
    }
    for(int i = 0; i < 10; i++) {
      delayMicroseconds(5500);
    }
    delay(575);
  }
  for(int i = 0; i < 20; i++) {
    digitalWrite(32, HIGH);
    digitalWrite(34, HIGH);
    delay(500);
    digitalWrite(32, LOW);
    digitalWrite(34, LOW);
  }
  stop_motor(0);
}




