#pragma once
// #ifndef GLF_WINDOW_H
// #define GLF_WINDOW_H


#define GLAD_GL_IMPLEMENTATION
#include "../../include/glad/glad.h"
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>
#include <cmath>
#include <vector>

using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;
using std::cerr;
using std::cout;
using std::endl;
using std::vector;

class Window{
public:
    Window(float screenHeight, float screenWidht);
    shared_ptr<GLFWwindow*> window_;

private:
    shared_ptr<GLFWwindow*>  start_GLF();
    
    struct {
        float screenHeight;
        float screenWidth;
        float centerX= screenWidth;
        float centerY = screenHeight;
    }properties;
};

//#endif