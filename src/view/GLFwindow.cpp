#include "GLFwindow.h"

Window::Window()
{
    window_ = start_GLF();
}

unique_ptr<GLFWwindow *> Window::start_GLF()
{
    if (!glfwInit())
    {
        cerr << "Fallo al inicializar glfw" << endl;
        return nullptr;
    }

    unique_ptr<GLFWwindow *> window = make_unique<GLFWwindow *>(glfwCreateWindow(800, 600, "gravity_sim", NULL, NULL));
    return window;
}

void Window::draw_body(float centerX, float centerY, float radio, int res)
{
    glfwMakeContextCurrent(*(window_.get()));

    int width = 800, height = 600;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // coordenadas 2D
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glColor3f(1.0f, 0.0f, 0.0f); // rojo
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(centerX, centerY);
    
    for (int i = 0; i <= res; i++)
    {
        float angle = 2.0f * M_PI * (static_cast<float>(i) / res);
        float x = centerX + cos(angle) * radio;
        float y = centerY + sin(angle) * radio;
        glVertex2d(x, y);
    }
    glEnd();
}

struct Window::GLFWwindowDeleter
{
    void operator()(GLFWwindow *window) const noexcept
    {
        if (window)
        {
            glfwDestroyWindow(window);
        }
    }
};
