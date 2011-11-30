#ifndef _RAYS_H_
#define _RAYS_H_

#define MAX_RECURSE_DEPTH 5

#include <list>

class Object;
struct Light;
struct Collision;

using namespace std;

class Ray
{
public:
	Vector3* origin;
	Vector3* direction;
	Vector3* color;

	Ray(Vector3* o, Vector3* d);
	Ray(Vector3* o, Vector3* d, int n);
	~Ray();

	Collision* getFirstCollision(list<Object*>* scene);
	void cast(list<Object*>* scene, list<Light*>* lights);
	bool castFeeler(list<Object*>* scene, Light* light);

private:
	int depth;
};

#endif