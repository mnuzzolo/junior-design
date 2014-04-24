const int SAMPLE_TIME = 4000;

const int DATA_PIN = 12;
const int RECIEVER_PIN = 18;

// message signals
int commRecievedMsg = 2;
int foundBlueMsg = 6;
int foundRedMsg = 10;
int invalidMsg = 14;

// store last message
int last_message = 0;

// store interrupt information (communication)
int lastInterrupt = 0;
int num_interrupts = 0;

// flags
int messageRecievedFlag = 0;
int communicationFlag = 0;

void setup() {
  pinMode(5, OUTPUT);
  Serial.begin(9600);Serial1.begin(1200);
  TCCR3A = _BV(COM3A0) | _BV(COM3B0) | _BV(WGM30) | _BV(WGM31);
  // sets COM Output Mode to FastPWM with toggle of OC3A on compare match with OCR3A
  // also sets WGM to mode 15: FastPWM with top set by OCR3A
  TCCR3B = _BV(WGM32) | _BV(WGM33) | _BV(CS31);
  // sets WGM as stated above; sets clock scaling to "divide by 8"
  OCR3A = 39; //approx 20.5kHz signal
  // above sets the counter value at which register resets to 0x0000;
  // generate 20kHz when OCR3A=50, 20.5kHz OCR3A = 48, 21kHz OCR3A = 46
  // Serial.println(TCCR3A, BIN);Serial.println(TCCR3B, BIN);
  //Serial.begin(9600);

  pinMode(DATA_PIN, OUTPUT); // data pin
  pinMode(RECIEVER_PIN, INPUT);
  pinMode(2, OUTPUT);
  //attachInterrupt(5, getMessage, RISING);

  // enable interrupts
  interrupts();
}

void loop() {
  //sendMessage(commRecievedMsg);
  //delay(1000);
  sendMessage(foundBlueMsg);
  delay(1000);
  sendMessage(foundRedMsg);
  delay(1000);
  sendMessage(invalidMsg);
  delay(1000);
}

void getMessage() {
  // new message indicator
  if( millis() - lastInterrupt >= 500 ) {  
    num_interrupts = 1;
  }
  // deal with "end of message" indicator 
  else if( millis() - lastInterrupt >= 150 ) {
    messageRecievedFlag = num_interrupts;
    num_interrupts = 1;
  }
  // increment counter
  else {
    num_interrupts++;
  }
  lastInterrupt = millis();
}

void decodeMessage() {
  //Serial.println("Decoding message...");
  if( messageRecievedFlag == commRecievedMsg ) {
    // message recieved
  }
  else if( messageRecievedFlag == foundBlueMsg ) {
    //Serial.println("Found blue!");
    // set blue found flag
  } 
  else if( messageRecievedFlag == foundRedMsg ) {
    //Serial.println("Found red!");
    // set red found flag
  } 
  else if( messageRecievedFlag == invalidMsg ) {
    //Serial.println("Found red!");
    // set red found flag
    sendMessage(last_message);
  } 
  else {
    sendMessage(invalidMsg);
  }

  messageRecievedFlag = 0;
}

void sendMessage(int message) {
  noInterrupts();
  digitalWrite(DATA_PIN, LOW);
  Serial.print("Sending message... ");
  Serial.println(message);
  for(int i = 0; i < message; i++) {
      // "1"
      digitalWrite(DATA_PIN, HIGH);
      delayMicroseconds(SAMPLE_TIME);
      // "0"
      digitalWrite(DATA_PIN, LOW);
      delayMicroseconds(SAMPLE_TIME);
  }
  
  for(int i = 0; i < 10; i++) {
    delayMicroseconds(6000);
  }
  
  // "1"
  digitalWrite(DATA_PIN, HIGH);
  delayMicroseconds(SAMPLE_TIME);
  // "0"
  digitalWrite(DATA_PIN, LOW);
  
  // set last messsge
  last_message = message;
  interrupts();
}  
