// C++ code
// Master Reader

#include <Wire.h>
#include <HardwareSerial.h>

union floatToBytes {

  char buffer[4];
  float voltage;
  
};

void setup() {
  
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

}

void loop() {
  
  floatToBytes converter;
  Wire.requestFrom(1, 12);                  // request 12 bytes from peripheral device #1

  for (int i = 0; i < 4; i++) {             // peripheral may send less than requested
    converter.buffer[i] = Wire.read();
  }
  Serial.print("x: ");
  Serial.print(converter.voltage);         // print the voltage
  
  for (int i = 0; i < 4; i++) { 
    converter.buffer[i] = Wire.read();
  }
  Serial.print("\ty: ");
  Serial.print(converter.voltage);
  
  for (int i = 0; i < 4; i++) {
    converter.buffer[i] = Wire.read();
  }
  Serial.print("\tz: ");
  Serial.print(converter.voltage);
  Serial.println();
  
  delay(1000);
}
