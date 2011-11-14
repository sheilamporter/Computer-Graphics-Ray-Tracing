#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Vector3.h"

struct Collision {
	Vector3 point;
	Vector3 normal;
	Vector3 color;
	float distance;
};