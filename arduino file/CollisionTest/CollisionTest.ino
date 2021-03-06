int value = 0;
int hit = 0;
int lastInterrupt = 0;

int colissionFlag = 0;

void setup() {
  Serial.begin(9600);
  // setup LEDs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  // setup motor
  pinMode(4, OUTPUT); //hBridge pin 2
  pinMode(10, OUTPUT);//hbridge pin 7
  pinMode(6, OUTPUT); // h bridge enable 1 (pin1)
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
  //setup collision sensor
  pinMode(A8, INPUT);

  forward(0);
}

void loop() {
  //delay(100);
  //Serial.println(analogRead(A8));
  if(colissionFlag) {
    Serial.println(colissionFlag);
    reverse(300);
    left(800);
    stop_motor(0);
    colissionFlag = 0;
  }
}

void hasColission() {  
  //Serial.println("in interrupt..."); 
  
  int timeSince = millis() - lastInterrupt;

  if(timeSince > 300) {
    lastInterrupt = millis();
    if(digitalRead(46) == HIGH) {
      Serial.println("Front");
    }
    else if(digitalRead(47) == HIGH) {
      Serial.println("Front left");
    }
    else if(digitalRead(48) == HIGH) {
      Serial.println("Left side");
    }
    else if(digitalRead(49) == HIGH) {
      Serial.println("Left back");
    }
    else if(digitalRead(50) == HIGH) {
      Serial.println("Back");
    }
    else if(digitalRead(51) == HIGH) {
      Serial.println("Right back");
    }
    else if(digitalRead(52) == HIGH) {
      Serial.println("Right side");
    }
    else if(digitalRead(53) == HIGH) {
      Serial.println("Front right");
    }
    else {
      Serial.println("What happened..."); 
    }
    
  //reverse(500);
    colissionFlag++;
    //stop_motor(0); 
  }
}



