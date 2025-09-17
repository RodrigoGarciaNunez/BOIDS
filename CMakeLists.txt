cmake_minimum_required(VERSION 3.0.0)
project(Gravity_engine)

add_executable(Gravity_engine src/main.cpp src/model/object.cpp 
            src/view/GLFwindow.cpp src/view/drawer.cpp
            src/controller/user_interface.cpp
            src/controller/object_creator.cpp)

target_link_libraries(Gravity_engine glfw glut OpenGL)