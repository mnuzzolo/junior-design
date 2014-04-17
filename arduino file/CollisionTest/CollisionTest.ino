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

  pinMode(20, INPUT);
  attachInterrupt(3, hasColission, RISING);

  pinMode(50, INPUT);
  pinMode(52, INPUT);
  pinMode(53, INPUT);
  //setup collision sensor
  pinMode(A8, INPUT);

  forward(0);
}

void loop() {
  /*value = analogRead(A8);
   if (value >= 500 && hit == 0) {
   //stop_motor(1000);
   reverse(500);
   stop_motor(0); 
   hit = 1;
   }
   
   if(hit)
   return;*/
  //delay(2000);
  //Serial.println(analogRead(8));
  //digitalWrite(2,LOW);
  //digitalWrite(3,LOW);
  //Serial.print("i am on");
  if(colissionFlag) {
    Serial.println(colissionFlag);
    reverse(750);
    forward(0);
    colissionFlag = 0;
    //colissionFlag = 0;
    //digitalWrite(2, HIGH);
    //digitalWrite(3, HIGH);
  }
}

void hasColission() {  
  int timeSince = millis() - lastInterrupt;

  if(timeSince > 200) {
    lastInterrupt = millis();
    if(digitalRead(50) == HIGH) {
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      reverse(500);
    }
    else if(digitalRead(52) == HIGH) {
      digitalWrite(2, HIGH);
    }
    else if(digitalRead(53) == HIGH) {
      digitalWrite(3, HIGH);
    }

    colissionFlag++;
    stop_motor(0); 
  }
}



