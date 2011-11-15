#ifndef _COLLISIONS_H_
#define _COLLISIONS_H_

#include "Vector3.h"

struct Collision {
	Vector3 point;
	Vector3 normal;
	Vector3 color;
	float distance;
};

#endif