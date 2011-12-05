#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <algorithm>
#include <iostream>

#include "Vector3.h"
#include "Rays.h"
#include "Objects.h"

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
	Vector3 v(3.0f, 4.0f, 0.0f);
	float mag = v.magnitude();
	assert(approx_equal(mag, 5.0f));

	v = Vector3(-1.0f, 0.0f, 0.0f);
	mag = v.magnitude();
	assert(approx_equal(mag, 1.0f));

	v = Vector3(0.0f, 0.0f, 0.0f);
	mag = v.magnitude();
	assert(approx_equal(mag, 0.0f));
}

void testVector3Add()
{
	Vector3 a(1.0f, 2.0f, 3.0f);
	Vector3 b(2.0f, -1.0f, 4.0f);

	Vector3 result = a + b;
	assert(result == Vector3(3.0f, 1.0f, 7.0f));
}

void testVector3Subtract()
{
	Vector3 a(1.0f, 2.0f, 3.0f);
	Vector3 b(2.0f, -1.0f, 4.0f);

	Vector3 result = a - b;
	assert(result == Vector3(-1.0f, 3.0f, -1.0f));
}

void testVector3Dot()
{
	Vector3 a(1.0f, 2.0f, 3.0f);
	Vector3 b(-1.0f, 4.0f, -2.0f);

	float result = a * b;
	assert(approx_equal(result, 1.0f));
}

void testVector3Scale()
{
	Vector3 a(1.0f, 1.0f, 1.0f);
	float scale = 5.0f;

	a *= scale;
	assert(a == Vector3(5.0f, 5.0f, 5.0f));
}

void testVector3Normal()
{
	Vector3 a(5.0f, 0.0f, 0.0f);
	Vector3 normal = a.normal();

	assert(approx_equal(normal.magnitude(), 1.0f));
	assert(normal == Vector3(1.0f, 0.0f, 0.0f));
}

void testVector3Reflect()
{
	Vector3 vec = Vector3(0.0f, -0.5f, -0.5f).normal();
	Vector3 norm(0.0f, 1.0f, 0.0f);

	Vector3 result = vec.reflect(norm);
	assert(result == Vector3(0.0f, 0.5f, -0.5f).normal());

	vec = Vector3(-0.009f, -0.066f, 0.998f).normal();
	norm = Vector3(-0.130f, -0.985f, -0.109f).normal();

	result = vec.reflect(norm).normal();
}

void testRaySphereCollide()
{
	Sphere sphere(Vector3(0.0f, 2.0f, 2.0f), 1.0f);
	Ray ray(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));

	Collision col = sphere.collideWithRay(ray);
	assert(col.distance < 0.0f);

	sphere = Sphere(Vector3(1.0f, 2.0f, 3.0f), 1.0f);
	ray = Ray(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.9f, 3.1f));

	col = sphere.collideWithRay(ray);

	sphere = Sphere(Vector3(0.0f, 0.0f, 1.0f), 1.0f);
	ray = Ray(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));

	col = sphere.collideWithRay(ray);
	assert(col.distance < 0.0f);

	sphere = Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f);
	ray = Ray(Vector3(-0.5f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
	ray.insideSphere = true;

	col = sphere.collideWithRay(ray);
	//assert(col.distance < 0.0f);
}

void testRayPlaneCollide()
{
	Plane plane(Vector3(0.0f, 0.0f, 5.0f), Vector3(0.0f, 0.0f, -1.0f));
	Ray ray(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
	Collision col = plane.collideWithRay(ray);
	assert(col.distance == 5.0f);

	ray = Ray(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 3.0f, 1.5f).normal());
	col = plane.collideWithRay(ray);
	assert(col.distance > 0.0f);

	ray = Ray(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f).normal());
	col = plane.collideWithRay(ray);
	assert(col.distance < 0.0f);

	ray = Ray(Vector3(0.0f, 0.0f, 10.0f), Vector3(0.0f, 0.0f, -1.0f));
	col = plane.collideWithRay(ray);
	assert(col.distance < 0.0f);
}

void main(int argc, char* argv)
{
	/* Vector3 unit tests */
	testVector3Magnitude();
	testVector3Add();
	testVector3Subtract();
	testVector3Dot();
	testVector3Scale();
	testVector3Normal();
	testVector3Reflect();

	/* Object collision unit tests */
	testRaySphereCollide();
	testRayPlaneCollide();

	cout << "All tests passed." << endl;
	system("pause");
}