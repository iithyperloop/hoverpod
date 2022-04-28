#include "Hoverpod/GUI/GUI.hpp"
#include "Hoverpod/IMU/IMU.hpp"

int main() {
    // https://en.cppreference.com/w/cpp/thread/thread
    // [] is lambda declaration (inline anonymous function)

    std::thread t([] { // [] {} == lambda
        while (true) { // run forever because if main thread exists, side thread exists
            this_thread::sleep_for(chrono::milliseconds(3));
            #ifdef JOYSTICK
            #include "bus.h"
            #include "i2c.h"
            
            /*
            my thought process:
              communication: Joystick --> arduino --> jetson --> actuators/motors

              joystick data comes in as x,y,z and 1/0 where x-->x_axis, y-->y_axis, z-->roatation || button = HIGH/LOW,
              arduino parses data and sends to i2c using a Master-Slave connection (ask Electrical team for details)

              float[]

              return [a, b];

              float[0] = a;
              float[1] = b;


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

                potentiometer is also looking at position?


            */

              cout << "in Joystick controller" << endl;

            #endif
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
