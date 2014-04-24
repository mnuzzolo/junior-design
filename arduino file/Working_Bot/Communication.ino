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

void messageProtocol(int message) {
  // sendMessage! 
  int counter = 0;
  while( messageRecievedFlag != commRecievedMsg && counter < 20) {
    sendMessage(message);
    delay(500); // wait for response
    left(50);
    stop_motor(0);
    if(messageRecievedFlag) {

    }
    counter++;
  }

  for(int i = 0; i < counter; i++) {
    right(50);
  }
  forward(0);

}

