const int ARRAY_SIZE = 4;
const int SAMPLE_TIME = 950;

const int DATA_PIN = 12;
const int RECIEVER_PIN = 18;

int sample_array[ARRAY_SIZE];

// message arrays
int colissionMsg[ARRAY_SIZE];
int foundBlueMsg[ARRAY_SIZE];
int foundRedMsg[ARRAY_SIZE];
int commRecievedMsg[ARRAY_SIZE];
int invalidMsg[ARRAY_SIZE];

int lastMessage[ARRAY_SIZE];

int lastInterrupt = 0;

// flags
int messageRecievedFlag = 0;

int counter = 0;
int counter2 = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(DATA_PIN, OUTPUT); // data pin
  pinMode(RECIEVER_PIN, INPUT);
  pinMode(2, OUTPUT);
  attachInterrupt(5, getMessage, RISING);
  
  setArrays();
  clearArray(sample_array);
  clearArray(lastMessage);
  
  // enable interrupts
  interrupts();
}

void loop() {
  //delay(SAMPLE_TIME/5);
 
 //delay(3000);
 
 //int message[4] = {1 0 1 0};
 //sendMessage(1);
  
  if( messageRecievedFlag ) {
    Serial.print("Message recieved: ");
    messageRecievedFlag = 0; 
    Serial.print(sample_array[0]);
    Serial.print(sample_array[1]);
    Serial.print(sample_array[2]);
    Serial.println(sample_array[3]); 
  }
  /*else if( counter > 32760  ) {
    if(counter2 > 5) {
      Serial.print("Invalid message: ");
      Serial.print(sample_array[0]);
      Serial.print(sample_array[1]);
      Serial.print(sample_array[2]);
      Serial.println(sample_array[3]); 
    }
    counter2++;
    counter = -32760;
  }*/
  
  counter++; 
  
}

void getMessage() {
  //Serial.println("Hit on rising");
  
  if( millis() - lastInterrupt > 50) {
    lastInterrupt = millis();
  digitalWrite(2, HIGH);
  detachInterrupt(2);
  noInterrupts();
  //Serial.println("Incoming message detected...");

  // stop bot
  //stop_motor();
  
  // recieve message
  for(int i = 0; i < ARRAY_SIZE; i++) {
   delayMicroseconds(SAMPLE_TIME/2);
   // this should read in the middle of a bit high/low 
   if (digitalRead(RECIEVER_PIN) == HIGH)
     sample_array[i] = 1;
   else { 
     sample_array[i] = 0;
   }
   delayMicroseconds(SAMPLE_TIME/2);
  }
  
  
  //delayMicroseconds(SAMPLE_TIME*1000);
  // find out what message was transmitted
  decodeMessage();
  
  //Serial.println("Leaving ISR...");
  interrupts();
  attachInterrupt(2, getMessage, RISING);
  digitalWrite(2, LOW);
  }
}

void clearArray(int array []) {
 for(int i = 0; i < ARRAY_SIZE; i++) {
   array[i] = 0;
 }
}

int compareArrays(int arr1[], int arr2[]) {
 for(int i = 0; i < ARRAY_SIZE; i++) {
  if(arr1[i] != arr2[i]) {
   return false; 
  }
 }
 return true; 
}

void decodeMessage() {
 messageRecievedFlag = 1;
 //Serial.println("Decoding message...");
 if( compareArrays(sample_array, colissionMsg) ) {
   //Serial.println("Wall hit!");
   // set wall hit flag
 }
 else if( compareArrays(sample_array, foundBlueMsg) ) {
   //Serial.println("Found blue!");
   // set blue found flag
 } 
 else if( compareArrays(sample_array, foundRedMsg) ) {
   //Serial.println("Found red!");
   // set red found flag
 } 
 else if( compareArrays(sample_array, commRecievedMsg) ) {
   //Serial.println("Communication successful");
   // exit routine
 } 
 else if( compareArrays(sample_array, invalidMsg) ) {
   // Serial.println("Communication failed. Resending message...");
   // give other bot time to prepare
   //delayMicroseconds(SAMPLE_TIME);
   //sendMessage(lastMessage);
 } 
 else {
  /*Serial.print("Invalid message recieved: ");
  Serial.print(sample_array[0]);
  Serial.print(sample_array[1]);
  Serial.print(sample_array[2]);
  Serial.println(sample_array[3]);*/
  
  // give other bot time to prepare
  //delayMicroseconds(SAMPLE_TIME);
  //sendMessage(5); 
  //messageRecievedFlag = 0;
 }
 
 //clearArray(sample_array);
}

// set the message arrays
void setArrays() {
  // 1001
  colissionMsg[0] = 1;
  colissionMsg[1] = 0;
  colissionMsg[2] = 0;
  colissionMsg[3] = 1;
  
  // 1010
  foundBlueMsg[0] = 1;
  foundBlueMsg[1] = 0;
  foundBlueMsg[2] = 1;
  foundBlueMsg[3] = 0;
  
  // 1011
  foundRedMsg[0] = 1;
  foundRedMsg[1] = 0;
  foundRedMsg[2] = 1;
  foundRedMsg[3] = 1;
  
  // 1100
  commRecievedMsg[0] = 1;
  commRecievedMsg[1] = 1;
  commRecievedMsg[2] = 0;
  commRecievedMsg[3] = 0;
  
  // 1101
  invalidMsg[0] = 1;
  invalidMsg[1] = 1;
  invalidMsg[2] = 0;
  invalidMsg[3] = 1;
  
}

void sendMessage(int message) {
  //Serial.println("Sending message...");
  if( message == 1 ) {
    for(int i = 0; i<ARRAY_SIZE; i++) {
      if( colissionMsg[i] == 1 ) {
        analogWrite(DATA_PIN, HIGH);
      }
      else {
        analogWrite(DATA_PIN, LOW); 
      }
      delayMicroseconds(SAMPLE_TIME);
    }
  }
  
  //if( message != 5) {
    // set the last message array
    //copyArrays(messageArr, lastMessage);
  //}
}  

// overwrites arr2 with arr1
void copyArrays(int arr1[], int arr2[]) {
  for(int i = 0; i < ARRAY_SIZE; i++) {
   arr2[i] = arr1[i]; 
  }
}
