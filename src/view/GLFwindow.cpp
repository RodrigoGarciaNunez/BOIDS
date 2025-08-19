#include "GLFwindow.h"

Window::Window(float screenHeight, float screenWidht)
{
    properties.screenHeight=screenHeight;
    properties.screenWidth=screenWidht;
    properties.centerX=screenWidht/2.0f;
    properties.centerY=screenHeight/2.0f;

    window_ = start_GLF();
    glfwMakeContextCurrent(*(window_.get()));
    glViewport(0, 0, properties.screenWidth, properties.screenHeight); //define el area en la que se va a dibujar
    
    // - Configura la proyección - //
    glMatrixMode(GL_PROJECTION); //define cómo se mapea el mundo en la pantalla (2d/3d)
    glLoadIdentity(); //resetea la matriz activa
    glOrtho(0, properties.screenWidth, 0, properties.screenHeight, -1, 1); //mapea las coordenadas 
    
    // - regresa a model view -
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

unique_ptr<GLFWwindow *> Window::start_GLF()
{
    if (!glfwInit())
    {
        cerr << "Fallo al inicializar glfw" << endl;
        return nullptr;
    }

    unique_ptr<GLFWwindow *> window = make_unique<GLFWwindow *>
        (glfwCreateWindow(properties.screenWidth, properties.screenHeight, "gravity_sim", NULL, NULL));
    
    return window;
}

void Window::draw_body(float centerX, float centerY, float radio, int res)
{

    // glLoadIdentity(); //resetea la matriz activa

    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity(); //se resetea la matriz (para asegurar que no trabajamos con transformadas anteriores)

    glColor3f(1.0f, 0.0f, 0.0f); // rojo
    glBegin(GL_TRIANGLE_FAN); //indica al gpu cómo y qué hacer con los vertices que colocamos
    glVertex2d(centerX, centerY); //primer vertice
    
    for (int i = 0; i <= res; i++)
    {
        float angle = 2.0f * M_PI * (static_cast<float>(i) / res);
        float x = centerX + cos(angle) * radio;
        float y = centerY + sin(angle) * radio;
        glVertex2d(x, y);
    }
    glEnd();
}


void Window::move_body(vector<float> movement, vector<float> prev_pos){
    glPushMatrix(); //agarras la matriz
    glTranslatef(movement[0], movement[1], 0);
    draw_body(prev_pos[0], prev_pos[1], 50.0f, 50);
    glPopMatrix();
}