#include "user_interface.h"
#include "object_creator.h"
#include "../view/drawer.h"
#include "../model/object.h"

user_interface::user_interface(shared_ptr<GLFWwindow *> window, shared_ptr<Drawer> drw)
{
    glfwSetWindowUserPointer(*(window.get()), this);
    glfwSetMouseButtonCallback(*(window.get()), user_interface::add_object_by_click);
    drw_ = drw;
    obj_creator = make_unique<object_creator>();
}

user_interface::~user_interface() {}

void user_interface::add_object_by_click(GLFWwindow *window, int button, int action, int mods)
{

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        user_interface *ptr_ = static_cast<user_interface *>(glfwGetWindowUserPointer(window));
        if (ptr_ != nullptr)
        {
            shared_ptr<user_interface> this_ = ptr_->shared_from_this();
            double x, y;

            glfwGetCursorPos(window, &x, &y);
            array<float, 3> position = {(float)x, (float)y, 100.0f};
            cout << "ix:"<<position[0] << " iy:"<<position[1] << " iz:"<<position[2]<< endl;
            shared_ptr<Object> objeto = this_->obj_creator->create_object(position);

            objeto->record_object();
            // shared_ptr<Object> objeto1 = make_shared<Object>(position, 100, 50, this_->drw_);
            // objeto1
        }
    }
}