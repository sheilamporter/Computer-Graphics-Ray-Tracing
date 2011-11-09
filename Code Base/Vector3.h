class Vector3
{
public:
	float v[4];

	Vector3();
	Vector3(float nw);
	Vector3(float nx, float ny, float nz);
	Vector3(float nx, float ny, float nz, float nw);

	float magnitude() const;
	Vector3 normal() const;
	
	Vector3 operator+(const Vector3 &a) const;
	Vector3 operator-(const Vector3 &a) const;
	Vector3 operator*(float s) const;
	Vector3 operator*(const Vector3 &a) const;
	Vector3 &operator*=(const Vector3 &a);
};