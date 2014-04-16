
int input = 0;

int lastR_read = 1023;
int currR_read = 0;
int lastB_read = 1023;
int currB_read = 0;

int blue_change = 0;
int red_change = 0; 

int on_blue = false;
int on_red = false;

void setup() {
  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);  
}
void loop(){
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  delay(250);
  currB_read = analogRead(A0);
  Serial.print("BLUE: ");
  Serial.println(currB_read);
  delay(250);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  delay(250);
  currR_read = analogRead(A0);
  Serial.print("RED: ");
  Serial.println(currR_read);
  delay(250);
  
  // calculate change in readings
  int blue_change = currB_read - lastB_read;
  int red_change = currR_read - lastR_read;
  
  // check if blue is found
  if(blue_change > 150 && blue_change > red_change)
  {
    Serial.println("***FOUND BLUE***");
    currR_read = 1023; // prevents a double "find"
    on_blue = true;
    on_red = false;
  }
  // check if red is found
  else if(red_change > 150 && red_change > blue_change)
  {
    Serial.println("***FOUND RED***");
    currB_read = 1023; // prevents a double "find"
    on_red = true;
    on_blue = false;
  }
  // check if blue is lost
  else if(on_blue && blue_change < -150)
  {
    Serial.println("***LOST BLUE***");
    on_blue = false;
  }
  // check if red is lost
  else if(on_red && red_change < -150)
  {
   Serial.println("***LOST RED***"); 
   on_red = false;
  }
  
  // store the current read for comparison
  lastB_read = currB_read;
  lastR_read = currR_read;
}
