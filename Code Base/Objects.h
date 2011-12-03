#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>

#include "Vector3.h"
#include "Collisions.h"
#include "Rays.h"

using namespace std;

class Vector3;
struct Collision;
struct Material;
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
	Material material;
        
    Object();
	Object(const Vector3& pos);
    Object(float x, float y, float z);
	Object(const Vector3& pos, const Vector3& clr);
	Object(float px, float py, float pz, float cx, float cy, float cz);
	~Object();

	void setMaterial(const Material& mat);

	Collision collideWithRay(const Ray& ray) const; // override this for per-object-type collision with ray
};

class Sphere: public Object
{
public:
    float radius;
        
    Sphere();
    Sphere(const Vector3& pos);
    Sphere(float posX, float posY, float posZ);
    Sphere(const Vector3& pos, float r);
    Sphere(float posX, float posY, float posZ, float r);
    Sphere(const Vector3& pos, float r, const Vector3& clr);
    Sphere(float posX, float posY, float posZ, float r, float clrX, float clrY, float clrZ);
	~Sphere();
    
	Collision collideWithRay(const Ray& ray) const;
        
};

#endif