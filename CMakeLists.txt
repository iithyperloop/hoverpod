cmake_minimum_required(VERSION 3.10)

project(Hoverpod VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Actuator Actuator/Actuator.cpp Actuator/Actuator.hpp)
add_library(HeightSensor HeightSensor/HeightSensor.cpp HeightSensor/HeightSensor.hpp)
add_library(IMU IMU/IMU.cpp IMU/IMU.hpp)
add_library(Motor Motor/Motor.cpp Motor/Motor.hpp)
add_library(LandingGear LandingGear/LandingGear.cpp LandingGear/LandingGear.hpp)
add_library(Threading Threading/Threading.cpp Threading/Threading.hpp)
add_library(KalmanFilter KalmanFilter/KalmanFilter.cpp KalmanFilter/KalmanFilter.hpp)

add_executable(Hoverpod Main.cpp)

set_target_properties(Hoverpod PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Hoverpod PRIVATE Actuator)
target_link_libraries(Hoverpod PRIVATE HeightSensor)
target_link_libraries(Hoverpod PRIVATE IMU)
target_link_libraries(Hoverpod PRIVATE Motor)
target_link_libraries(Hoverpod PRIVATE LandingGear)
target_link_libraries(Hoverpod PRIVATE Threading)
target_link_libraries(Hoverpod PRIVATE KalmanFilter)