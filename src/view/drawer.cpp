#include "drawer.h"
#include "../model/object.h"

map<shared_ptr<Object>, bool> Drawer::bodies_to_draw;

static const Vertex vertices[3] = {
    {{-0.6f, -0.4f}, {1.f, 0.f, 0.f}},
    {{0.6f, -0.4f}, {0.f, 1.f, 0.f}},
    {{0.f, 0.6f}, {0.f, 0.f, 1.f}}};

static const char *vertex_shader_text =
    "#version 330\n"
    "uniform mat4 MVP;\n"
    "in vec3 vCol;\n"
    "in vec2 vPos;\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
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
    GLuint auxVAO = createVertexArray(ShaderProgram);
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
GLuint Drawer::createVertexArray(GLuint program)
{

  
    // Crear Vertex Buffer Object (almacena datos en GPU)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), vertices, GL_STATIC_DRAW);

    // Crear Vertex Array Object (describe cómo leer el VBO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    const GLint mvp_location_ = glGetUniformLocation(program, "MVP"); //"MVP" (matriz Model-View-Projection).
    const GLint vpos_location_ = glGetAttribLocation(program, "vPos");
    const GLint vcol_location_ = glGetAttribLocation(program, "vCol");

    mvp_location = mvp_location;
    vpos_location = vpos_location_;
    vcol_location = vcol_location_;
    // Configurar atributo posición
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (void *)offsetof(Vertex, pos));

    // Configurar atributo color
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (void *)offsetof(Vertex, col));

    return VAO; // Devolvemos el VAO para usarlo en el render
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

void Drawer::render()
{
    int width, height;
    glfwGetFramebufferSize(*(window.get()), &width, &height);
    const float ratio = width / (float)height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    mat4x4 m, p, mvp;
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float)glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    glUseProgram(ShaderProgram);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)&mvp);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(*(window.get()));
    glfwPollEvents();
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