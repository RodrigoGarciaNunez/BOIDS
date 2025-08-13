#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <cmath>


using namespace std;
using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;
using std::cerr;
using std::cout;
using std::endl;

class Window{
public:
    Window();
    void draw_body(float centerX, float centerY, float radio, int re);
    unique_ptr<GLFWwindow*> window_;

private:
    unique_ptr<GLFWwindow*>  start_GLF();
    struct GLFWwindowDeleter;
};