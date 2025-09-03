#pragma once

#include "../model/object.h"
#include "../view/drawer.h"
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <vector>

using std::shared_ptr;
using std::make_shared;
using std::cerr;
using std::endl;
using std::vector;

struct Object;

class user_interface: public enable_shared_from_this<user_interface>{
public:
    user_interface(shared_ptr<GLFWwindow*> window, shared_ptr<Drawer> drw);
    virtual ~user_interface();
    
    static void add_object_by_click(GLFWwindow* window, int button, int action, int mods);

private:
    shared_ptr<GLFWwindow*> window;
    shared_ptr<Drawer> drw_;
};