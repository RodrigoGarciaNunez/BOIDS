#include "drawer.h"

Drawer::Drawer(){
    
}

//Drawer::~Drawer(){}

void Drawer::Draw_body(float centerX, float centerY, float radio, int res){
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

void Drawer::update_body_matrix(vector<float> movement, vector<float>prev_position){
    glPushMatrix(); //agarras la matriz
    glTranslatef(movement[0], movement[1], 0);
    Draw_body(prev_position[0], prev_position[1], 50.0f, 50);
    glPopMatrix();
}


void Drawer::Erase(){

}