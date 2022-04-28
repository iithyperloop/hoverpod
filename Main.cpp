#include "Hoverpod/GUI/GUI.hpp"
#include "Hoverpod/IMU/IMU.hpp"
#include "Hoverpod/Actuator/Actuator.hpp"
#include "Hoverpod/Motor/Motor.hpp"
#ifdef __linux__
#include "bus.h"
#include "i2c.h"
#endif

struct joystick_data { float x, y, z; };

int main() {
    // https://en.cppreference.com/w/cpp/thread/thread
    // [] is lambda declaration (inline anonymous function)

    std::thread t([] { // [] {} == lambda
        while (true) { // run forever because if main thread exists, side thread exists
            this_thread::sleep_for(chrono::milliseconds(3));
            
            auto get_joystick_data = []() -> joystick_data {
                // do that here
                return joystick_data{1,1,1}; // placeholder
            };

            /*
            my thought process:
              communication: Joystick --> arduino --> jetson --> actuators/motors

              joystick data comes in as x,y,z and 1/0 where x-->x_axis, y-->y_axis, z-->roatation || button = HIGH/LOW,
              arduino parses data and sends to i2c using a Master-Slave connection (ask Electrical team for details)

              float[]

              return [a, b];

              float[0] = a;
              float[1] = b;
>>>>>>> abbd54760d6a20d4fc18c19d6f02357ec7920850

            // faith does xyz handling (insert here)

            /*
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
