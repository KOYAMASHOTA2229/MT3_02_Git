#pragma once
#include "Vector3.h"

struct Affine
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

struct Line {
	Vector3 origin;
	Vector3 diff;
};

struct Ray {
	Vector3 origin;
	Vector3 diff; 
};

struct Segment {
	Vector3 origin;
	Vector3 diff;
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