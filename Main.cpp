#include "Hoverpod/GUI/GUI.hpp"
#include "Hoverpod/IMU/IMU.hpp"

int main() {
    // https://en.cppreference.com/w/cpp/thread/thread
    // [] is lambda declaration (inline anonymous function)

    std::thread t([] { // [] {} == lambda
        while (true) { // run forever because if main thread exists, side thread exists
            this_thread::sleep_for(chrono::milliseconds(3));
            #ifdef JOYSTICK
            
            /*
            my thought process:
              communication: Joystick --> arduino --> jetson --> actuators/motors

              joystick data comes in as x,y,z and 1/0 where x-->x_axis, y-->y_axis, z-->roatation || button = HIGH/LOW,
              arduino parses data and sends to i2c using a Master-Slave connection (ask Electrical team for details)


              **FOR XYZ**
              jetson recieves data in this class
                  jetson determines what the pod should do i.e. moveForward(), moveBackward(), moveLeft(), moveRight(), rotateCW(), rotateCCW()
                  this is communicating with the actuator class where the commands ^ exists

               **FOR Button**
               jetson recieves a HIGH when button is pressed 
               if motors are off:
                    turnMotorOn() (ask Electrical team for details)
               else:
                    turnMotorOff() (ask Electrical team for details)

            */
            
            cout << "in Joystick controller" << endl;
            // Input from button goes 1-0 then we turn on
            if (buttonState == 1) {
            if (buttonState == 0 ) {
                for (int i = 0; i < takeOffSpeed; i++) {
                    increaseSpeed(i);
                }
                if (buttonState == 1) {
                    if (buttonState == 0) {
                        for (int j = 0; j > 0; j++) {
                            decreaseSpeed(j);
                        }
                    }
                }
            }
         }
            
    });
    t.detach(); // run seperate from main thread
    
    init_gui(); // do gui (which has loop inside of it)

    /*IMU imu;
    std::thread t1([&imu] { // [] {} == lambda 
        imu.do_imu(); // do gui (which has loop inside of it)
    });
    t1.detach(); // run seperate from main thread*/

    return 1; // success (should never reach this)
}
