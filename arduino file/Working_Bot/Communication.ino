void getMessage() {
  //Serial.print("in interrupt: ");
  //Serial.println(num_interrupts);
  // new message indicator
  if( millis() - lastMsgInterrupt >= 500 ) {  
    num_interrupts = 1;
  }
  // deal with "end of message" indicator 
  else if( millis() - lastMsgInterrupt >= 50 ) {
    messageRecievedFlag = num_interrupts;
    num_interrupts = 1;
  }
  // increment counters
  else if( millis() - lastMsgInterrupt >= 3) {
    num_interrupts++;
  }
  lastMsgInterrupt = millis();
}

void decodeMessage() {
  //Serial.println("Decoding message...");
  if( messageRecievedFlag == commRecievedMsg ) {
    // message recieved
  }
  else if( messageRecievedFlag == foundBlueMsg ) {
    // set blue found flag
    color_to_find = "RED";
    sendMessage(commRecievedMsg); 
    delay(500);
    sendMessage(commRecievedMsg);   
  } 
  else if( messageRecievedFlag == foundRedMsg ) {
    // set red found flag
    color_to_find = "BLUE";
    sendMessage(commRecievedMsg);
  } 
  else if( messageRecievedFlag == invalidMsg ) {
    // set red found flag
    sendMessage(last_message);
  } 
  else {
    sendMessage(invalidMsg);
  }
}

void sendMessage(int message) {
  noInterrupts();
  digitalWrite(32, HIGH);
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
    delayMicroseconds(5500);
  }
  
  digitalWrite(32, LOW);

  // "1"
  digitalWrite(DATA_PIN, HIGH);
  delayMicroseconds(SAMPLE_TIME);
  // "0"
  digitalWrite(DATA_PIN, LOW);

  // set last messsge
  last_message = message;
  interrupts();
}  

void messageProtocol(int message) {
  // sendMessage! 
  int counter = 0;
  while( ! (messageRecievedFlag >= (commRecievedMsg - 5) && messageRecievedFlag <= (commRecievedMsg + 5) ) && counter < 20 ) {
    delay(25);
    sendMessage(message);
    delay(700); // wait for response
    if(!messageRecievedFlag) {
      if(message==foundRedMsg) {
        right(COMM_TURN_AMT); 
      }
      else if(message==foundBlueMsg) {
        left(COMM_TURN_AMT);
      }
      else {
        left(COMM_TURN_AMT); 
      }
      stop_motor(0);
    }
    else if (messageRecievedFlag > 1) {
      Serial.print("message is: "); 
      Serial.println(messageRecievedFlag);
    }

  if(message != finishedTrack)
    counter++;
  }

  if(messageRecievedFlag) {
    digitalWrite(34, HIGH);
    Serial.print("got confirmation!");
    messageRecievedFlag = 0;
  }
  
  delay(500);
  digitalWrite(34, LOW);

  for(int i = 0; i < counter/2; i++) {
    if(message==foundBlueMsg) {
      right(COMM_TURN_AMT-3);
    }
    else {
      left(COMM_TURN_AMT-3); 
    }
    stop_motor(0);
    delay(100);
  }
  stop_motor(0);
  
}


