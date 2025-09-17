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
#include "controller/object_creator.h"
#include <mutex>
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
using std::mutex;
using std::unique_lock;
//revisa toooodos los includes. Son una telaraña.

float screenHeight = 600.0f;
float screenWidth = 800.0f;
mutex mtx;
unique_lock<mutex> u_lock(mtx, defer_lock); //defer lock es para que no se bloquee al instante

int main(){
    
    //GLFWwindow* window = startGLFW();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-5, 5);


    shared_ptr<Window> main_window = make_shared<Window>(screenHeight, screenWidth);
    shared_ptr<Drawer> drawer = make_shared<Drawer>();
    shared_ptr<user_interface> usr_int = make_shared<user_interface>(main_window->window_, drawer);
    shared_ptr<object_creator> obj_cr = make_shared<object_creator>();
    //glfwMakeContextCurrent(*(main_window->window_.get()));
    //vector<float> pos = {100.0f,100.0f};
    //vector<float> pos2 = {400.0f,100.0f};

    //shared_ptr<Object> obj1 = make_shared<Object>(pos, 100, 50, drawer);
    //obj1->record_object();
    //shared_ptr<Object> obj2 = make_shared<Object>(pos2, 100, 50, drawer);
    //obj2->record_object();
    //vector<shared_ptr<Object>> objects = {obj1};
    float radio = 50.0f;
    int res = 100; 

    //cerr << "hola" << endl;
    // vector<float> movement;
    
    // vector<shared_ptr<thread>> threads={
    //     make_shared<thread>(&Object::run,obj1),  //como son shared, se están pasando como "referencia"
    //     make_shared<thread>(&Object::run,obj2)
    // };


    while(!glfwWindowShouldClose(*(main_window->window_.get()))){

        // for (auto object :  drawer->bodies_to_draw){
        //     for (int i =0; i< 2; i++){
        //         movement.push_back(dist(gen));
        //         //movement.push_back(1);
        //     } 
        //     object.first->movement2d(movement);
        //     movement.clear();
        // }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();  // Reset del frame

        //cerr << "hola" << endl;
        
        u_lock.lock();
            drawer->update_frame();
        u_lock.unlock();

        glfwSwapBuffers(*(main_window->window_.get())); 
        glfwPollEvents();
   
    }


    for(auto &hilo : obj_cr->objects){
        hilo->join();
    }
    
    return 0;
}


