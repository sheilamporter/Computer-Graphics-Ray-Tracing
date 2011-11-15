#include <cstdlib>
#include <iostream>
#include <cmath>
#include <object.h>
#include <Vector3.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


class Camera
{
    public:
        Vector3 position;
        Vector3 normal;
        
        Camera() : position(), normal(0f, 1f, 0) {}
        Camera(Vector3 pos, Vector3 norm) : position(pos.v[0], pos.v[1], pos.v[2]), normal(norm.v[0], norm.v[1], norm.v[2]) {}
        Camera(float posX, float posY, float posZ, float normX, float normY, float normZ) : position(posx, posY, posZ), normal(normX, normY, normZ) {}
    
}