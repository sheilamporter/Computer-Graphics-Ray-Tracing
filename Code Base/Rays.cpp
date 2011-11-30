#include <math.h>
#include <list>
#include "Vector3.h"
#include "Rays.h"
#include "Objects.h"
#include "Collisions.h"

using namespace std;

#define IMPLEMENTATION 2

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

	Collision* col = new Collision;
	col->point = new Vector3((*collisions->begin())->point);
	col->normal = new Vector3((*collisions->begin())->normal);
	col->color = new Vector3((*collisions->begin())->color);
	col->distance = (*collisions->begin())->distance;

	list<Collision*>::iterator colItr = collisions->begin();
	for( ; colItr != collisions->end(); colItr++)
	{
		delete (*colItr);
	}
	delete collisions;

	return col;
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
		if(IMPLEMENTATION == 2)
		{
			// take the color of the collision
			color = new Vector3(col->color);

			// for each light, case a feeler ray to see if there should be shadow
			list<Light*>::iterator itr = lights->begin();
			for( ; itr != lights->end(); itr++)
			{
				// compute the normal to the light
				Vector3* toLight = ((*(*itr)->position) - col->point)->normal();
				Ray* feeler = new Ray(col->point, toLight);
				bool feelerHit = feeler->castFeeler(scene, (*itr));
				delete feeler;
				if(feelerHit) 
				{
					color->set(0.05f, 0.05f, 0.05f);
				}
				else
				{
					float intensity = (*toLight) * col->normal;
					color = (*color) + ((*(*itr)->color) * intensity);

				}
				delete toLight;
			}

			delete col;
			return;
		}

		// third implementation: spawn feeler rays for shadows, and also reflective rays

		// fourth implementation: spanw feeler rays, reflective rays, refractive rays
	}

	color = new Vector3(0.0f, 0.0f, 0.0f);
}

bool Ray::castFeeler(list<Object*>* scene, Light* light)
{
	Collision* col = getFirstCollision(scene);
	bool hit = false;
	
	// if col is NULL or if the distance is greater than the distance to the light, return the light color
	if(!col)
	{
		delete col;
		return hit;
	}

	Vector3* diff = (*light->position) - origin;
	float distToLight = diff->magnitude();
	delete diff;

	if(distToLight > col->distance)
	{
		hit = true;
	}
	
	delete col;
	return hit;
}