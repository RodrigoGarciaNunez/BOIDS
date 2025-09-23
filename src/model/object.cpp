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
    
    //lock_guard<mutex> lguard(Object::mtx); 
    //u_lock.lock();
    pair<float, float> posible_movement = boid_movement();
    //cerr << "x_mov: "<<posible_movement.first << " y_mov:" << posible_movement.second<< endl;

    if(posible_movement.first == 0 && posible_movement.second==0){
        //cerr << "inercico" << endl;
        posible_movement.first =  properties.movement.first;
        posible_movement.second = properties.movement.second;
    } 

    //properties.movement =  (posible_movement.first!= 0 || posible_movement.second!= 0) ? posible_movement : properties.movement;
     
    float posible_position_x = properties.position.first+posible_movement.first;
    float posible_position_y = properties.position.second+posible_movement.second;

    //cerr << "x_pos_mov: "<<posible_movement.first << " y_pos_mov:" << posible_movement.second<< endl;

    properties.position.first= (posible_position_x>=50 && posible_position_x <=750) ? 
                                posible_position_x : posible_position_x-20*(posible_movement.first);
    
    properties.position.second= (posible_position_y>=50 && posible_position_y <=550) ? 
                                posible_position_y : posible_position_y-2*(posible_movement.second);

    //cerr << "x: "<<properties.position.first << " y:" << properties.position.second<< endl;
     //si se piensa hacer que cada objeto tenga su hilo, aquí habrá competencia.
    u_lock.lock();
    drawer_->bodies_to_draw[shared_from_this()] = true;  
    u_lock.unlock();
}

pair<float, float> Object::boid_movement(){
    float xpos_avg=0.0f; 
    float ypos_avg=0.0f; 
    float xvel_avg=0.0f; 
    float yvel_avg=0.0f; 
    float close_dx= 0.0f; 
    float close_dy = 0.0f;
    float visual_range = 2*(properties.radio)+20.0f;
    float protected_range = 2*(properties.radio)+10.0f;
    float dx=0.0f;
    float dy=0.0f;
    float squared_dist = 0.0f;
    float centering_factor = 0.005f;
    float matching_factor = 0.05f;
    float avoid_factor = 0.05f;
    float aux_mov_x=0.0f;
    float aux_mov_y=0.0f; 
    float aux_pos_x=0.0f; 
    float aux_pos_y = 0.0;

    pair<float, float> self_pos = properties.position;
    pair<float, float> self_mov = properties.movement;
    //pair<float, float> other_boid_pos, other_boid_mov;
    pair<float, float> movement={0.0f,0.0f};
    int neighbor=0;
    u_lock.lock();
    for(auto &boid : objects_dir){
        if(boid != this_){
            dx = self_pos.first - boid->properties.position.first;
            dy = self_pos.second - boid->properties.position.second;

            if(abs(dx) < visual_range && abs(dy) < visual_range){
                squared_dist = dx*dx + dy*dy;

                if (squared_dist < pow(protected_range, 2.0f)){
                    close_dx += self_pos.first- boid->properties.position.first;
                    close_dy += self_pos.second- boid->properties.position.second;
                }
                else if(squared_dist < pow(visual_range,2.0f)){
                    xpos_avg += boid->properties.position.first;
                    ypos_avg += boid->properties.position.second;

                    xvel_avg += boid->properties.movement.first;
                    yvel_avg += boid->properties.movement.second;
                    neighbor++;
                }
                
            }
        }
    }
    u_lock.unlock();
    //cerr << xpos_avg << endl;
    if(neighbor > 0){
        
        xpos_avg /= neighbor;
        ypos_avg /= neighbor;
        xvel_avg /= neighbor;
        yvel_avg /= neighbor;

        aux_mov_x= self_mov.first + (xpos_avg - self_pos.first)*centering_factor +
                (xvel_avg- self_mov.first)* matching_factor;
        
        aux_mov_y= self_mov.second + (ypos_avg - self_pos.second)*centering_factor +
                (yvel_avg- self_mov.second)* matching_factor;

    }

    aux_mov_x += (close_dx*avoid_factor);
    aux_mov_y += (close_dy*avoid_factor);

    movement={aux_mov_x,aux_mov_y};
    return movement;
}

properties_ Object::getProperties(){
    return properties;
}

void Object::run(){
    pair<float, float> movement;
  
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-0.05, 0.05);
    movement.first = dist(gen);
    movement.second = dist(gen);
    movement2d(movement); //primer_movimiento aleatorio
    
    while(true){
        
        movement2d();
    }
}




