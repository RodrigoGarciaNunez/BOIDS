#include "drawer.h"
#include "../model/object.h"

map<shared_ptr<Object>, pair<GLuint, bool>> Drawer::bodies_to_draw;

static const Vertex vertices[18] = {
    // cono
    // Base (dos triángulos)
    {{-0.5f, 0.0f, -0.5f}, {1.f, 0.f, 0.f}},
    {{0.5f, 0.0f, -0.5f}, {0.f, 1.f, 0.f}},
    {{0.5f, 0.0f, 0.5f}, {0.f, 0.f, 1.f}},

    {{0.5f, 0.0f, 0.5f}, {0.f, 0.f, 1.f}},
    {{-0.5f, 0.0f, 0.5f}, {1.f, 1.f, 0.f}},
    {{-0.5f, 0.0f, -0.5f}, {1.f, 0.f, 0.f}},

    // Cara 1
    {{0.0f, 1.0f, 0.0f}, {1.f, 0.f, 0.f}},
    {{-0.5f, 0.0f, -0.5f}, {0.f, 1.f, 0.f}},
    {{0.5f, 0.0f, -0.5f}, {0.f, 0.f, 1.f}},

    // Cara 2
    {{0.0f, 1.0f, 0.0f}, {1.f, 0.f, 0.f}},
    {{0.5f, 0.0f, -0.5f}, {0.f, 1.f, 0.f}},
    {{0.5f, 0.0f, 0.5f}, {0.f, 0.f, 1.f}},

    // Cara 3
    {{0.0f, 1.0f, 0.0f}, {1.f, 0.f, 0.f}},
    {{0.5f, 0.0f, 0.5f}, {0.f, 1.f, 0.f}},
    {{-0.5f, 0.0f, 0.5f}, {0.f, 0.f, 1.f}},

    // Cara 4
    {{0.0f, 1.0f, 0.0f}, {1.f, 0.f, 0.f}},
    {{-0.5f, 0.0f, 0.5f}, {0.f, 1.f, 0.f}},
    {{-0.5f, 0.0f, -0.5f}, {0.f, 0.f, 1.f}},
};

static const char *vertex_shader_text =
    "#version 330\n"
    "uniform mat4 MVP;\n"
    "in vec3 vCol;\n"
    "in vec3 vPos;\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = MVP * vec4(vPos, 1.0);\n"
    "    color = vCol;\n"
    "}\n";

static const char *fragment_shader_text =
    "#version 330\n"
    "in vec3 color;\n"
    "out vec4 fragment;\n"
    "void main()\n"
    "{\n"
    "    fragment = vec4(color, 1.0);\n"
    "}\n";

Drawer::Drawer(shared_ptr<GLFWwindow *> window_)
{
    window = window_;

    ShaderProgram = createShaderProgram();
    //GLuint auxVAO = createVertexArray();

    mat4x4_look_at(view, EYE, CENTER, UP);

    glfwGetFramebufferSize(*(window.get()), &width, &height);
    const float ratio = width / (float)height;
    mat4x4_perspective(projection, 45.0f * (M_PI / 180.0f), ratio, 0.1f, 1000.0f);
    // glEnable(GL_DEPTH_TEST);
}

// Drawer::~Drawer(){}

// manejar shaders (compilarlos y empaquetarlos en un solo programa)
GLuint Drawer::createShaderProgram()
{

    // Crear y compilar vertex shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    // Crear y compilar fragment shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    // Crear el programa y enlazar shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex_shader);
    glAttachShader(shaderProgram, fragment_shader);
    glLinkProgram(shaderProgram);

    // Ya no necesitamos los objetos shader sueltos
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shaderProgram;
}

// sube datos a la GPU y describir cómo usarlos (posiciones y colores).
GLuint Drawer::createVertexArray()
{
    // Crear Vertex Buffer Object (almacena datos en GPU)
    GLuint VAO, VBO;

      // Crear Vertex Array Object (describe cómo leer el VBO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    const GLint mvp_location_ = glGetUniformLocation(ShaderProgram, "MVP"); //"MVP" (matriz Model-View-Projection).
    const GLint vpos_location_ = glGetAttribLocation(ShaderProgram, "vPos");
    const GLint vcol_location_ = glGetAttribLocation(ShaderProgram, "vCol");

    mvp_location = mvp_location_;
    vpos_location = vpos_location_;
    vcol_location = vcol_location_;
    // Configurar atributo posición
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (void *)offsetof(Vertex, pos));

    // Configurar atributo color
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (void *)offsetof(Vertex, col));

 

    return VAO; // Devolvemos el VAO para usarlo en el render
}

void Drawer::register_Vertex_Array(shared_ptr<Object> objecto){
    bodies_to_draw[objecto].first = createVertexArray(); 
}
void Drawer::render()
{
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(ShaderProgram);
    properties_ body_properties;
    array<float, 3> body_position;
    for (auto &object : bodies_to_draw)
    {
        body_properties = object.first->getProperties();
        body_position = body_properties.position;
        int subs = 1;
        //if (object.second.second == true)
        //{
            mat4x4 model, mvp;

            mat4x4_identity(model);
            
            //cin.get();
            //mat4x4_rotate_Z(model, model, (float)glfwGetTime());
            mat4x4_translate(model,0.01*(body_position[0]), 0.01f*(body_position[1]), 0.0f+glfwGetTime());
            mat4x4_mul(mvp, view, model);
            mat4x4_mul(mvp, projection, mvp);
            cout << object.first.get()<<" "<<object.second.first<< endl;
            //glUseProgram(object.second.first);
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)&mvp);
            glBindVertexArray(object.second.first);
            glDrawArrays(GL_TRIANGLES, 0, 18); // 6 caras x 3 vertices = 18
            subs++;        
        //}
    }
    glfwSwapBuffers(*(window.get()));
    glfwPollEvents();
}

vector<float> Drawer::generateCircleVertex(float radius, float resolution)
{
    vector<float> vertices;
    vertices.push_back(0.0f); // centro X
    vertices.push_back(0.0f); // centro Y

    for (int i = 0; i <= resolution; i++)
    {
        float angle = 2.0f * M_PI * i / resolution;
        vertices.push_back(std::cos(angle) * radius);
        vertices.push_back(std::sin(angle) * resolution);
    }

    return vertices;
}

// void Drawer::update_body_matrix(array<float, 3> movement, array<float, 3> prev_position)
// {

//     glPushMatrix(); // agarras la matriz
//     glTranslatef(movement[0], movement[1], 0);
//     Draw_body(32, 32);
//     glPopMatrix();
// }

// void Drawer::Erase()
// {
// }

// void Drawer::update_frame()
// {
//     properties_ body_properties;
//     for (auto &body : bodies_to_draw)
//     {
//         // body.first->u_lock.lock();
//         body_properties = (body.first)->getProperties();
//         if (body.second == true) // si es true, el objeto cambió. Hay que actualizar la matriz
//             update_body_matrix(body_properties.movement, body_properties.position);
//         else
//             Draw_body(32, 32);

//         body.second = false;
//     }
// }