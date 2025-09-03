#include "user_interface.h"
#include "../model/object.h"

user_interface::user_interface(shared_ptr<GLFWwindow *> window, shared_ptr<Drawer> drw)
{
    glfwSetWindowUserPointer(*(window.get()), this);
    glfwSetMouseButtonCallback(*(window.get()), user_interface::add_object_by_click);
    drw_ = drw;
}

user_interface::~user_interface() {}

void user_interface::add_object_by_click(GLFWwindow *window, int button, int action, int mods)
{
    user_interface * ptr_ = static_cast<user_interface*>(glfwGetWindowUserPointer(window));
    if (ptr_ != nullptr)
    {
        shared_ptr<user_interface> this_= ptr_->shared_from_this(); 
        double x, y;

        glfwGetCursorPos(window, &x, &y);
        vector<float> position = {(float)x, (float)y};
        shared_ptr<Object> objeto = make_shared<Object>(position, 100, 50, this_->drw_);
        objeto->register_in_drawer();
    }
}