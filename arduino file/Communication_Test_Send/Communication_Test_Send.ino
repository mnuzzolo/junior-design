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
  Serial.begin(9600);

  pinMode(DATA_PIN, OUTPUT); // data pin
  pinMode(RECIEVER_PIN, INPUT);
  pinMode(2, OUTPUT);
  attachInterrupt(5, getMessage, RISING);

  // enable interrupts
  interrupts();
}

void loop() {
  sendMessage(commRecievedMsg);
  delay(1000);
  sendMessage(foundBlueMsg);
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
    delayMicroseconds(6 000);
  }
  
  // "1"
  digitalWrite(DATA_PIN, HIGH);
  delayMicroseconds(SAMPLE_TIME);
  // "0"
  digitalWrite(DATA_PIN, LOW);
  
  // set last messsge
  last_message = message;
}  
