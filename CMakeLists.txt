cmake_minimum_required(VERSION 3.10)

project(Hoverpod VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Actuator Actuator/Actuator.cpp Actuator/Actuator.hpp)
add_library(IMU IMU/IMU.cpp IMU/IMU.hpp IMU/DblIntegration.cpp)
add_library(Motor Motor/Motor.cpp Motor/Motor.hpp)
add_library(LandingGear LandingGear/LandingGear.cpp LandingGear/LandingGear.hpp)
add_library(Threading Threading/Threading.cpp Threading/Threading.hpp)

add_executable(Hoverpod Main.cpp)

set_target_properties(Hoverpod PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Hoverpod PRIVATE Actuator)
target_link_libraries(Hoverpod PRIVATE IMU)
target_link_libraries(Hoverpod PRIVATE Motor)
target_link_libraries(Hoverpod PRIVATE LandingGear)
target_link_libraries(Hoverpod PRIVATE Threading)
target_link_libraries(Hoverpod PRIVATE KalmanFilter)

set(VNPROG
        vnproglib/src/attitude.cpp
        vnproglib/src/compositedata.cpp
        vnproglib/src/conversions.cpp
        vnproglib/src/criticalsection.cpp
        vnproglib/src/dllvalidator.cpp
        vnproglib/src/error_detection.cpp
        vnproglib/src/event.cpp
        vnproglib/src/ezasyncdata.cpp
        vnproglib/src/memoryport.cpp
        vnproglib/src/packet.cpp
        vnproglib/src/packetfinder.cpp
        vnproglib/src/port.cpp
        vnproglib/src/position.cpp
        vnproglib/src/rtcmlistener.cpp
        vnproglib/src/rtcmmessage.cpp
        vnproglib/src/searcher.cpp
        vnproglib/src/sensors.cpp
        vnproglib/src/serialport.cpp
        vnproglib/src/thread.cpp
        vnproglib/src/types.cpp
        vnproglib/src/util.cpp
        vnproglib/src/utilities.cpp
        vnproglib/src/vntime.cpp
        vnproglib/include/vn/exceptions.h
        vnproglib/include/vn/matrix.h
        vnproglib/include/vn/attitude.h
        vnproglib/include/vn/boostpython.h
        vnproglib/include/vn/dllvalidator.h
        vnproglib/include/vn/signal.h
        vnproglib/include/vn/error_detection.h
        vnproglib/include/vn/position.h
        vnproglib/include/vn/registers.h
        vnproglib/include/vn/rtcmlistener.h
        vnproglib/include/vn/rtcmmessage.h
        vnproglib/include/vn/utilities.h
        vnproglib/include/vn/memoryport.h
        vnproglib/include/vn/nocopy.h
        vnproglib/include/vn/compositedata.h
        vnproglib/include/vn/criticalsection.h
        vnproglib/include/vn/compiler.h
        vnproglib/include/vn/sensors.h
        vnproglib/include/vn/searcher.h
        vnproglib/include/vn/event.h
        vnproglib/include/vn/ezasyncdata.h
        vnproglib/include/vn/serialport.h
        vnproglib/include/vn/export.h
        vnproglib/include/vn/vector.h
        vnproglib/include/vn/vntime.h
        vnproglib/include/vn/packetfinder.h
        vnproglib/include/vn/conversions.h
        vnproglib/include/vn/types.h
        vnproglib/include/vn/int.h
        vnproglib/include/vn/thread.h
        vnproglib/include/vn/mock.h
        vnproglib/include/vn/port.h
        vnproglib/include/vn/util.h
        vnproglib/include/vn/consts.h
        vnproglib/include/vn/packet.h)

include_directories(
    vnproglib/include)

add_library(libvncxx ${VNPROG})