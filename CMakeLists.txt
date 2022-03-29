cmake_minimum_required(VERSION 3.10)

project(Hoverpod VERSION 1.0)

set(OpenGL_GL_PREFERENCE "GLVND")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Actuator Hoverpod/Actuator/Actuator.cpp Hoverpod/Actuator/Actuator.hpp)
add_library(IMU Hoverpod/IMU/IMU.cpp Hoverpod/IMU/IMU.hpp Hoverpod/IMU/DblIntegration.cpp)
add_library(Motor Hoverpod/Motor/Motor.cpp Hoverpod/Motor/Motor.hpp)
add_library(LandingGear Hoverpod/LandingGear/LandingGear.cpp Hoverpod/LandingGear/LandingGear.hpp)
add_library(Threading Hoverpod/Threading/Threading.cpp Hoverpod/Threading/Threading.hpp)
add_library(GUI Hoverpod/GUI/GUI.cpp Hoverpod/GUI/GUI.hpp)

add_executable(Hoverpod Main.cpp)

set_target_properties(Hoverpod PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Hoverpod PRIVATE Actuator)
target_link_libraries(Hoverpod PRIVATE IMU)
target_link_libraries(Hoverpod PRIVATE Motor)
target_link_libraries(Hoverpod PRIVATE LandingGear)
target_link_libraries(Hoverpod PRIVATE Threading)
target_link_libraries(Hoverpod PRIVATE GUI)

set(VNPROG_PATH "libs/vnproglib")
    
file(GLOB IMGUI_SOURCES ${VNPROG_PATH}/src/*.cpp) 
    
add_library(libvncxx STATIC ${IMGUI_SOURCES})
target_include_directories(libvncxx PUBLIC ${IMGUI_PATH}/include)

include_directories(
    libs/vnproglib/include)

target_link_libraries(Hoverpod PUBLIC libvncxx)

include_directories(
    libs/glfw/include)

if (UNIX)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif (UNIX)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)

target_link_libraries(Hoverpod PUBLIC glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(Hoverpod PUBLIC OpenGL::GL)

set(IMGUI_PATH "libs/imgui")
    
file(GLOB IMGUI_SOURCES
    ${IMGUI_PATH}/*.cpp
    ${IMGUI_PATH}/backends/*.cpp) 
    
add_library("ImGui" STATIC ${IMGUI_SOURCES})
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})
target_link_libraries(Hoverpod PUBLIC ImGui)