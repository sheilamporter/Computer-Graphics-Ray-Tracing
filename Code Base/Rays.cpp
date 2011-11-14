#include <math.h>
#include "Vector3.h"

class Ray
{
public:
	Vector3* origin;
	Vector3* direction;
	Vector3* color;

	void cast();
};