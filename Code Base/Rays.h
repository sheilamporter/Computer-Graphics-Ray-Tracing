#ifndef _RAYS_H_
#define _RAYS_H_

#define MAX_RECURSE_DEPTH 5

#include <list>

class Object;
struct Light;
struct Collision;

using namespace std;

public class Ray
{
public:
	Vector3* origin;
	Vector3* direction;
	Vector3* color;

	Ray(Vector3* o, Vector3* d);
	Ray(Vector3* o, Vector3* d, int n);

	Collision* getFirstCollision(list<Object*>* scene);
	Vector3* cast(list<Object*>* scene, list<Light*>* lights);
	Vector3* castFeeler(list<Object*>* scene, Light* light);

private:
	int depth;
};

#endif