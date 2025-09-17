#include "object_creator.h"
#include "../model/object.h"

object_creator::object_creator(){}

object_creator::~object_creator(){}

shared_ptr<Object> object_creator::create_object(pair<float, float> position){
    
    shared_ptr<Object> obj = make_shared<Object>(position, 100, 50);
    
    objects.push_back(make_shared<thread>(&Object::run, obj));

    return obj;
}