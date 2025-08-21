#include "object.h"

Object::Object(vector<float> position, float mass, float radio){
    properties_.position=position;
    properties_.mass=mass;
    properties_.radio=radio;
    drawer = make_unique<Drawer>();
}

Object::~Object(){
}

void Object::movement2d(vector<float> movement){
    float posible_position_x = properties_.position[0]+movement[0];
    float posible_position_y = properties_.position[1]+movement[1];

    properties_.position[0]= (posible_position_x>0 && posible_position_x < 800) ? posible_position_x : properties_.position[0];
    properties_.position[1]= (posible_position_y>0 && posible_position_y < 600) ? posible_position_y : properties_.position[1];

    drawer->Draw_body(properties_.position[0], 
        properties_.position[1], properties_.radio, 50);
}


