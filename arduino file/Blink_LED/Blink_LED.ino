int switch1 = HIGH;
int switch2 = HIGH;
int blue_on10 = false;
int blue_on1 = false;
int red_on = false;
int sensorPin = A0;
int sensorValue = 0;

void setup() {
// initialize the digital pin as an output.
// Pin 13 has an LED connected on most Arduino boards:
pinMode(13, OUTPUT);
pinMode(11, OUTPUT);
pinMode(1, OUTPUT); //control for MOSFET and motor
pinMode(2, INPUT); //switch 1
pinMode(3, INPUT); //switch 2
pinMode(4, OUTPUT); //hBridge pin 2
pinMode(5, OUTPUT);//hbridge pin 7
pinMode(6, OUTPUT); // h bridge enable 1
checkSwitch();
attachInterrupt(0, checkSwitch, CHANGE);
attachInterrupt(1, checkSwitch, CHANGE);

}
void loop() {
  digitalWrite(6, HIGH);
  digitalWrite(4, HIGH); 
  digitalWrite(5, LOW); 
  delay(5000);
  digitalWrite(4, LOW); 
  digitalWrite(5, HIGH); 
  sensorValue = (analogRead(A0)/4); //reads potentiometer value
  
  if ( blue_on10 && !red_on ){
    analogWrite(13, sensorValue);
    delay(100);
    analogWrite(13, LOW);
    delay(100);
    analogWrite(11, LOW);
  }
  else if ( blue_on10 && red_on )
  {
      analogWrite(11, sensorValue);
      analogWrite(13, sensorValue);
      delay(100);
      analogWrite(13, LOW);
      delay(100);
 
  }
  else {
    analogWrite(13, sensorValue);
    delay(1000);
    analogWrite(13, LOW);
    delay(1000);
    analogWrite(11, LOW);

  }
  
}

void checkSwitch() {
  
  int new_switch1 = digitalRead(2);
  int new_switch2 = digitalRead(3);

  // if both switches are off
  if ( new_switch1 == HIGH && new_switch2 == HIGH) {
     blue_on1 = true;
     blue_on10 = false;
     red_on = false; 
  }
  
  // switch 1 moves from open to closed
  if ( switch1 == HIGH && new_switch1 == LOW ) {
     blue_on10 = true;
  }
  // if switch 2 moves from closed to open  
  if ( switch2 == LOW && new_switch2 == HIGH && blue_on10) {
     red_on = true; 
  }
  
  switch1 = new_switch1;
  switch2 = new_switch2;
}
