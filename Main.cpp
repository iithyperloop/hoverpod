#include "Hoverpod/GUI/GUI.hpp"
#include "Hoverpod/IMU/IMU.hpp"

int main() {
    // https://en.cppreference.com/w/cpp/thread/thread
    // [] is lambda declaration (inline anonymous function)
    std::thread t([] { // [] {} == lambda 
        init_gui(); // do gui (which has loop inside of it)
    });
    t.detach(); // run seperate from main thread
    
    while (true) { // run forever because if main thread exists, side thread exists
        #ifdef JOYSTICK
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
        #endif
        #ifdef GUI
        cout << "in GUI controller" << endl;  #endif
        #endif

        #ifdef IMU
        cout << "in Joystick controller" << endl;
        #endif
    }

    return 1; // success (should never reach this)
}
