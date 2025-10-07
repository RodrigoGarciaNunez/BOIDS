#pragma once

//#include "../model/object.h"
//#include "../view/drawer.h"
//#include "object_creator.h"

#define GLAD_GL_IMPLEMENTATION
#include "../../include/glad/glad.h"
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <vector>

using std::shared_ptr;
using std::unique_ptr;
using std::make_unique;
using std::make_shared;
using std::cerr;
using std::endl;
using std::vector;
using std::array;
using std::enable_shared_from_this;

struct Object;
struct object_creator;
struct Drawer;

extern shared_ptr<Drawer> drawer; 

class user_interface: public enable_shared_from_this<user_interface>{
public:
    user_interface(shared_ptr<GLFWwindow*> window, shared_ptr<Drawer> drw);
    virtual ~user_interface();
    
    static void add_object_by_click(GLFWwindow* window, int button, int action, int mods);

private:
    shared_ptr<GLFWwindow*> window;
    shared_ptr<Drawer> drw_;
    unique_ptr<object_creator> obj_creator;
};