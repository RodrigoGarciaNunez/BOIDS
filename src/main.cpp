#include <iostream>
#include "model/object.h"
#include "view/GLFwindow.h"
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
//#include <ctime>
//#include <memory>

//using namespace std;
using std::rand;
using std::srand;

using std::mt19937;
using std::random_device;
using std::uniform_real_distribution;
//using std::time;
// using std::make_shared;
// using std


float screenHeight = 600.0f;
float screenWidth = 800.0f;

int main(){
    
    //GLFWwindow* window = startGLFW();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-10, 10);


    unique_ptr<Window> main_window = make_unique<Window>(screenHeight, screenWidth);
    
    //glfwMakeContextCurrent(*(main_window->window_.get()));
    vector<float> pos = {100.0f,100.0f};
    vector<float> pos2 = {400.0f,100.0f};

    shared_ptr<Object> obj1 = make_shared<Object>(pos, 100, 50);
    shared_ptr<Object> obj2 = make_shared<Object>(pos2, 100, 50);
    vector<shared_ptr<Object>> objects = {obj1, obj2};
    float radio = 50.0f;
    int res = 100; 

    vector<float> movement;
    int elec;
    shared_ptr<Object> aux;
    shared_ptr<Object> aux1;
    while(!glfwWindowShouldClose(*(main_window->window_.get()))){

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();  // Reset del frame

        //cerr << "hola" << endl;
        
        for (auto object : objects){
            for (int i =0; i< 2; i++){
                movement.push_back(dist(gen));
            }    
            object->movement2d(movement);

            movement.clear();
        }
        //main_window->draw_body(pos[0], pos[1], 50.0f, 50);
       
        //main_window->move_body(movement, aux->properties_.position);
        //aux->movement2d(movement);

        //cerr << "update" << endl;
        glfwSwapBuffers(*(main_window->window_.get())); 
        glfwPollEvents();
   
    }


    
    return 0;
}


