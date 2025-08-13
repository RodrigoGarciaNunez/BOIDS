cmake_minimum_required(VERSION 3.0.0)
project(Gravity_engine)

add_executable(Gravity_engine src/main.cpp src/object.cpp src/view/GLFwindow.cpp)

target_link_libraries(Gravity_engine glfw glut OpenGL)