// C++ code
// Slave Sender

#include <Wire.h>

union floatToBytes {

  char buffer[4];
  float voltage;
  
};

void setup() {
  
  Wire.begin(1);
  Wire.onRequest(requestEvent); // register event
  
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
}

void loop(){
  
  delay(100);
    
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  
  // sending 12 bytes total (4 x 3)
  floatToBytes converter;
  
  converter.voltage = analogRead(A0);
  // respond with message of 4 bytes as expected by master
  Wire.write(converter.buffer, 4);
  
  converter.voltage = analogRead(A1);
  Wire.write(converter.buffer, 4);
  
  converter.voltage = analogRead(A2);
  Wire.write(converter.buffer, 4);
  
}
