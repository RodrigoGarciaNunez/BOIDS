#pragma once
//#include "object.h"
#include <vector>
#include <memory>
#include <utility>
#include <thread>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::pair;
using std::array;
using std::thread;

struct Object;

class object_creator{
public:
    object_creator();
    virtual ~object_creator();

    shared_ptr<Object> create_object(array<float, 3> movement);
    vector<shared_ptr<thread>> objects;

private:
};