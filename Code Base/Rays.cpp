#include <math.h>
#include "Vector3.h"
#include "Rays.h"

#define IMPLEMENTATION 1

Ray::Ray(Vector3* o, Vector3* d)
{
	origin = o;
	direction = d;
	depth = 0;
}

Ray::Ray(Vector3* o, Vector3*d, int n)
{
	origin = o;
	direction = d;
	depth = n;
}

Collision* Ray::getFirstCollision(list<Object*> scene)
{
	list<Collision*> collisions;

	// for each object in the scene
	// call the object's collision test with ray
	// if the object collides, add the collision to the list

	// if the list is empty, return NULL
	return NULL;

	// sort the list by increasing distance, return the first element
}

Vector3* Ray::cast(list<Object*> scene, list<Light*> lights)
{
	Collision *col = getFirstCollision(scene);

	// if there is a collision
	// first implementation: return the color immediately

	// second implementation: spawn feeler rays for shadows, combine returned colors

	// third implementation: spawn feeler rays for shadows, and also reflective rays

	// fourth implementation: spanw feeler rays, reflective rays, refractive rays

	return NULL;
}

Vector3* Ray::castFeeler(list<Object*> scene, Light* light)
{
	Collision* col = getFirstCollision(scene);
	
	// if col is NULL or if the distance is greater than the distance to the light, return the light color
	
	return new Vector3(0.0f, 0.0f, 0.0f);
}