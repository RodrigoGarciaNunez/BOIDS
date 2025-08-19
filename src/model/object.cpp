#include "object.h"

Object::Object(vector<float> position, float mass){
    properties_.position=position;
    properties_.mass=mass;
}

Object::~Object(){
}

void Object::movement2d(vector<float> movement){
    properties_.position[0]+=movement[0];
    properties_.position[1]+=movement[1];
}


