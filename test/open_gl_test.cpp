//#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) {
        std::cerr << "Error: No se pudo inicializar GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Version", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error: No se pudo crear ventana\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // // Inicializar GLEW
    // if (glewInit() != GLEW_OK) {
    //     std::cerr << "Error: No se pudo inicializar GLEW\n";
    //     return -1;
    // }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}