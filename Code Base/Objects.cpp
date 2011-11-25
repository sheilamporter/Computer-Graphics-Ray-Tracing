#include <math.h>
#include "Vector3.h"
#include "Collisions.h"
#include "Objects.h"
#include "Rays.h"

Object::Object()
{
	position = new Vector3();
	color = new Vector3(1.0f, 0.0f, 0.0f);
}

Object::Object(Vector3* pos)
{
	position = pos;
	color = new Vector3(1.0f, 0.0f, 0.0f);
}

Object::Object(float x, float y, float z)
{
	position = new Vector3(x,y,z);
	color = new Vector3(1.0f, 0.0f, 0.0f);
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

Object::~Object()
{
	delete position;
	delete color;
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

Sphere::~Sphere()
{
	delete position;
	delete color;
}

Collision* Sphere::collideWithRay(Ray* ray)
{
	Vector3* originToCenter = (*position) - ray->origin;

	float distance = -1.0f;
	float angle = acos((*originToCenter->normal()) * ray->direction->normal());

	if (angle > 90.0f)
		return NULL;

	Vector3* directionNorm = ray->direction->normal();

	float b = ((*originToCenter) * directionNorm) * 2.0f;
	float c = ((*originToCenter) * originToCenter) - pow(radius, 2);
	float a = ((*directionNorm) * directionNorm);

	float divisor = 1.0f / (2.0f * a);
	float discriminate = pow(b, 2) - 4.0f*a*c;

	if (discriminate <= 0.0f)
		return NULL;

	float b4ac = sqrt(discriminate);
	float l1 = (b - b4ac) * divisor;
	float l2 = (b + b4ac) * divisor;

	if (l1 < l2) distance = l1;
	else distance = l2;

	Collision* col = new Collision;
	col->distance = distance;
	col->point = (*ray->origin) + (*directionNorm * distance);
	col->normal = (*col->point) - position;
	col->color = color;

	return col;
}