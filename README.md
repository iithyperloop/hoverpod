![Build](https://github.com/hyperloopiit/hoverpod/actions/workflows/cmake.yml/badge.svg)
<br></br>
# Illinois Tech Hyperloop ( Website: __________ )
Hyperloop is an approach to reinvent cross continental travel; our organization built a Hoverpod that levitates using the principles of magnetic and electric conductance with a strong integration of power electronics.  

# Project Description
## IMU (Inertial Measurement Unit)
A sensor that has an accelerometer, gyroscope,  magnetometers, and a high power processor that is used to output real time acceleration and heading. We use this to calculate instantaneous velocity and position to display to the GUI and also used when calculating the movement of any mechanical devices.

## I2C (Inter Integrated Circuits)
The I2C, also known as IIC or I2C, is a device that is used to synchronous, multi-controller/multi-target, packet switched, single-ended, serial communication bus. We used it within our project to create a read or write only (MasterSlaveIO) communication channels to the different arduino devices based on the controller it would be connected to. 

## ESC (Electronic Speed Controller) ~ Actuator, Motor, ThrustVector, etc.
An electronic speed control is an electronic circuit that controls and regulates the speed of an electric motor. It may also provide reversing of the motor and dynamic braking. We utilized this, alongside a potentiometer and linear actuators and designed a model in which binary inputs can accurately depict 360 degree lateral freedom.

## BMS (Battery Management System)
A battery management system is any electronic system that manages a rechargeable battery, such as by protecting the battery from operating outside its safe operating area, monitoring its state, calculating secondary data, reporting that data, and controlling its environment. We use it for this purpose exactly because we have high amounts of magnetic and electric flux throughout our Hoverpod.

## GUI (Graphical User Interface)
A User Interface connected to our main PC, the Jetson Nano, that displays current speed, current temperature, etc. 

# What is Threading and How do we run our System

# Credits
## Software Team Members:
![GitHub Contributors Image](https://contrib.rocks/image?repo=hyperloopiit/hoverpod)
<br></br>

## Tech Sponsors:                  
SHI, 
Microsoft, 
Meta, 
Mathworks, 
Solidworks, 
Ansys, 
LG, 
UGC, 
Logitech, 
Intel,  
Raspberry Pi, 
Arduino, 
Dragon Plate

## Faculty + School:
Illinois Institute of Technology

# Wiki
Check out the [Wiki](https://github.com/hyperloopiit/hoverpod/wiki) for build instructions if your machine isn't Unix arm64

