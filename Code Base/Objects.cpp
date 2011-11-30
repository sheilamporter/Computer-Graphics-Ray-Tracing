#include <math.h>
#include "Vector3.h"
#include "Collisions.h"
#include "Objects.h"
#include "Rays.h"

#define PI 3.14159

Object::Object()
{
	color.set(1.0f,0.0f,0.0f);
}

Object::Object(const Vector3& pos)
{
	position = pos;
	color.set(1.0f,0.0f,0.0f);
}

Object::Object(float x, float y, float z)
{
	position.set(x,y,z);
	color.set(1.0f,0.0f,0.0f);
}

Object::Object(const Vector3& pos, const Vector3& clr)
{
	position = pos;
	color = clr;
}

Object::Object(float px, float py, float pz, float cx, float cy, float cz)
{
	position.set(px,py,pz);
	color.set(cx,cy,cz);
}

Object::~Object()
{
}

Collision Object::collideWithRay(const Ray& ray) const
{
	Collision col;
	return col;
}

Sphere::Sphere() : Object() {}

Sphere::Sphere(const Vector3& pos) : Object(pos)
{
	radius = 1.0f;
}

Sphere::Sphere(float posX, float posY, float posZ) : Object(posX, posY, posZ)
{
	radius = 1.0f;
}

Sphere::Sphere(const Vector3& pos, float r) : Object(pos)
{
	radius = r;
}

Sphere::Sphere(float posX, float posY, float posZ, float r) : Object(posX, posY, posZ)
{
	radius = r;
}

Sphere::Sphere(const Vector3& pos, float r, const Vector3& clr) : Object(pos, clr)
{
	radius = r;
}

Sphere::Sphere(float posX, float posY, float posZ, float r, float clrX, float clrY, float clrZ) : Object(posX, posY, posZ, clrX, clrY, clrZ)
{
	radius = r;
}

Sphere::~Sphere()
{
}

Collision Sphere::collideWithRay(const Ray& ray) const
{
	Collision col;
	Vector3 originToCenter = position - ray.origin;

	float distance = -1.0f;
	float angle = acos(originToCenter.normal() * ray.direction.normal());
	angle = (angle / PI) * 180.0f;

	if (angle > 90.0f)
	{
		col.distance = -1.0f;
		return col;
	}

	Vector3 directionNorm = ray.direction.normal();

	float b = (originToCenter * directionNorm) * 2.0f;
	float c = (originToCenter * originToCenter) - pow(radius, 2);
	float a = (directionNorm * directionNorm);

	float divisor = 1.0f / (2.0f * a);
	float discriminate = pow(b, 2) - 4.0f*a*c;

	if (discriminate <= 0.0f)
	{
		col.distance = -1.0f;
		return col;
	}

	float b4ac = sqrt(discriminate);
	float l1 = (b - b4ac) * divisor;
	float l2 = (b + b4ac) * divisor;

	if (l1 < l2) distance = l1;
	else distance = l2;

	col.distance = distance;
	col.point = ray.origin + (directionNorm * distance);
	col.normal = col.point - position;
	col.color = color;

	return col;
}