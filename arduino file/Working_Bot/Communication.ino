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
  // increment counter
  else {
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

void messageProtocol(int message) {
  // sendMessage! 
  int counter = 0;
  while( messageRecievedFlag != commRecievedMsg) {
    sendMessage(message);
    delay(100); // wait for response
      Serial.println("sending message...");
    if(!messageRecievedFlag) {
      left(70);
      stop_motor(0);
    }
     
    counter++;
  }
  
  if(messageRecievedFlag) {
     Serial.println("got confirmation!"); 
  }
  
  digitalWrite(32, HIGH);
  delay(500);
  digitalWrite(32, LOW);

  for(int i = 0; i < counter; i++) {
    right(70);
    stop_motor(0);
  }
  stop_motor(0);

}

