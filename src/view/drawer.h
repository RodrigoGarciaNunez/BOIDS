#pragma once



#define GLAD_GL_IMPLEMENTATION
#include "../../include/glad/glad.h"
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <cmath>

#include "../../include/linmath.h/linmath.h"

using std::vector;
using std::map;
using std::shared_ptr;
using std::pair;
using std::array;




struct Object; //fordward declaration

using Vertex = struct Vertex{
    vec3 pos; //atributo de posicíon
    vec3 col; //atributo de color
};



class Drawer{
public:
    Drawer(shared_ptr<GLFWwindow *> window_);
    GLuint createVertexArray(GLuint program);
    vector<float> generateCircleVertex(float radius, float resolution);
    void render();

    void update_frame();

    void update_body_matrix(array<float, 3> movement, array<float, 3>prev_position);

    static map<shared_ptr<Object>, bool> bodies_to_draw; //este funciona para saber si el cuerpo se debe actualizar o sólo se imprime como está para el siguiente frame
    const float PI = 3.14159265359f;

private:

// Vertex shader (GLSL)
    const char* vertexShaderSource;

    // Fragment shader (GLSL)
    const char* fragmentShaderSource;
    GLuint shaderProgram;

    GLuint createShaderProgram(); 
    
    shared_ptr<GLFWwindow *> window;

    GLint mvp_location; //"MVP" (matriz Model-View-Projection).
    GLint vpos_location;
    GLint vcol_location;
    GLuint VBO, VAO;
    GLuint ShaderProgram;
    

    //camera
    mat4x4 view;
    const vec3 EYE =  { 0.0f, 6.0f, 3.0f };
    const vec3 CENTER =  { 0.0f, 0.0f, 0.0f };
    const vec3 UP = { 0.0f, 1.0f, 0.0f }; 

    // perspectiva
    mat4x4 projection;

    //pantalla
    int height, width;

    
};

//#endif