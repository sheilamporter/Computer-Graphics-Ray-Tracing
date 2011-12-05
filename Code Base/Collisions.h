#ifndef _COLLISIONS_H_
#define _COLLISIONS_H_

class Vector3;

struct Material
{
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	Vector3 emittance;
	float shininess;
	float reflection;
	float transmission;
	float refractionIndex;
};

struct Collision {
	Material material;
	Vector3 point;
	Vector3 normal;
	float distance;
};

#endif