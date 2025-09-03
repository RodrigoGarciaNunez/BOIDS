#include <iostream>
#include "model/object.h"
#include "view/GLFwindow.h"
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include "view/drawer.h"
#include "controller/user_interface.h"
//#include <ctime>
//#include <memory>

//using namespace std;
using std::rand;
using std::srand;
using std::thread;
using std::mt19937;
using std::random_device;
using std::uniform_real_distribution;
using std::make_shared;


//revisa toooodos los includes. Son una telaraña.

float screenHeight = 600.0f;
float screenWidth = 800.0f;

int main(){
    
    //GLFWwindow* window = startGLFW();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-5, 5);


    shared_ptr<Window> main_window = make_shared<Window>(screenHeight, screenWidth);
    shared_ptr<Drawer> drawer = make_shared<Drawer>();
    shared_ptr<user_interface> usr_int = make_shared<user_interface>(main_window->window_, drawer);
    //glfwMakeContextCurrent(*(main_window->window_.get()));
    vector<float> pos = {100.0f,100.0f};
    vector<float> pos2 = {400.0f,100.0f};

    shared_ptr<Object> obj1 = make_shared<Object>(pos, 100, 50, drawer);
    obj1->register_in_drawer();
    shared_ptr<Object> obj2 = make_shared<Object>(pos2, 100, 50, drawer);
    obj2->register_in_drawer();
    vector<shared_ptr<Object>> objects = {obj1, obj2};
    float radio = 50.0f;
    int res = 100; 

    //cerr << "hola" << endl;
    vector<float> movement;
    
    // vector<unique_ptr<thread>> threads={
    //     (make_unique<thread>(obj1)),  //como son shared, se están pasando como referencia
    //     (make_unique<thread>(obj2))
    // };


    while(!glfwWindowShouldClose(*(main_window->window_.get()))){

        for (auto object :  drawer->bodies_to_draw){
            for (int i =0; i< 2; i++){
                movement.push_back(dist(gen));
                //movement.push_back(1);
            } 
            object.first->movement2d(movement);
            movement.clear();
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();  // Reset del frame

        //cerr << "hola" << endl;
        
        
        drawer->update_frame();
      
        glfwSwapBuffers(*(main_window->window_.get())); 
        glfwPollEvents();
   
    }


    // for(auto &hilo : threads){
    //     hilo->join();
    // }


    
    return 0;
}


