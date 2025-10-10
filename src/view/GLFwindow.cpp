#include "GLFwindow.h"

Window::Window(float screenHeight, float screenWidht)
{
    properties.screenHeight=screenHeight;
    properties.screenWidth=screenWidht;
    properties.centerX=screenWidht/2.0f;
    properties.centerY=screenHeight/2.0f;

    window_ = start_GLF();
    
    if (*(window_.get()) == nullptr) exit(EXIT_FAILURE);

    glfwMakeContextCurrent(*(window_.get()));
    gladLoadGL();
    glfwSwapInterval(1);
    
    //glViewport(0, 0, properties.screenWidth, properties.screenHeight); //define el area en la que se va a dibujar
   
    

    // // - Configura la proyección - //
    // glMatrixMode(GL_PROJECTION); //define cómo se mapea el mundo en la pantalla (2d/3d)
    // glLoadIdentity(); //resetea la matriz activa
    // glOrtho(0, properties.screenWidth, 0, properties.screenHeight, -properties.screenHeight,properties.screenHeight); //mapea las coordenadas 
    // //glFrustum(0, properties.screenWidth, 0, properties.screenHeight, 0, properties.screenHeight); //mapea las coordenadas 
    
    // // - regresa a model view -
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    
}

shared_ptr<GLFWwindow *> Window::start_GLF()
{
    if (!glfwInit())
    {
        cerr << "Fallo al inicializar glfw" << endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    shared_ptr<GLFWwindow *> window = make_shared<GLFWwindow *>
        (glfwCreateWindow(properties.screenWidth, properties.screenHeight, "gravity_sim", NULL, NULL));
    
    return window;
}