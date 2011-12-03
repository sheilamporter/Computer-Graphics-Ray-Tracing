#ifndef _COLLISIONS_H_
#define _COLLISIONS_H_

class Vector3;

struct Material
{
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	float shininess;
	float reflection;
	float transmission;
};

struct Collision {
	Material material;
	Vector3 point;
	Vector3 normal;
	Vector3 color;
	float distance;
};

#endif