#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <Vector3.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

class Object
{
    public:
        Vector3 position;
        Vector3 color;
        
        Object() : position() {}
        Object(Vector3 pos) : position(pos.v[0], pos.v[1], pos.v[2]) {}        
        Object (float x, float y, float z) : position(x, y, z) {}
}

class Sphere: public Object
{
    public:
        float radius;
        
        Sphere() : position(), radius(1f), color() {}
        Sphere(Vector3 pos) : position(pos), radius(1f), color() {}
        Sphere(float posX, float posY, float posZ) : position(posX, posY, posZ), radius(1f), color() {}
        Sphere(Vector3 pos, float r) : position(pos.v[0], pos.v[1], pos.v[2]), radius(f), color() {}
        Sphere(float posX, float posY, float posZ, float r) : position(posX, posY, posZ), radius(r), color() {}
        Sphere(Vector3 pos, float r, Vector3 clr) : position(pos.v[0], pos.v[1], pos.v[2]), radius(f), color(clr.v[0], clr.v[1], clr.v[2]) {}
        Sphere(float posX, float posY, float posZ, float r, float clrX, float clrY, float clrZ) : position(posX, posY, posZ), radius(r), color(clrX, clrY, clrZ) {}
        
        //TODO: function to test for collisions - takes a ray, returns a Collision
        
}