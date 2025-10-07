#include "object_creator.h"
#include "../model/object.h"

object_creator::object_creator(){}

object_creator::~object_creator(){}

shared_ptr<Object> object_creator::create_object(array<float,3> position){
    
    shared_ptr<Object> obj = make_shared<Object>(position, 100, 50);
    obj->record_object();    
    objects.push_back(make_shared<thread>(&Object::run, obj));

    return obj;
}

void object_creator::free_trhreads(){
    for(auto &obj: objects){
        obj->join();
    }
}