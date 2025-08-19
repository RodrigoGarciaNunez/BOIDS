#ifndef OBJETO_H
#define OBJETO_H

#include <vector>

using namespace std;

class Object{
public:
    Object(vector<float> position, float mass);
    virtual ~Object();
    void movement2d(vector<float> movement);
    
    struct{
        vector<float> position;
        float mass;
    }properties_;
    

private:
    
    

};

#endif