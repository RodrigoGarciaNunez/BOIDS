#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>

using std::vector;

class Drawer{
public:
    Drawer();
    void Draw_body(float centerX, float centerY, float radio, int res);

    void update_body_matrix(vector<float> movement, vector<float>prev_position);
    void Erase();

private:
};