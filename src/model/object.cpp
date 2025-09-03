#include "object.h"
#include "../view/drawer.h"

Object::Object(vector<float> position, float mass, float radio, shared_ptr<Drawer> drawer){
    properties.position=position;
    properties.mass=mass;
    properties.radio=radio;
    //cerr << "objeto creado 0" << endl;
    drawer_ = drawer;
      //pasamos un shared de sí mismo para que el drawer sepa a quien sí actualizar

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-50, 50);

    cerr << "objeto creado" << endl;
}

Object::~Object(){
}

void Object::register_in_drawer(){
    drawer_->bodies_to_draw[shared_from_this()] = false;
}

void Object::movement2d(vector<float> movement_){
    properties.movement=movement_;

    float posible_position_x = properties.position[0]+properties.movement[0];
    float posible_position_y = properties.position[1]+properties.movement[1];

    properties.position[0]= (posible_position_x>0 && posible_position_x < 800) ? posible_position_x : properties.position[0];
    properties.position[1]= (posible_position_y>0 && posible_position_y < 600) ? posible_position_y : properties.position[1];


    //si se piensa hacer que cada objeto tenga su hilo, aquí habrá competencia.
    drawer_->bodies_to_draw[shared_from_this()] = true;  
    
}

properties_ Object::getProperties(){
    return properties;
}

void Object::run(){
    vector<float> movement;
  
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-50, 50);
    
    while(true){
        movement.push_back(dist(gen));
        movement.push_back(dist(gen)); 
        movement2d(movement);
    }
}




