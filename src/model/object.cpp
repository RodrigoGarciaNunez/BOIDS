#include "object.h"
#include "../view/drawer.h"

mutex Object::mtx;
vector<shared_ptr<Object>> Object::objects_dir;

Object::Object(array<float,3> position, float mass, float radio) :u_lock(Object::mtx, defer_lock){
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

void Object::movement2d(array<float, 3> movement_){

    lock_guard<mutex> lguard(Object::mtx); 
    properties.movement= movement_;
    float posible_position_x = properties.position[0]+properties.movement[0];
    float posible_position_y = properties.position[1]+properties.movement[1];
    float posible_position_z = properties.position[2]+properties.movement[2];

    properties.position[0]= (posible_position_x>0 && posible_position_x < 800) ? posible_position_x : properties.position[0];
    properties.position[1]= (posible_position_y>0 && posible_position_y < 600) ? posible_position_y : properties.position[1];
    properties.position[2]= (posible_position_z>0 && posible_position_z < 600) ? posible_position_z : properties.position[2];

    //si se piensa hacer que cada objeto tenga su hilo, aquí habrá competencia.
    drawer_->bodies_to_draw[shared_from_this()] = true;  
}

void Object::movement2d(){
    
    //lock_guard<mutex> lguard(Object::mtx); 
    //u_lock.lock();
    array<float, 3> posible_movement = boid_movement();
    //cerr << "x_mov: "<<posible_movement[0] << " y_mov:" << posible_movement[1]<< endl;

    if(posible_movement[0] == 0 && posible_movement[1]==0 && posible_movement[2] == 0){
        //cerr << "inercico" << endl;
        posible_movement[0] =  properties.movement[0];
        posible_movement[1] = properties.movement[1];
        posible_movement[2] = properties.movement[2];
    } 

    //properties.movement =  (posible_movement[0]!= 0 || posible_movement[1]!= 0) ? posible_movement : properties.movement;
     
    float posible_position_x = properties.position[0]+posible_movement[0];
    float posible_position_y = properties.position[1]+posible_movement[1];
    float posible_position_z = properties.position[2]+posible_movement[2]; 

    //cout << "x_pos_mov: "<<posible_movement[0] << " y_pos_mov:" << posible_movement[1]<< "z_pos_mov"<< endl;

    properties.position[0]= (posible_position_x>=50 && posible_position_x <=750) ? 
                                posible_position_x : posible_position_x-20*(posible_movement[0]);
    
    properties.position[1]= (posible_position_y>=50 && posible_position_y <=550) ? 
                                posible_position_y : posible_position_y-2*(posible_movement[1]);

    properties.position[2] = (posible_position_z>=50 && posible_position_z <=550) ? 
                                posible_position_z : posible_position_z-2*(posible_movement[2]);
    //cin.get();
    cout << "x"<<this_.get()<<": "<<properties.position[0] << " y:" << properties.position[1]<< " z:"<< properties.position[2]<<endl;
     //si se piensa hacer que cada objeto tenga su hilo, aquí habrá competencia.
    u_lock.lock();
    drawer_->bodies_to_draw[shared_from_this()] = true;  
    u_lock.unlock();
}

array<float, 3> Object::boid_movement(){
    float xpos_avg=0.0f; 
    float ypos_avg=0.0f;
    float zpos_avg = 0.0f; 
    float xvel_avg=0.0f; 
    float yvel_avg=0.0f; 
    float zvel_avg=0.0f;
    float close_dx= 0.0f; 
    float close_dy = 0.0f;
    float close_dz= 0.0f;
    float visual_range = 2*(properties.radio)+20.0f;
    float protected_range = 2*(properties.radio)+10.0f;
    float dx=0.0f;
    float dy=0.0f;
    float dz=0.0f;
    float squared_dist = 0.0f;
    float centering_factor = 0.005f;
    float matching_factor = 0.05f;
    float avoid_factor = 0.05f;
    float aux_mov_x=0.0f;
    float aux_mov_y=0.0f; 
    float aux_mov_z=0.0f;
    float aux_pos_x=0.0f; 
    float aux_pos_y=0.0;
    float aux_pos_z=0.0f;

    array<float, 3> self_pos = properties.position;
    array<float, 3> self_mov = properties.movement;
    //pair<float, float> other_boid_pos, other_boid_mov;
    array<float, 3> movement={0.0f,0.0f,0.0f};
    int neighbor=0;
    u_lock.lock();
    for(auto &boid : objects_dir){
        if(boid != this_){
            dx = self_pos[0] - boid->properties.position[0];
            dy = self_pos[1] - boid->properties.position[1];
            dz = self_pos[2] - boid->properties.position[2];

            if(abs(dx) < visual_range && abs(dy) < visual_range && abs(dz) < visual_range){
                squared_dist = dx*dx + dy*dy + dz*dz;

                if (squared_dist < pow(protected_range, 2.0f)){
                    close_dx += self_pos[0]- boid->properties.position[0];
                    close_dy += self_pos[1]- boid->properties.position[1];
                    close_dz += self_pos[2]- boid->properties.position[2];
                }
                else if(squared_dist < pow(visual_range,2.0f)){
                    xpos_avg += boid->properties.position[0];
                    ypos_avg += boid->properties.position[1];
                    zpos_avg += boid->properties.position[2];

                    xvel_avg += boid->properties.movement[0];
                    yvel_avg += boid->properties.movement[1];
                    zpos_avg += boid->properties.position[2];

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
        zpos_avg /= neighbor;
        xvel_avg /= neighbor;
        yvel_avg /= neighbor;
        zvel_avg /= neighbor;

        aux_mov_x= self_mov[0] + (xpos_avg - self_pos[0])*centering_factor +
                (xvel_avg- self_mov[0])* matching_factor;
        
        aux_mov_y= self_mov[1] + (ypos_avg - self_pos[1])*centering_factor +
                (yvel_avg- self_mov[1])* matching_factor;

        aux_mov_z= self_mov[2] + (zpos_avg - self_pos[2])*centering_factor +
            (zvel_avg- self_mov[2])* matching_factor;

    }

    aux_mov_x += (close_dx*avoid_factor);
    aux_mov_y += (close_dy*avoid_factor);
    aux_mov_z += (close_dz*avoid_factor);

    movement={aux_mov_x,aux_mov_y,aux_mov_z};
    return movement;
}

properties_ Object::getProperties(){
    return properties;
}

void Object::run(){
    array<float, 3> movement;
  
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-5, 5);
    movement[0] = dist(gen);
    movement[1] = dist(gen);
    movement[2] = dist(gen);
    movement2d(movement); //primer_movimiento aleatorio
    
    while(true){
        movement2d();
    }
}




