#pragma once
#include "Vector3.h"

struct Affine
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

struct Sphere
{
	Vector3 center;
	float radius;
};

struct Plane {

	Vector3 normal;
	float distance;
};