#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>

#include "Vector3.h"
#include "Collisions.h"
#include "Rays.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

class Ray;

struct Light
{
	Vector3 position;
	Vector3 color;
};

class Object
{
public:
    Vector3 position;
    Vector3 color;
        
    Object() : position(), color() {}
	Object(Vector3 pos) : position(pos), color() {} 
    Object(float x, float y, float z) : position(x, y, z), color() {}
	Object(Vector3 pos, Vector3 clr) : position(pos), color(clr) {}
	Object(float px, float py, float pz, float cx, float cy, float cz) : position(px,py,pz), color(cx,cy,cz) {}

	virtual Collision* collideWithRay(Ray* ray); // override this for per-object-type collision with ray
};

class Sphere: public Object
{
public:
    float radius;
        
    Sphere() : Object(), radius(1.0f) {}
    Sphere(Vector3 pos) : Object(pos), radius(1.0f) {}
    Sphere(float posX, float posY, float posZ) : Object(posX, posY, posZ), radius(1.0f) {}
    Sphere(Vector3 pos, float r) : Object(pos), radius(r) {}
    Sphere(float posX, float posY, float posZ, float r) : Object(posX, posY, posZ), radius(r) {}
    Sphere(Vector3 pos, float r, Vector3 clr) : Object(pos, clr), radius(r) {}
    Sphere(float posX, float posY, float posZ, float r, float clrX, float clrY, float clrZ) : Object(posX, posY, posZ, clrX, clrY, clrZ), radius(r) {}
        
    //TODO: function to test for collisions - takes a ray, returns a Collision
        
};

#endif