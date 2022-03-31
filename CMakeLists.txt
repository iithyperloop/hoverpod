cmake_minimum_required(VERSION 3.10)

project(Hoverpod VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find vnproglib source files
set(VNPROG_PATH libs/vnproglib)
file(GLOB VNPROG_SOURCES ${VNPROG_PATH}/src/*.cpp) 
include_directories(${VNPROG_PATH}/include)

# Find ImGui source files
set(IMGUI_PATH libs/imgui)
file(GLOB_RECURSE IMGUI_SOURCES ${IMGUI_PATH}/*.cpp)
include_directories(${IMGUI_PATH})

# Add hoverpod cpp files to be compiled and set language to c++
add_executable(Hoverpod Main.cpp
                        Hoverpod/Actuator/Actuator.cpp
                        Hoverpod/IMU/IMU.cpp
                        Hoverpod/Motor/Motor.cpp
                        Hoverpod/LandingGear/LandingGear.cpp
                        Hoverpod/Threading/Threading.cpp
                        Hoverpod/GUI/GUI.cpp
                        ${VNPROG_SOURCES}
                        ${IMGUI_SOURCES})
set_target_properties(Hoverpod PROPERTIES LINKER_LANGUAGE CXX)

# Needed for std::thread on unix
if (UNIX)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif (UNIX)

# Add and link glfw library
include_directories(libs/glfw/include)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw)
target_link_libraries(Hoverpod PUBLIC glfw)

# Link OpenGL library
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
target_link_libraries(Hoverpod PUBLIC OpenGL::GL)