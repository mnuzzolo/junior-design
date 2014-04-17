  int value = 0;
  int hit = 0;
  
void setup() {
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
  
  //setup collision sensor
  pinMode(A8, INPUT);
  Serial.begin(9600);
  forward(0);
  
}
void loop() {
   value = analogRead(A8);
   if (value >= 500 && hit == 0) {
    //stop_motor(1000);
    reverse(500);
    stop_motor(0); 
    hit = 1;
   }

  if(hit)
    return;
}
