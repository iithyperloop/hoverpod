// C++ code
// Slave Sender

#include <Wire.h>

union floatToBytes {

  char buffer[4];
  float voltage;
  
};

const int xcompPin = A0;   
const int ycompPin = A1;   
const int zcompPin = A2;   
const int buttonPin = 8;

int run;

void setup() {
  run = 0;
  pinMode(buttonPin, INPUT_PULLUP);
  
  Serial.begin(9600);
  
  Wire.begin(1);
  Wire.onRequest(requestEvent); // register event

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

}

void loop(){

  // code you always run regardless of the button goes here
  // right now it just reads and prints out
  // Rest of the code will take outputs and use them to actually make stuff happen
  int xcomp = analogRead(xcompPin);
  int ycomp = analogRead(ycompPin);
  int zcomp = analogRead(zcompPin);
  int buttonState = digitalRead(buttonPin);   // read state of push button value

  //print results to Serial Monitor
  String output = "xcomp = " + String(xcomp) + " " +
                  "ycomp = " + String(ycomp) + " " +
                  "zcomp = " + String(zcomp) + " " +
                  "buttonState = " + String(buttonState);
  
  Serial.println(output);

  //check button press here and if it is pressed then toggle run variable between 0 and 255; REQUIRED!
 
  if (buttonState == LOW) {

    // functions based off of button pulling input pin LOW
    
    if (run == 0) {
      run = 255;
    } else {
      run = 0;
    }
    
  } if (run > 0) {

    // code for if button was pressed, stops running when button pressed again, so forth...
    
    // return output to let code know to turn pod off (extend landing gear and turn off engine)
    // actual code will be run outside of this, so we just need output to be letting other code know
  }
  
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
  
  converter.voltage = analogRead(xcompPin);
  Wire.write(converter.buffer, 4);
  
  converter.voltage = analogRead(ycompPin);
  Wire.write(converter.buffer, 4);

  converter.voltage = analogRead(buttonPin);
  Wire.write(converter.buffer, 4);
  
}
