Alek Popovic
LAST UPDATED 03/11/2022

This is the preliminary code for the I2C communication between the
Arduino with the joystick and the Jetson. Becuase I did not have
access to the hardware I needed for a long time, I simulated everything
on tinkercad with 2 Arduinos. The code in the 2 Arduino files
successfully sends the voltage readings of each of the 3 potentiometers
in the joystick from one Arduino to another. The Arduinos/wiring can be
seen in the screenshot. Now that I have the necessary hardware, I
can start making adjustments to the code that receives the communication
so that it will work properly on a Jetson. The principles behind the
code will stay the same, and most of the code should look almost
identical to the current receiving code. The biggest differences will
likely be the I2C libraries that I use on the Jetson and the wiring to
connect the Arduino to the Jetson. 