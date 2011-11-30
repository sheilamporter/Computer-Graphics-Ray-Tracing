#include <assert.h>
#include <math.h>
#include <iostream>
#include "Vector3.h"

Vector3::Vector3()
{
	v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 0.0f;
}

Vector3::Vector3(float nw)
{
	v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = nw;
}

Vector3::Vector3(float nx, float ny, float nz)
{
	v[0] = nx; v[1] = ny; v[2] = nz; v[3] = 1.0f;
}

Vector3::Vector3(float nx, float ny, float nz, float nw)
{
	v[0] = nx; v[1] = ny; v[2] = nz; v[3] = nw;
}

Vector3::Vector3(const Vector3& a)
{
	v[0] = a.v[0]; v[1] = a.v[1]; v[2] = a.v[2]; v[3] = 1.0f;
}

void Vector3::set(float x, float y, float z)
{
	v[0] = x; v[1] = y; v[2] = z;
}

float Vector3::magnitude() const
{
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

Vector3 Vector3::normal() const
{
    float oneOverMag = 1.0f / magnitude();

	return Vector3(v[0]*oneOverMag,v[1]*oneOverMag,v[2]*oneOverMag);
}

void Vector3::operator=(const Vector3& a)
{
	v[0] = a.v[0]; v[1] = a.v[1]; v[2] = a.v[2]; v[3] = 1.0f;
}

Vector3 Vector3::operator+(const Vector3& a) const
{
	return Vector3(v[0]+a.v[0],v[1]+a.v[1],v[2]+a.v[2]);
}

Vector3 Vector3::operator-(const Vector3& a) const
{
	return Vector3(v[0]-a.v[0],v[1]-a.v[1],v[2]-a.v[2]);
}

Vector3 Vector3::operator*(float s) const
{
	return Vector3(v[0]*s,v[1]*s,v[2]*s);
}

float Vector3::operator*(const Vector3& a) const
{
	return v[0]*a.v[0] + v[1]*a.v[1] + v[2]*a.v[2];
}

Vector3 Vector3::operator*=(float s)
{
	(*this) = (*this) * s;
	return (*this);
}

bool Vector3::operator==(const Vector3& a)
{
	return (v[0] == a.v[0]) && (v[1] == a.v[1]) && (v[2] == a.v[2]);
}

Vector3 crossProduct(const Vector3 a, const Vector3 b)
{
	Vector3 v;
    v.v[0] = (a.v[1]*b.v[2]) - (a.v[2]*b.v[1]);
    v.v[1] = (a.v[2]*b.v[0]) - (a.v[0]*b.v[2]);
    v.v[2] = (a.v[0]*b.v[1]) - (a.v[1]*b.v[0]);
    
    return v;
}