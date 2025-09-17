#pragma once


#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <map>
#include <memory>
#include <utility>

using std::vector;
using std::map;
using std::shared_ptr;
using std::pair;

struct Object; //fordward declaration

class Drawer{
public:
    Drawer();
    void Draw_body(float centerX, float centerY, float radio, int res);
    void update_frame();

    void update_body_matrix(pair<float, float> movement, pair<float, float>prev_position);
    void Erase();

    static map<shared_ptr<Object>, bool> bodies_to_draw; //este funciona para saber si el cuerpo se debe actualizar o sólo se imprime como está para el siguiente frame

private:
     
};

//#endif