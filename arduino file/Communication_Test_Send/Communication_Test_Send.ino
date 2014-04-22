const int ARRAY_SIZE = 4;
const int SAMPLE_TIME = 2000;

const int DATA_PIN = 12;
const int RECIEVER_PIN = 21;

int sample_array[ARRAY_SIZE];

// message arrays
int colissionMsg[ARRAY_SIZE];
int foundBlueMsg[ARRAY_SIZE];
int foundRedMsg[ARRAY_SIZE];
int commRecievedMsg[ARRAY_SIZE];
int invalidMsg[ARRAY_SIZE];

int lastMessage[ARRAY_SIZE];

// flags
int messageRecievedFlag = 0;


void setup() {
  //carrier signal setup
  pinMode(5, OUTPUT);
  Serial.begin(9600);Serial1.begin(1200);
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
  pinMode(2, OUTPUT);
  attachInterrupt(2, getMessage, RISING);
  
  setArrays();
  clearArray(sample_array);
  clearArray(lastMessage);
  
  
  // enable interrupts
  interrupts();
}

void loop() {
  //delay(SAMPLE_TIME/5);
 
 delay(100);
 
 //int message[4] = {1 0 1 0};
 sendMessage(1);
 
 //delay(20);
 
 //sendMessage(2);
 
 //delay(20);
 
 //sendMessage(3);
 
  /*if( messageRecievedFlag ) {
    Serial.print("Message recieved: ");
    //messageRecievedFlag = 0;
  }
  else {//if( invalidMessageFlag ) {
    Serial.print("Invalid message: ");
  }
  
  Serial.print(sample_array[0]);
  Serial.print(sample_array[1]);
  Serial.print(sample_array[2]);
  Serial.println(sample_array[3]);*/ 
}

void getMessage() {
  //Serial.println("Hit on rising");
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
   if (digitalRead(21) == HIGH)
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
   delayMicroseconds(SAMPLE_TIME);
   //sendMessage(lastMessage);
 } 
 else {
  /*Serial.print("Invalid message recieved: ");
  Serial.print(sample_array[0]);
  Serial.print(sample_array[1]);
  Serial.print(sample_array[2]);
  Serial.println(sample_array[3]);*/
  
  // give other bot time to prepare
  delayMicroseconds(SAMPLE_TIME);
  sendMessage(5); 
  messageRecievedFlag = 0;
 }
 
 //clearArray(sample_array);
}

// set the message arrays
void setArrays() {
  // 1001
  colissionMsg[0] = 1;
  colissionMsg[1] = 0;
  colissionMsg[2] = 1;
  colissionMsg[3] = 0;
  
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
  digitalWrite(DATA_PIN, LOW); 
  Serial.println("Sending message...");
  if( message == 1 ) {
    for(int i = 0; i<ARRAY_SIZE; i++) {
      if( colissionMsg[i] == 1 ) {
        digitalWrite(DATA_PIN, HIGH);
      }
      else {
        digitalWrite(DATA_PIN, LOW); 
      }
      delayMicroseconds(SAMPLE_TIME);
    }
  }
  else if( message == 2 ) {
    for(int i = 0; i<ARRAY_SIZE; i++) {
      if( foundBlueMsg[i] == 1 ) {
        digitalWrite(DATA_PIN, HIGH);
      }
      else {
        digitalWrite(DATA_PIN, LOW); 
      }
      delayMicroseconds(SAMPLE_TIME);
    }
  }
  else if( message == 3 ) {
    for(int i = 0; i<ARRAY_SIZE; i++) {
      if( foundRedMsg[i] == 1 ) {
        digitalWrite(DATA_PIN, HIGH);
      }
      else {
        digitalWrite(DATA_PIN, LOW); 
      }
      delayMicroseconds(SAMPLE_TIME);
    }
  }
  digitalWrite(DATA_PIN, LOW); 
  /*if( message != 5) {
    // set the last message array
    //copyArrays(messageArr, lastMessage);
  }*/
}  

// overwrites arr2 with arr1
void copyArrays(int arr1[], int arr2[]) {
  for(int i = 0; i < ARRAY_SIZE; i++) {
   arr2[i] = arr1[i]; 
  }
}
