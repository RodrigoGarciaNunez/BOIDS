//#ifndef OBJETO_H
//#define OBJETO_H

#include <vector>
#include "../view/drawer.h"
#include <memory>

using namespace std;
using std::make_unique;
using std::unique_ptr;

class Object{
public:
    Object(vector<float> position, float mass, float radio);
    virtual ~Object();
    void movement2d(vector<float> movement);

private:
    unique_ptr<Drawer> drawer;
    
    struct{
        vector<float> position;
        float mass;
        float radio;
    }properties_;

};

//#endif