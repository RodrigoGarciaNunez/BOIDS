#include <iostream>
#include "../src/view/GLFwindow.h"
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include "../src/view/drawer.h"
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

#define SCREEN_HEIGTH 640.0f
#define SCREEN_WIDTH 480.0f

int main(){
    
    //GLFWwindow* window = startGLFW();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-5, 5);


    shared_ptr<Window> main_window = make_shared<Window>(SCREEN_HEIGTH, SCREEN_WIDTH);
    shared_ptr<Drawer> drawer = make_shared<Drawer>(main_window->window_);

    while(!glfwWindowShouldClose(*(main_window->window_.get()))){
        drawer->render();
        cerr << "hola" << endl;
   
    }
    return 0;
}


