#pragma once
// #ifndef OBJECT_H
// #define OBJECT_H

//#include <vector>
//#include "../view/drawer.h"
#include <memory>
#include <random>
#include <iostream>
#include <functional> //para pasar funciones como argumentos
#include <mutex>
#include <utility>
#include <cmath>


using std::make_unique;
using std::make_shared;
using std::enable_shared_from_this;
using std::unique_ptr;
using std::shared_ptr;
using std::mt19937;
using std::random_device;
using std::uniform_real_distribution;
using std::vector;
using std::pair;
using std::array;
using std::function;
using std::cerr;
using std::cout;
using std::endl;
using std::mutex;
using std::lock_guard;
using std::unique_lock;
using std::defer_lock;
using std::pow;
using std::cin;


#define X_SUPERIOR_LIM 750
#define Y_SUPERIOR_LIM 550
#define Z_SUPERIOR_LIM 550
#define X_INFERIOR_LIM 50
#define Y_INFERIOR_LIM 50
#define Z_INFERIOR_LIM 50

using properties_ = struct properties_{ 
        //vector<float> position;
        //vector<float> movement;
        array<float, 3> position;
        array<float, 3> movement;
        float mass;
        float radio;
        float acceleration;
        float speed;
};

struct Drawer; //fordward declaration

extern shared_ptr<Drawer> drawer; 

class Object:public enable_shared_from_this<Object>{
public:
    Object(array<float, 3> position, float mass, float radio);
    virtual ~Object();
    void movement2d(array<float, 3> movement);
    void movement2d();

    void record_object();
    
    properties_ getProperties();
    void run();

    array<float, 3> boid_movement(); //se usa static para evitar que dependa de la instanccia

  

private:

    shared_ptr<Object> this_;
    shared_ptr<Drawer> drawer_;
    properties_ properties;    
    
    static vector<shared_ptr<Object>> objects_dir;
    static mutex mtx;
    unique_lock<mutex> u_lock;
    
    
    //el lock_guard sólo se crea cuando quieras bloquear, se desbloquea al salir del scope. No debe ser static

};

//#endif