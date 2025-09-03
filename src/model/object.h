#pragma once
// #ifndef OBJECT_H
// #define OBJECT_H

#include <vector>
//#include "../view/drawer.h"
#include <memory>
#include <random>
#include <iostream>


using std::make_unique;
using std::make_shared;
using std::enable_shared_from_this;
using std::unique_ptr;
using std::shared_ptr;
using std::mt19937;
using std::random_device;
using std::uniform_real_distribution;
using std::vector;

using std::cerr;
using std::endl;

using properties_ = struct properties_{
        vector<float> position;
        vector<float> movement;
        float mass;
        float radio;
        float acceleration;
        float speed;
};

struct Drawer; //fordward declaration

class Object:public enable_shared_from_this<Object>{
public:
    Object(vector<float> position, float mass, float radio, shared_ptr<Drawer> drawer);
    virtual ~Object();
    void movement2d(vector<float> movement);

    void register_in_drawer();
    
    properties_ getProperties();
    void run();

    
    bool did_it_change;

private:
    shared_ptr<Drawer> drawer_;
    properties_ properties;    
    
    

    // random_device rd;
    // mt19937 gen(random_device());
    // uniform_real_distribution<> dist(mt19937);


};

//#endif