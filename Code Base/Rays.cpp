#include <math.h>
#include <list>
#include "Vector3.h"
#include "Rays.h"
#include "Objects.h"
#include "Collisions.h"

using namespace std;

Ray::Ray(const Vector3& o, const Vector3& d)
{
	origin = o;
	direction = d.normal();
	depth = 0;
	distance = 0.0f;
	color = NULL;
	mediumRefraction = 1.0f;
	insideSphere = false;
}

Ray::Ray(const Vector3& o, const Vector3& d, int n)
{
	origin = o;
	direction = d.normal();
	depth = n;
	distance = 0.0f;
	color = NULL;
	mediumRefraction = 1.0f;
	insideSphere = false;
}

Ray::~Ray()
{
}

bool compare_distance(const Collision& col1, const Collision& col2)
{
	return col1.distance < col2.distance;
}

Collision Ray::getFirstCollision(const list<Object*>& scene)
{
	Collision firstCol;
	list<Collision> collisions;

	// for each object in the scene
	list<Object*>::const_iterator itr = scene.begin();
	for( ; itr != scene.end(); itr++)
	{
		// call the object's collision test with ray
		Collision col = (*itr)->collideWithRay((*this));

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

Vector3 Ray::cast(const list<Object*>& scene, const list<Light>& lights, int depth)
{
	Collision col = getFirstCollision(scene);

	// if there is a collision
	if(col.distance > 0.0f)
	{
		distance = col.distance;
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

		if (depth > 0)
		{
			if (col.material.reflection > 0.0f && !insideSphere)
			{
				float distanceDropOff = 30.0f;
				Vector3 dir = direction.reflect(col.normal).normal();
				Ray reflect(col.point, dir);
				reflect.insideSphere = insideSphere;
				Vector3 reflectColor = reflect.cast(scene, lights, depth-1);
				color += reflectColor * (reflect.distance < distanceDropOff ? 1.0f : 1.0f / (reflect.distance - distanceDropOff))  * col.material.reflection;
			} else {}

			if (col.material.transmission > 0.0f)
			{
				float c1 = (direction * col.normal) * -1.0f;
				//float n = 1.0f / col.material.refractionIndex;
				float n = mediumRefraction / (mediumRefraction == 1.0f ? col.material.refractionIndex : 1.0f);
				float c2 = sqrt( 1 - pow(n,2) * (1 - pow(c1, 2)));
				Vector3 norm = (insideSphere ? col.normal * -1.0f : col.normal);
				Vector3 dir = (direction * n) + (norm * (n * c1 - c2));
				Ray refract(col.point, dir);
				refract.insideSphere = !insideSphere;
				refract.mediumRefraction = col.material.refractionIndex;
				Vector3 refractColor = refract.cast(scene, lights, depth-1);
				color += refractColor * col.material.transmission;
				color *= 0.5f;
			} else {}
		}

		return color;
	}
	
	color.set(0.0f,0.0f,0.0f);
	return color;
}

Vector3 Ray::castPath(const list<Object*>& scene, const list<Light>& lights, int depth)
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

bool Ray::castFeeler(const list<Object*>& scene, const Light& light)
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