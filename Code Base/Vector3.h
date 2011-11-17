#ifndef _VECTOR3_H_
#define _VECTOR3_H_

class Vector3
{
public:
	float v[4];

	Vector3();
	Vector3(float nw);
	Vector3(float nx, float ny, float nz);
	Vector3(float nx, float ny, float nz, float nw);
	Vector3(const Vector3* a);

	float magnitude() const;
	Vector3* normal() const;
	
	Vector3* operator+(const Vector3* a) const;
	Vector3* operator-(const Vector3* a) const;
	Vector3* operator*(float s) const;
	float operator*(const Vector3* a) const;
	Vector3* operator*=(float s);
	bool operator==(const Vector3* a);
};

Vector3* crossProduct(Vector3* a, Vector3* b);

#endif