#include <math.h>
#include <list>
#include "Vector3.h"
#include "Rays.h"
#include "Objects.h"
#include "Collisions.h"

using namespace std;

#define IMPLEMENTATION 3

Ray::Ray(const Vector3& o, const Vector3& d)
{
	origin = o;
	direction = d.normal();
	depth = 0;
	color = NULL;
}

Ray::Ray(const Vector3& o, const Vector3& d, int n)
{
	origin = o;
	direction = d.normal();
	depth = n;
	color = NULL;
}

Ray::~Ray()
{
}

bool compare_distance(const Collision& col1, const Collision& col2)
{
	return col1.distance < col2.distance;
}

Collision Ray::getFirstCollision(const list<Sphere>& scene)
{
	Collision firstCol;
	list<Collision> collisions;

	// for each object in the scene
	list<Sphere>::const_iterator itr = scene.begin();
	for( ; itr != scene.end(); itr++)
	{
		// call the object's collision test with ray
		Collision col = (*itr).collideWithRay((*this));

		// if the object collides, add the collision to the list
		if(col.distance > -1.0f)
			collisions.push_back(col);
	}

	// if the list is empty, return NULL
	if (collisions.size() == 0)
	{
		firstCol.distance = -1.0f;
		return firstCol;
	}

	// sort the list by increasing distance, return the first element
	collisions.sort(compare_distance);

	return *(collisions.begin());
}

Vector3 Ray::cast(const list<Sphere>& scene, const list<Light>& lights, int depth)
{
	Collision col = getFirstCollision(scene);

	// if there is a collision
	if(col.distance > 0.0f)
	{
		// first implementation: return the color immediately
		if(IMPLEMENTATION == 1)
		{
			color = col.color;
			return color;
		}

		// second implementation: spawn feeler rays for shadows, combine returned colors
		if(IMPLEMENTATION > 1)
		{
			// for each light, case a feeler ray to see if there should be shadow
			list<Light>::const_iterator itr = lights.begin();
			for( ; itr != lights.end(); itr++)
			{
				// compute the normal to the light
				Vector3 toLight = ((*itr).position - col.point).normal();
				Ray feeler(col.point, toLight);
				bool feelerHit = feeler.castFeeler(scene, (*itr));
				
				// Ambient component of lighting.
				color += col.material.ambient.scale((*itr).color);
				// If there's an obstruction, the only affect of this light is it's ambient.
				if(feelerHit) 
				{
					continue;
				}
				else
				{
					// The following is an appoximation of Phong's lighting model.
					// Compute the angles between the light direction and: the view; the normal.
					float normAngle = toLight * col.normal;
					//float specAngle = (toLight*-1.0f).reflect(col.normal) * direction;
					float specAngle = ((toLight + (direction * -1.0f)) * 0.5f).normal() * col.normal;

					// Diffuse component of lighting.
					color += col.material.diffuse.scale((*itr).color) * normAngle;

					// Specular component of lighting.
					if(specAngle > 0.0f)
						color += col.material.specular.scale((*itr).color) * pow(specAngle, col.material.shininess);
				}
			}

			// third implementation: spawn feeler rays for shadows, and also reflective rays
			if(IMPLEMENTATION > 2)
			{
				if (depth > 0)
				{
					Vector3 dir = direction.reflect(col.normal).normal();
					Ray reflect(col.point, dir);
					color +=  reflect.cast(scene, lights, depth-1) * col.material.reflection;
				}
			}

			return color;
		}

		// fourth implementation: spawn feeler rays, reflective rays, refractive rays
	}
	
	color.set(0.0f,0.0f,0.0f);
	return color;
}

Vector3 Ray::castPath(const list<Sphere>& scene, const list<Light>& lights, int depth)
{
	Collision col = getFirstCollision(scene);

	if (col.distance > 0.0f)
	{
		//
		if (depth > 0)
		{
			//color *= reflected ray (recursion)
			color.scale(castPath(scene, lights, depth-1));
		}
		color += col.material.emittance;
		return color;
	}

	color.set(0.0f,0.0f,0.0f);
	return color;

}

bool Ray::castFeeler(const list<Sphere>& scene, const Light& light)
{
	Collision col = getFirstCollision(scene);
	bool hit = false;
	
	// if col is NULL or if the distance is greater than the distance to the light, return the light color
	if(col.distance <= -1.0f)
	{
		return hit;
	}

	Vector3 diff = light.position - origin;
	float distToLight = diff.magnitude();

	if(distToLight > col.distance)
	{
		hit = true;
	}
	
	return hit;
}