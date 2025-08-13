#ifndef OBJETO_H
#define OBJETO_H

#include <vector>

using namespace std;

class Object{
public:
    Object(vector<float> position, float mass);
    virtual ~Object();

private:
    float mass;
    vector<float> position;

};

#endif