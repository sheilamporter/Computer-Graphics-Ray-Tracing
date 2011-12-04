#ifndef _RAYS_H_
#define _RAYS_H_

#define MAX_RECURSE_DEPTH 5

#include <list>

#include "Objects.h"
#include "Collisions.h"

class Object;
class Sphere;
struct Light;
struct Collision;

using namespace std;

class Ray
{
public:
	Vector3 origin;
	Vector3 direction;
	Vector3 color;

	Ray(const Vector3& o, const Vector3& d);
	Ray(const Vector3& o, const Vector3& d, int n);
	~Ray();

	Collision getFirstCollision(const list<Sphere>& scene);
	Vector3 cast(const list<Sphere>& scene, const list<Light>& lights, int depth);
	Vector3 castPath(const list<Sphere>& scene, const list<Light>& lights, int depth);
	bool castFeeler(const list<Sphere>& scene, const Light& light);

private:
	int depth;
};

#endif