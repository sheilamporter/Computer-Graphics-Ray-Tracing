#include <math.h>
#include "Vector3.h"
#include "Collisions.h"
#include "Objects.h"
#include "Rays.h"

#define PI 3.14159f

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

void Object::setMaterial(const Material& mat)
{
	material = mat;
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
	// Current collision based on: http://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html
	Collision col;

	if(ray.insideSphere)
	{
		Vector3 half = (position - ray.origin).project(ray.direction);
		float rest = pow(radius,2) - (position - (ray.origin + half)).magnitude();
		float full = half.magnitude() + rest;
		col.point = ray.origin + ray.direction * full;
		col.distance = full;
		col.material = material;
		col.normal = col.point - position;
		return col;
	}

	Vector3 originToCenter = position - ray.origin;

	float distance = -1.0f;
	float angle = acos(originToCenter.normal() * ray.direction.normal());
	angle = (angle / PI) * 180.0f;

	if (angle > 90.0f)
	{
		col.distance = -1.0f;
		return col;
	}

	float v = originToCenter * ray.direction;
	float disc = pow(radius, 2) - ((originToCenter * originToCenter) - pow(v, 2));
	if (disc < 0.0f)
	{
		col.distance = -1.0f;
		return col;
	}

	float d = sqrt(disc);
	col.point = ray.origin + (ray.direction * (v - d));
	col.distance = (col.point - ray.origin).magnitude();
	col.material = material;
	col.normal = (col.point - position).normal();

	return col;
}

Plane::Plane(const Vector3& point, const Vector3& norm) : Object(point)
{
	normal = norm;
	width = -1.0f;
	height = -1.0f;
}

Plane::Plane(const Vector3& point, const Vector3& norm, float w, float h) : Object(point)
{
	normal = norm;
	width = w;
	height = h;
}

Collision Plane::collideWithRay(const Ray& ray) const
{
	Collision col;
	float denom = ray.direction * normal;

	if(denom >= 0.0f)
	{
		col.distance = -1.0f;
		return col;
	}

	float numer = (position - ray.origin) * normal;

	col.distance = numer / denom;
	col.point = ray.origin + (ray.direction * col.distance);

	if(width > 0.0f && height > 0.0f)
	{
		if (fabs((col.point - position).v[0]) > width || fabs((col.point - position).v[1]) > height)
		{
			col.distance = -1.0f;
			return col;
		}
	}

	col.material = material;
	col.normal = normal;

	return col;
}