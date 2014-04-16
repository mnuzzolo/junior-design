  int value = 0;

void setup() {

pinMode(A1, INPUT);
  Serial.begin(9600);
}
void loop() {
   value = analogRead(A1); 
   Serial.print("Value ");
   Serial.println(value);
   delay(1000);
   
}
  
