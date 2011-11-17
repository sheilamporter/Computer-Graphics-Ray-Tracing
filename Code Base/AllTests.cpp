#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <algorithm>
#include <iostream>

#include "Vector3.h"

using namespace std;

bool approx_equal(double x, double y)
{  
   const double EPSILON = 1E-14;
   if (x == 0) return fabs(y) <= EPSILON;
   if (y == 0) return fabs(x) <= EPSILON;
   return fabs(x - y) / max(fabs(x), fabs(y)) <= EPSILON;
}

void testVector3Magnitude()
{
	Vector3* v = new Vector3(3.0f, 4.0f, 0.0f);
	float mag = v->magnitude();
	assert(approx_equal(mag, 5.0f));

	v = new Vector3(-1.0f, 0.0f, 0.0f);
	mag = v->magnitude();
	assert(approx_equal(mag, 1.0f));

	v = new Vector3(0.0f, 0.0f, 0.0f);
	mag = v->magnitude();
	assert(approx_equal(mag, 0.0f));
}

void testVector3Add()
{
	Vector3* a = new Vector3(1.0f, 2.0f, 3.0f);
	Vector3* b = new Vector3(2.0f, -1.0f, 4.0f);

	Vector3* result = (*a) + b;
	assert((*result) == new Vector3(3.0f, 1.0f, 7.0f));
}

void testVector3Subtract()
{
	Vector3* a = new Vector3(1.0f, 2.0f, 3.0f);
	Vector3* b = new Vector3(2.0f, -1.0f, 4.0f);

	Vector3* result = (*a) - b;
	assert(*result == new Vector3(-1.0f, 3.0f, -1.0f));
}

void testVector3Dot()
{
	Vector3* a = new Vector3(1.0f, 2.0f, 3.0f);
	Vector3* b = new Vector3(-1.0f, 4.0f, -2.0f);

	float result = (*a) * b;
	assert(approx_equal(result, 1.0f));
}

void testVector3Scale()
{
	Vector3* a = new Vector3(1.0f, 1.0f, 1.0f);
	float scale = 5.0f;

	(*a) *= scale;
	assert(*a == new Vector3(5.0f, 5.0f, 5.0f));
}

void testVector3Normal()
{
	Vector3* a = new Vector3(5.0f, 0.0f, 0.0f);
	Vector3* normal = a->normal();

	assert(approx_equal(normal->magnitude(), 1.0f));
	assert(*normal == new Vector3(1.0f, 0.0f, 0.0f));
}

void main(int argc, char* argv)
{
	testVector3Magnitude();
	testVector3Add();
	testVector3Subtract();
	testVector3Dot();
	testVector3Scale();
	testVector3Normal();

	cout << "All tests passed." << endl;
	system("pause");
}