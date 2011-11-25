#include <math.h>
#include <list>
#include "Vector3.h"
#include "Rays.h"
#include "Objects.h"
#include "Collisions.h"

using namespace std;

#define IMPLEMENTATION 1

Ray::Ray(Vector3* o, Vector3* d)
{
	origin = o;
	direction = d->normal();
	depth = 0;
	color = NULL;
}

Ray::Ray(Vector3* o, Vector3*d, int n)
{
	origin = o;
	direction = d;
	depth = n;
	color = NULL;
}

Ray::~Ray()
{
	delete origin;
	delete direction;
	delete color;
}

bool compare_distance(Collision* col1, Collision* col2)
{
	return col1->distance < col2->distance;
}

Collision* Ray::getFirstCollision(list<Object*>* scene)
{
	list<Collision*>* collisions = new list<Collision*>();

	// for each object in the scene
	list<Object*>::iterator itr = scene->begin();
	for( ; itr != scene->end(); itr++)
	{
		// call the object's collision test with ray
		Collision* col = (*itr)->collideWithRay(this);

		// if the object collides, add the collision to the list
		if(col)
			collisions->push_back(col);
	}

	// if the list is empty, return NULL
	if (collisions->size() == 0)
		return NULL;

	// sort the list by increasing distance, return the first element
	collisions->sort(compare_distance);
	return *(collisions->begin());
}

void Ray::cast(list<Object*>* scene, list<Light*>* lights)
{
	Collision *col = getFirstCollision(scene);

	// if there is a collision
	if(col)
	{
		// first implementation: return the color immediately
		if(IMPLEMENTATION == 1)
		{
			color = new Vector3(col->color);
			delete col;
			return;
		}

		// second implementation: spawn feeler rays for shadows, combine returned colors

		// third implementation: spawn feeler rays for shadows, and also reflective rays

		// fourth implementation: spanw feeler rays, reflective rays, refractive rays
	}

	color = new Vector3(0.0f, 0.0f, 0.0f);
}

Vector3* Ray::castFeeler(list<Object*>* scene, Light* light)
{
	Collision* col = getFirstCollision(scene);
	
	// if col is NULL or if the distance is greater than the distance to the light, return the light color
	
	return new Vector3(0.0f, 0.0f, 0.0f);
}