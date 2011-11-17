#include <math.h>
#include "Vector3.h"
#include "Collisions.h"
#include "Objects.h"
#include "Rays.h"

Object::Object()
{
	position = new Vector3();
	color = new Vector3();
}

Object::Object(Vector3* pos)
{
	position = pos;
	color = new Vector3();
}

Object::Object(float x, float y, float z)
{
	position = new Vector3(x,y,z);
	color = new Vector3();
}

Object::Object(Vector3* pos, Vector3* clr)
{
	position = pos;
	color = clr;
}

Object::Object(float px, float py, float pz, float cx, float cy, float cz)
{
	position = new Vector3(px,py,pz);
	color = new Vector3(cx,cy,cz);
}

//virtual Collision* Object::collideWithRay(Ray* ray) = 0;

Sphere::Sphere() : Object() {}

Sphere::Sphere(Vector3* pos) : Object(pos)
{
	radius = 1.0f;
}

Sphere::Sphere(float posX, float posY, float posZ) : Object(posX, posY, posZ)
{
	radius = 1.0f;
}

Sphere::Sphere(Vector3* pos, float r) : Object(pos)
{
	radius = r;
}

Sphere::Sphere(float posX, float posY, float posZ, float r) : Object(posX, posY, posZ)
{
	radius = r;
}

Sphere::Sphere(Vector3* pos, float r, Vector3* clr) : Object(pos, clr)
{
	radius = r;
}

Sphere::Sphere(float posX, float posY, float posZ, float r, float clrX, float clrY, float clrZ) : Object(posX, posY, posZ, clrX, clrY, clrZ)
{
	radius = r;
}

Collision* Sphere::collideWithRay(Ray* ray)
{
	return NULL;
}