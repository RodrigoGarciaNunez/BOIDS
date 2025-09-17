#include "drawer.h"
#include "../model/object.h"

map<shared_ptr<Object>, bool> Drawer::bodies_to_draw;

Drawer::Drawer()
{
    
}

// Drawer::~Drawer(){}

void Drawer::Draw_body(float centerX, float centerY, float radio, int res)
{
    glColor3f(1.0f, 0.0f, 0.0f);  // rojo
    glBegin(GL_TRIANGLE_FAN);     // indica al gpu cómo y qué hacer con los vertices que colocamos
    glVertex2d(centerX, centerY); // primer vertice

    for (int i = 0; i <= res; i++)
    {
        float angle = 2.0f * M_PI * (static_cast<float>(i) / res);
        float x = centerX + cos(angle) * radio;
        float y = centerY + sin(angle) * radio;
        glVertex2d(x, y);
    }
    glEnd();
}

void Drawer::update_body_matrix(pair<float, float> movement, pair<float, float> prev_position)
{
    if (movement.first != 0 && movement.second != 0)
    {
        glPushMatrix(); // agarras la matriz
        glTranslatef(movement.first, movement.second, 0);
        Draw_body(prev_position.first, prev_position.second, 50.0f, 50);
        glPopMatrix();
    }
}

void Drawer::Erase()
{}

void Drawer::update_frame()
{
    properties_ body_properties;
    for (auto &body : bodies_to_draw)
    {
        //body.first->u_lock.lock();
        body_properties= (body.first)->getProperties(); 
        if (body.second == true) //si es true, el objeto cambió. Hay que actualizar la matriz   
            update_body_matrix(body_properties.movement,body_properties.position);
        else 
            Draw_body(body_properties.position.first, body_properties.position.second, 
                body_properties.radio, 50);
        
        body.second= false;
    }
}