#ifndef _COLLISIONS_H_
#define _COLLISIONS_H_

class Vector3;

struct Collision {
	Vector3* point;
	Vector3* normal;
	Vector3* color;
	float distance;
};

#endif