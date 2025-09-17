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
using std::function;
using std::cerr;
using std::endl;
using std::mutex;
using std::lock_guard;
using std::unique_lock;
using std::defer_lock;

using properties_ = struct properties_{ 
        //vector<float> position;
        //vector<float> movement;
        pair<float, float> position;
        pair<float, float> movement;
        float mass;
        float radio;
        float acceleration;
        float speed;
};

struct Drawer; //fordward declaration

class Object:public enable_shared_from_this<Object>{
public:
    Object(pair<float, float> position, float mass, float radio);
    virtual ~Object();
    void movement2d(pair<float, float> movement);
    void movement2d();

    void record_object();
    
    properties_ getProperties();
    void run();

    pair<float, float> boid_movement(); //se usa static para evitar que dependa de la instanccia

  

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