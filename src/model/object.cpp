#include "object.h"
#include "../view/drawer.h"

mutex Object::mtx;
vector<shared_ptr<Object>> Object::objects_dir;

Object::Object(pair<float,float> position, float mass, float radio) :u_lock(Object::mtx, defer_lock){
    properties.position=position;
    properties.mass=mass;
    properties.radio=radio;

    cerr << "objeto creado" << endl;
}

Object::~Object(){
}

void Object::record_object(){
    lock_guard<mutex> lguard(Object::mtx);  //bloquea y se desbloquea al salir del método
    this_ = shared_from_this(); 
    drawer_->bodies_to_draw[this_] = false;
    
    Object::objects_dir.push_back(shared_from_this());
}

void Object::movement2d(pair<float, float> movement_){

    lock_guard<mutex> lguard(Object::mtx); 
    properties.movement= movement_;
    float posible_position_x = properties.position.first+properties.movement.first;
    float posible_position_y = properties.position.second+properties.movement.second;

    properties.position.first= (posible_position_x>0 && posible_position_x < 800) ? posible_position_x : properties.position.first;
    properties.position.second= (posible_position_y>0 && posible_position_y < 600) ? posible_position_y : properties.position.second;

    //si se piensa hacer que cada objeto tenga su hilo, aquí habrá competencia.
    drawer_->bodies_to_draw[shared_from_this()] = true;  
}

void Object::movement2d(){
    lock_guard<mutex> lguard(Object::mtx); 
    properties.movement =  boid_movement();

    float posible_position_x = properties.position.first+properties.movement.first;
    float posible_position_y = properties.position.second+properties.movement.second;

    properties.position.first= (posible_position_x>0 && posible_position_x < 800) ? posible_position_x : properties.position.first;
    properties.position.second= (posible_position_y>0 && posible_position_y < 600) ? posible_position_y : properties.position.second;

    //si se piensa hacer que cada objeto tenga su hilo, aquí habrá competencia.
    drawer_->bodies_to_draw[shared_from_this()] = true;  

}

pair<float, float> Object::boid_movement(){
    float xpos_avg, ypos_avg, xvel_avg, yvel_avg, neighboring_boids, close_dx, close_dy = 0;
    float dx, dy, squared_dist = 0;
    float centroid_x, centroid_y = 0;
    pair<float, float> movement={0,0};
    int i=0;
    for(auto &boid : objects_dir){
        
        if(boid != this_){
            dx = properties.position.first - boid->properties.position.first;
            dy = properties.position.second - boid->properties.position.second;

            if(abs(dx) < properties.radio && abs(dy) < properties.radio){
                squared_dist = dx*dx + dy*dy;

                centroid_x += boid->properties.position.first;
                centroid_y += boid->properties.position.second;
                i++;
            }
        }
    }

    if(i > 0){
        centroid_x /= i;
        centroid_y /=i;

        movement={(centroid_x - properties.position.first) * 0.01f,(centroid_y - properties.position.second) * 0.01f};
    }
    return movement;
}

properties_ Object::getProperties(){
    return properties;
}

void Object::run(){
    pair<float, float> movement;
  
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-0.5, 0.5);
    
    movement.first = dist(gen);
    movement.second = dist(gen); 
    while(true){
        
        movement2d();
    }
}




