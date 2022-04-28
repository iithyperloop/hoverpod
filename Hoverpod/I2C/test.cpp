/*============================================================================
 *  Name        : BlinkSample.cpp
 *  Author      : praful vanker
 *  Version     :
 *  Copyright   : GPL-3.0-only
 *  			  Everyone is permitted to copy and distribute verbatim copies
 *  			  of this license document, but changing it is not allowed.
 *  Description : Blink LED connected to Pin 40
============================================================================*/

#ifdef __linux__
#include <iostream>
#include <unistd.h>


#ifdef JOYSTICK
#include "thrustVectoring.h"
#endif


#ifdef GUI
#include "GUI.h"
#endif

#ifdef IMU
#include "IMU.h"
#endif

//using namespace pmvankerNano;

/*int main() {

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
  
  return 0;
}*/
#endif
