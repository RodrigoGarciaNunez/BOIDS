#pragma
// #ifndef GLF_WINDOW_H
// #define GLF_WINDOW_H


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
    void draw_frame(float centerX, float centerY, float radio, int re);
    void move_body(vector<float>movement, vector<float> prev_pos);
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