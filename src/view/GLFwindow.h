#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <cmath>
#include <vector>

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
    Window(float screenHeight, float screenWidht);
    void draw_frame(float centerX, float centerY, float radio, int re);
    void move_body(vector<float>movement, vector<float> prev_pos);
    unique_ptr<GLFWwindow*> window_;

private:
    unique_ptr<GLFWwindow*>  start_GLF();
    
    struct {
        float screenHeight;
        float screenWidth;
        float centerX= screenWidth;
        float centerY = screenHeight;
    }properties;
};