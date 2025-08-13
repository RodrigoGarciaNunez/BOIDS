#include <iostream>
#include "object.h"
#include "view/GLFwindow.h"
//#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
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

    unique_ptr<Window> main_window = make_unique<Window>();
    //glfwMakeContextCurrent(window);
    vector<float> pos = {400.0f,300.0f};
    float centerX= screenWidth /2.0f;
    float centerY = screenHeight / 2.0f;
    float radio = 50.0f;
    int res = 100; 
    //Object * body = new Object(pos, 300);

    int width = 800, height = 600;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // sistema de coordenadas 2D
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while(!glfwWindowShouldClose(*(main_window->window_.get()))){
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        main_window->draw_body(pos[0], pos[1], 50.0f, 50);
        
        glfwSwapBuffers(*(main_window->window_.get())); 
        glfwPollEvents();
    }


    
    return 0;
}


// GLFWwindow* startGLFW(){
//     if(!glfwInit()){
//         cerr<< "Fallo al inicializar glfw" << endl;
//         return nullptr;
//     }

//     GLFWwindow* window = glfwCreateWindow(800, 600, "gravity_sim", NULL, NULL);
//     return window;
// }

// void DrawBody(float centerX, float centerY, float radio, int res){
//     glBegin(GL_TRIANGLE_FAN);
//     glVertex2d(centerX, centerY);

//     for(int i =0; i <= res; i++){
//         float angle = 2.0f * M_PI *(static_cast<float>(i)/res);
//         float x = centerX + cos(angle) * radio;
//         float y = centerY + sin(angle) * radio;
//         glVertex2d(x, y);
//     }
// }