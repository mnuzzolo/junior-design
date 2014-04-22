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
  if( messageRecievedFlag ) {
    Serial.print("Message recieved: ");
    Serial.println(messageRecievedFlag);
    messageRecievedFlag = 0; 
  }
}

void getMessage() {
  //Serial.print("in interrupt: ");
  //Serial.println(num_interrupts);
  // new message indicator
  if( millis() - lastInterrupt >= 500 ) {  
    num_interrupts = 1;
  }
  // deal with "end of message" indicator 
  else if( millis() - lastInterrupt >= 50 ) {
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
  //Serial.println("Sending message...");
  if( message == 1 ) {
    for(int i = 0; i < message; i++) {
      // "1"
      analogWrite(DATA_PIN, HIGH);
      delayMicroseconds(SAMPLE_TIME);
      // "0"
      analogWrite(DATA_PIN, LOW);
      delayMicroseconds(SAMPLE_TIME);
    }
  }

  // set last messsge
  last_message = message;
}  
