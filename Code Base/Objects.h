#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

class Vector3;
struct Collision;
class Ray;

struct Light
{
	Vector3* position;
	Vector3* color;
};

class Object
{
public:
    Vector3* position;
    Vector3* color;
        
    Object();
	Object(Vector3* pos);
    Object(float x, float y, float z);
	Object(Vector3* pos, Vector3* clr);
	Object(float px, float py, float pz, float cx, float cy, float cz);
	~Object();

	virtual Collision* collideWithRay(Ray* ray) = 0; // override this for per-object-type collision with ray
};

class Sphere: public Object
{
public:
    float radius;
        
    Sphere();
    Sphere(Vector3* pos);
    Sphere(float posX, float posY, float posZ);
    Sphere(Vector3* pos, float r);
    Sphere(float posX, float posY, float posZ, float r);
    Sphere(Vector3* pos, float r, Vector3* clr);
    Sphere(float posX, float posY, float posZ, float r, float clrX, float clrY, float clrZ);
	~Sphere();
    
	Collision* collideWithRay(Ray* ray);
        
};

#endif