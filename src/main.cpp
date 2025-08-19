#include <iostream>
#include "model/object.h"
#include "view/GLFwindow.h"
//#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>
//#include <memory>

using namespace std;
// using std::make_shared;
// using std

//GLFWwindow* startGLFW();
//void DrawBody(float centerX, float centerY, float radio, int res);

float screenHeight = 600.0f;
float screenWidth = 800.0f;

int main(){
    
    //GLFWwindow* window = startGLFW();

    unique_ptr<Window> main_window = make_unique<Window>(screenHeight, screenWidth);
    
    //glfwMakeContextCurrent(*(main_window->window_.get()));
    vector<float> pos = {400.0f,300.0f};
    shared_ptr<Object> obj1 = make_shared<Object>(pos, 100);
    float radio = 50.0f;
    int res = 100; 

    vector<float> movement= {5.0f, 5.0f};
    
    while(!glfwWindowShouldClose(*(main_window->window_.get()))){
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();  // Reset del frame
        //main_window->draw_body(pos[0], pos[1], 50.0f, 50);
       
        main_window->move_body(movement, obj1->properties_.position);
        obj1->movement2d(movement);

        cerr << "update" << endl;
        glfwSwapBuffers(*(main_window->window_.get())); 
        glfwPollEvents();

        this_thread::sleep_for(chrono::milliseconds(100));
   
    }


    
    return 0;
}


